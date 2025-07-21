# Architecture Documentation

This document provides a comprehensive overview of the RevShells application architecture, design patterns, and implementation details.

## System Overview

RevShells is built using modern C++ design patterns to create a flexible, extensible reverse shell generation system. The architecture emphasizes:

- **Modularity**: Clear separation of concerns
- **Extensibility**: Easy to add new features
- **Maintainability**: Well-organized, testable code
- **Performance**: Efficient resource usage

## High-Level Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    Application Layer                        │
├─────────────────────────────────────────────────────────────┤
│  CLI Interface  │  GUI Interface  │  API Interface         │
├─────────────────────────────────────────────────────────────┤
│                    Business Logic Layer                     │
├─────────────────────────────────────────────────────────────┤
│  PayloadFactory │  ListenerFactory │  EncodingUtils        │
├─────────────────────────────────────────────────────────────┤
│                    Core Abstractions                        │
├─────────────────────────────────────────────────────────────┤
│  IPayload       │  IListener      │  Options               │
├─────────────────────────────────────────────────────────────┤
│                    Implementation Layer                     │
├─────────────────────────────────────────────────────────────┤
│  Concrete Payloads     │     Concrete Listeners            │
└─────────────────────────────────────────────────────────────┘
```

## Directory Structure

```
src/
├── app/                    # CLI application entry point
│   └── main.cpp           # Main function and command-line interface
├── core/                  # Core abstractions and configuration
│   ├── Options.h          # Configuration structures and enums
│   ├── InterfacePayload.h # Abstract payload interface
│   └── InterfaceListener.h# Abstract listener interface
├── payloads/              # Payload generation system (25 implementations)
│   ├── PayloadFactory.h   # Factory class declaration
│   ├── PayloadFactory.cpp # Factory implementation with encoding
│   └── implementations/   # Concrete payload implementations
│       ├── Bash_I_Payload.{h,cpp}    # Interactive Bash shells
│       ├── Bash_196_Payload.{h,cpp}  # Bash /dev/tcp method
│       ├── Bash_5_Payload.{h,cpp}    # Bash reverse shell
│       ├── Bash_RL_Payload.{h,cpp}   # Bash read line method
│       ├── Bash_UDP_Payload.h        # UDP-based Bash shell
│       ├── C_Payload.{h,cpp}         # C language reverse shell
│       ├── C_Sharp_*.{h,cpp}         # C# implementations
│       ├── C_Windows_Payload.{h,cpp} # Windows C implementation
│       ├── Curl_Payload.{h,cpp}      # cURL-based reverse shell
│       ├── Haskell_Payload.{h,cpp}   # Haskell reverse shell
│       ├── Nc_*_Payload.{h,cpp}      # Multiple netcat variants
│       ├── Ncat_*_Payload.{h,cpp}    # Multiple Ncat variants
│       ├── OpenSSL_Payload.{h,cpp}   # SSL encrypted reverse shell
│       ├── PHP_*_Payload.{h,cpp}     # PHP implementations
│       ├── Perl_*_Payload.{h,cpp}    # Perl implementations
│       └── Rustcat_Payload.{h,cpp}   # Rust-based reverse shell
├── listeners/             # Listener management system (17 implementations)
│   ├── ListenerFactory.h  # Factory class with registry pattern
│   └── implementations/   # Concrete listener implementations
│       ├── Nc_Listener.h          # Standard netcat listener
│       ├── NcBusyBox_Listener.h   # BusyBox netcat variant
│       ├── NcFreeBsd_Listener.h   # FreeBSD netcat variant
│       ├── Ncat_Listener.h        # Nmap's Ncat listener
│       ├── NcatExe_Listener.h     # Windows Ncat executable
│       ├── NcatTLS_Listener.h     # TLS-enabled Ncat
│       ├── Openssl_Listener.h     # OpenSSL encrypted listener
│       ├── Powercat_Listener.h    # PowerShell netcat equivalent
│       ├── Pwncat_Listener.h      # Enhanced netcat alternative
│       ├── PwncatWindows_Listener.h # Windows pwncat variant
│       ├── RlwrapNc_Listener.h    # rlwrap-enhanced netcat
│       ├── Rustcat_Listener.h     # Rust-based listener
│       ├── Socat_Listener.h       # Socat multipurpose listener
│       ├── SocatTTY_Listener.h    # TTY-enabled socat listener
│       ├── WindowsConPty_Listener.h # Windows ConPTY listener
│       ├── Hoaxshell_Listener.h   # Hoaxshell framework
│       └── Msfconsole_Listener.h  # Metasploit console listener
└── ui/                    # Qt6 GUI interface
    ├── CMakeLists.txt     # Qt-specific build configuration
    ├── README.md          # GUI-specific documentation
    ├── mainwindow.{h,cpp,ui} # Main application window
    └── [Qt UI components]
