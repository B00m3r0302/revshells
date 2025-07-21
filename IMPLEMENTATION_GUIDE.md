# Implementation Guide - RevShells Architecture

## Overview

This guide provides detailed implementation information for the RevShells reverse shell generation tool. The project uses a modular C++ architecture with Qt6 GUI support and comprehensive payload/listener implementations.

## Core Architecture

The project is organized around these key design patterns:

### Factory Pattern Implementation
- **PayloadFactory**: Manages 25+ reverse shell payload implementations
- **ListenerFactory**: Manages 17+ listener implementations  
- **Registry Pattern**: Dynamic registration and lookup of implementations

### Interface-Based Design
- **IPayload**: Abstract interface for all payload implementations
- **IListener**: Abstract interface for all listener implementations
- **Options**: Centralized configuration structure

## Implementation Status

### Current Capabilities
- ✅ **25+ Payload Types**: Bash, C, C#, PHP, Perl, netcat variants, encrypted shells
- ✅ **17+ Listener Types**: netcat, socat, openssl, msfconsole, framework integration
- ✅ **Multi-Platform Support**: Linux, Windows, macOS payload generation
- ✅ **Encoding Support**: Base64, URL encoding, double URL encoding
- ✅ **Dual Interface**: CLI and Qt6 GUI applications
- ✅ **Modular CMake Build**: Clean separation of components

## Project Structure

```
revshells/
├── CMakeLists.txt              # Main project configuration
├── README.md                   # Project documentation
├── ARCHITECTURE.md             # Detailed architecture documentation
├── DEVELOPMENT.md              # Developer contribution guide
├── IMPLEMENTATION_GUIDE.md     # This implementation guide
├── revshells.qtcreator         # Qt Creator project file
├── main.cpp                    # Legacy main file (CLI moved to src/app/)
├── translations/               # Qt6 internationalization files
├── build/                      # Build output directory
└── src/
    ├── core/                   # Core interfaces and configuration
    │   ├── InterfacePayload.h  # Abstract payload interface
    │   ├── InterfaceListener.h # Abstract listener interface  
    │   └── Options.h           # Configuration enums and structs
    ├── payloads/               # Payload generation system
    │   ├── PayloadFactory.{h,cpp}  # Factory with encoding support
    │   └── implementations/    # 25+ concrete payload implementations
    │       ├── Bash_*_Payload.{h,cpp}     # Multiple Bash variants
    │       ├── C_*_Payload.{h,cpp}        # C language implementations
    │       ├── *_Sharp_*_Payload.{h,cpp}  # C# implementations
    │       ├── PHP_*_Payload.{h,cpp}      # PHP variants
    │       ├── Perl_*_Payload.{h,cpp}     # Perl implementations
    │       ├── Nc*_Payload.{h,cpp}        # Netcat variants
    │       ├── Ncat*_Payload.{h,cpp}      # Ncat implementations
    │       ├── OpenSSL_Payload.{h,cpp}    # Encrypted shells
    │       └── [Additional implementations]
    ├── listeners/              # Listener management system
    │   ├── ListenerFactory.h   # Factory class with registry
    │   └── implementations/    # 17+ concrete listener implementations
    │       ├── Nc*_Listener.h        # Netcat variants
    │       ├── Ncat*_Listener.h      # Ncat implementations
    │       ├── Socat*_Listener.h     # Socat variants
    │       ├── *ssl_Listener.h       # SSL/TLS listeners
    │       ├── Pwncat*_Listener.h    # Enhanced listeners
    │       ├── Msfconsole_Listener.h # Metasploit integration
    │       └── [Framework integrations]
    ├── app/                    # CLI application entry point
    │   └── main.cpp           # Command-line interface implementation
    └── ui/                     # Qt6 GUI application
        ├── CMakeLists.txt     # Qt-specific build configuration
        ├── README.md          # GUI module documentation
        ├── mainwindow.{h,cpp,ui} # Main application window
        └── [Qt UI components]
```

## Build Targets

The CMake configuration produces two main executables:

- **revshells-cli**: Command-line interface application
- **revshells-gui**: Qt6 graphical user interface application

## Building the Project

### Prerequisites
- CMake 3.19 or higher
- Qt6 6.5 or higher (for GUI)
- C++17 compatible compiler (GCC, Clang, MSVC)

### Build Process
```bash
cd /home/kali/Documents/real_revshells/revshells
mkdir build && cd build
cmake ..
make -j$(nproc)  # Parallel build
```

### Qt Creator Integration
1. Open the root `CMakeLists.txt` in Qt Creator
2. Configure with Qt6 kit
3. Available build targets: `revshells-cli`, `revshells-gui`
4. Run either target based on your interface preference

## Implementation Details

### Payload Factory Architecture

```cpp
class PayloadFactory {
private:
    std::unordered_map<std::string, std::unique_ptr<IPayload>> registry_;
    
    // Platform-specific generators (src/payloads/PayloadFactory.cpp:15-25)
    std::string generateLinuxPayload(const Options& opts) const;
    std::string generateWindowsPayload(const Options& opts) const;
    std::string generateMacPayload(const Options& opts) const;
    
    // Encoding utilities (src/payloads/PayloadFactory.cpp:20-30)
    std::string base64Encode(const std::string& input) const;
    std::string urlEncode(const std::string& input) const;
    std::string applyEncoding(const std::string& payload, const Options& opts) const;

public:
    // Factory interface (src/payloads/PayloadFactory.h:31-40)
    std::vector<std::string> available() const;
    std::string generate(const std::string& type, const Options& opts) const;
    std::string generateByType(const Options& opts) const;
};
```

### Options Configuration System

The centralized configuration uses type-safe enums:

```cpp
// src/core/Options.h:15-33
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

## Key Features

### Security Features
- **Input Validation**: Host and port validation in factory methods
- **Encoding Support**: Multiple encoding methods for payload obfuscation
- **Platform Isolation**: Separate generation paths for different operating systems

### Extensibility Features  
- **Plugin Architecture**: Easy addition of new payload types via registration
- **Interface Consistency**: All implementations follow IPayload/IListener interfaces
- **Configuration Flexibility**: Extensible Options struct with generic flags

### Performance Optimizations
- **Factory Pattern**: O(1) payload/listener lookup via hash tables
- **Smart Pointers**: Automatic memory management with unique_ptr
- **Minimal Interfaces**: Lean interfaces reduce coupling and compilation time

## Educational Value

This implementation serves as an excellent example of:

1. **Modern C++ Design**: Smart pointers, RAII, enum classes
2. **Design Patterns**: Factory, Strategy, Registry patterns in practice  
3. **Cross-Platform Development**: Platform-specific implementations with unified interfaces
4. **CMake Integration**: Modular build system with Qt6 support
5. **Security Tool Architecture**: Responsible framework design for educational purposes

⚠️ **Important**: This tool is designed for educational purposes, authorized penetration testing, and security research in controlled environments only.