```

## Design Patterns

### 1. Abstract Factory Pattern

The system uses the Abstract Factory pattern to create families of related objects:

```cpp
// Abstract Product
class IPayload {
public:
    virtual ~IPayload() = default;
    virtual std::string name() const = 0;
    virtual std::string generate(const Options& opts) const = 0;
    virtual std::string listener(const Options& opts) const = 0;
};

// Concrete Factory
class PayloadFactory {
private:
    std::unordered_map<std::string, std::unique_ptr<IPayload>> registry_;
public:
    std::string generate(const std::string& type, const Options& opts) const;
    std::vector<std::string> available() const;
};
```

**Benefits:**
- Decouples client code from concrete implementations
- Makes it easy to add new payload types
- Provides a consistent interface for all payloads

### 2. Strategy Pattern

The encoding system uses the Strategy pattern to select algorithms at runtime:

```cpp
enum class Encoding {
    NONE, URL, DOUBLE_URL, BASE64
};

class PayloadFactory {
private:
    std::string applyEncoding(const std::string& payload, const Options& opts) const {
        switch (opts.encoding) {
            case Encoding::BASE64: return base64Encode(payload);
            case Encoding::URL: return urlEncode(payload);
            case Encoding::DOUBLE_URL: return doubleUrlEncode(payload);
            default: return payload;
        }
    }
};
```

**Benefits:**
- Algorithms can be selected at runtime
- Easy to add new encoding methods
- Keeps encoding logic separate from payload generation

### 3. Registry Pattern

Both factories use a registry pattern to manage implementations:

```cpp
class ListenerFactory {
private:
    std::unordered_map<std::string, std::unique_ptr<IListener>> registry_;
    
public:
    ListenerFactory() {
        registry_["nc"] = std::make_unique<NcListener>();
        registry_["socat"] = std::make_unique<SocatListener>();
        // Register other implementations...
    }
    
    IListener* get(const std::string& name) const {
        auto it = registry_.find(name);
        return it != registry_.end() ? it->second.get() : nullptr;
    }
};
```

**Benefits:**
- Centralized management of implementations
- Easy to query available options
- Supports plugin-like architecture

## Core Components

### Options System

The `Options` struct serves as the central configuration hub:

```cpp
enum class PayloadType { REVERSE, BIND, MSFVENOM, HOAXSHELL };
enum class Platform { LINUX, WINDOWS, MAC };
enum class Encoding { NONE, URL, DOUBLE_URL, BASE64 };

struct Options {
    std::string host;
    int port;
    PayloadType payloadType = PayloadType::REVERSE;
    Platform platform = Platform::LINUX;
    Encoding encoding = Encoding::NONE;
    std::string listenerType;
    std::string interpreter;
    std::map<std::string, bool> flags;
};
```

**Design Decisions:**
- **Enums over strings**: Type safety and performance
- **Default values**: Sensible defaults for common use cases
- **Extensible flags**: Future-proof with generic flag system

### Interface Design

The interfaces follow the Interface Segregation Principle:

```cpp
// Minimal payload interface
class IPayload {
public:
    virtual ~IPayload() = default;
    virtual std::string name() const = 0;
    virtual std::string generate(const Options& opts) const = 0;
    virtual std::string listener(const Options& opts) const = 0;
};

// Minimal listener interface
class IListener {
public:
    virtual ~IListener() = default;
    virtual std::string name() const = 0;
    virtual std::string command(const Options& opts) const = 0;
};
```

**Benefits:**
- Small, focused interfaces
- Easy to implement and test
- Minimal coupling between components

## Factory Implementation Details

### PayloadFactory Architecture

```cpp
class PayloadFactory {
private:
    // Registry of available payloads
    std::unordered_map<std::string, std::unique_ptr<IPayload>> registry_;
    
    // Platform-specific generation methods
    std::string generateLinuxPayload(const Options& opts) const;
    std::string generateWindowsPayload(const Options& opts) const;
    std::string generateMacPayload(const Options& opts) const;
    
    // Encoding utilities
    std::string applyEncoding(const std::string& payload, const Options& opts) const;
    
public:
    // Main generation method
    std::string generateByType(const Options& opts) const;
    
    // Registry management
    std::vector<std::string> available() const;
    std::string generate(const std::string& type, const Options& opts) const;
};
```

### Generation Flow

```
Options Input
     ↓
Platform Detection
     ↓
Payload Type Switch
     ↓
Shell Generation
     ↓
Encoding Application
     ↓
Final Payload
```

## Memory Management

### Smart Pointer Usage

The system uses modern C++ memory management:

```cpp
// Factory registry uses unique_ptr for single ownership
std::unordered_map<std::string, std::unique_ptr<IPayload>> registry_;

// Registration example
registry_["bash"] = std::make_unique<BashPayload>();

// Access through raw pointers (non-owning)
IPayload* payload = registry_["bash"].get();
```

**Benefits:**
- Automatic memory management
- Clear ownership semantics
- Exception safety
- No memory leaks

### RAII Pattern

Resources are managed through RAII:

```cpp
class PayloadFactory {
private:
    std::unordered_map<std::string, std::unique_ptr<IPayload>> registry_;
    
public:
    // Constructor initializes all resources
    PayloadFactory() {
        initializePayloads();
    }
    
    // Destructor automatically cleans up (compiler-generated)
    ~PayloadFactory() = default;
};
```

## Error Handling Strategy

### Return Value Strategy

Most methods use return values for error handling:

```cpp
std::string PayloadFactory::generate(const std::string& type, const Options& opts) const {
    auto it = registry_.find(type);
    if (it == registry_.end()) {
        return "";  // Empty string indicates error
    }
    return it->second->generate(opts);
}
```

### Exception Strategy (Alternative)

For critical errors, exceptions may be used:

```cpp
std::string PayloadFactory::generate(const std::string& type, const Options& opts) const {
    if (opts.host.empty() || opts.port <= 0) {
        throw std::invalid_argument("Invalid host or port");
    }
    
    auto it = registry_.find(type);
    if (it == registry_.end()) {
        throw std::runtime_error("Unknown payload type: " + type);
    }
    
    return it->second->generate(opts);
}
```

## Performance Characteristics

### Time Complexity

- **Payload Generation**: O(1) - Hash table lookup
- **Listener Lookup**: O(1) - Hash table lookup  
- **Encoding**: O(n) - Linear in payload length
- **Registry Initialization**: O(m) - Linear in number of implementations

### Space Complexity

- **Factory Storage**: O(m) - One instance per implementation
- **Payload Generation**: O(n) - Linear in payload length
- **Options Storage**: O(1) - Fixed size structure

### Memory Usage

```cpp
// Typical memory footprint
sizeof(PayloadFactory) ≈ 
    sizeof(std::unordered_map) +           // ~64 bytes
    (number_of_payloads * sizeof(unique_ptr)) +  // ~8 bytes per payload
    (sum of all payload object sizes)      // Varies by implementation
```

## Threading Considerations

### Thread Safety

The current implementation is **not thread-safe** by design:

```cpp
// NOT thread-safe - multiple threads accessing registry
class PayloadFactory {
private:
    std::unordered_map<std::string, std::unique_ptr<IPayload>> registry_;
public:
    std::string generate(const std::string& type, const Options& opts) const;
};
```

### Making it Thread-Safe

For thread safety, consider these approaches:

1. **Immutable Registry**: Initialize once, never modify
2. **Read-Write Locks**: Allow concurrent reads, exclusive writes
3. **Thread-Local Storage**: Separate registry per thread

```cpp
// Thread-safe version with mutex
class ThreadSafePayloadFactory {
private:
    mutable std::shared_mutex registry_mutex_;
    std::unordered_map<std::string, std::unique_ptr<IPayload>> registry_;
    
public:
    std::string generate(const std::string& type, const Options& opts) const {
        std::shared_lock<std::shared_mutex> lock(registry_mutex_);
        // Safe concurrent access for reads
        auto it = registry_.find(type);
        return it != registry_.end() ? it->second->generate(opts) : "";
    }
};
```

## Extensibility Points

### Adding New Payload Types

1. **Create Interface Implementation**:
```cpp
class NewPayload : public IPayload {
    std::string name() const override { return "new_payload"; }
    std::string generate(const Options& opts) const override;
    std::string listener(const Options& opts) const override;
};
```

2. **Register in Factory**:
```cpp
PayloadFactory::PayloadFactory() {
    registry_["new_payload"] = std::make_unique<NewPayload>();
}
```

### Adding New Platforms

1. **Extend Platform Enum**:
```cpp
enum class Platform { LINUX, WINDOWS, MAC, FREEBSD };
```

2. **Add Generation Method**:
```cpp
std::string PayloadFactory::generateFreeBSDPayload(const Options& opts) const;
```

3. **Update Platform Switch**:
```cpp
switch (opts.platform) {
    case Platform::FREEBSD: return generateFreeBSDPayload(opts);
    // Other cases...
}
```

## Testing Architecture

### Unit Testing Structure

```cpp
class PayloadFactoryTest : public ::testing::Test {
protected:
    PayloadFactory factory;
    Options opts;
    
    void SetUp() override {
        opts.host = "127.0.0.1";
        opts.port = 4444;
        opts.platform = Platform::LINUX;
    }
};
```

### Mock Objects

For testing, create mock implementations:

```cpp
class MockPayload : public IPayload {
public:
    MOCK_METHOD(std::string, name, (), (const, override));
    MOCK_METHOD(std::string, generate, (const Options&), (const, override));
    MOCK_METHOD(std::string, listener, (const Options&), (const, override));
};
```

## Build System Integration

### CMake Structure

```cmake
cmake_minimum_required(VERSION 3.10)
project(RevShells)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/app/main.cpp
    src/payloads/PayloadFactory.cpp
    src/payloads/implementations/Bash_I_Payload.cpp
    # Add other source files...
)

# Include directories
include_directories(src)

# Create executable
add_executable(revshells ${SOURCES})

# Link libraries
target_link_libraries(revshells ${CMAKE_THREAD_LIBS_INIT})
```

## Security Considerations

### Input Validation

```cpp
std::string PayloadFactory::generate(const std::string& type, const Options& opts) const {
    // Validate inputs
    if (opts.host.empty() || opts.port <= 0 || opts.port > 65535) {
        throw std::invalid_argument("Invalid host or port");
    }
    
    // Sanitize host input
    if (opts.host.find_first_not_of("0123456789.abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-") != std::string::npos) {
        throw std::invalid_argument("Invalid characters in host");
    }
    
    // Continue with generation...
}
```

### Output Sanitization

```cpp
std::string PayloadFactory::sanitizePayload(const std::string& payload) const {
    // Remove potentially dangerous characters
    std::string sanitized = payload;
    // Implementation depends on specific security requirements
    return sanitized;
}
```

## Future Architecture Considerations

### Plugin System

Consider a dynamic plugin system:

```cpp
class PluginManager {
public:
    void loadPlugin(const std::string& pluginPath);
    void unloadPlugin(const std::string& pluginName);
    std::vector<std::string> listPlugins() const;
};
```

### Configuration System

Add configuration file support:

```cpp
class ConfigManager {
public:
    void loadConfig(const std::string& configPath);
    Options getDefaultOptions() const;
    void saveConfig(const std::string& configPath) const;
};
```

### Logging System

Implement structured logging:

```cpp
class Logger {
public:
    void log(LogLevel level, const std::string& message);
    void setLogLevel(LogLevel level);
    void addHandler(std::unique_ptr<LogHandler> handler);
};
```

This architecture provides a solid foundation for a maintainable, extensible, and performant reverse shell generation system while maintaining clean separation of concerns and following modern C++ best practices.