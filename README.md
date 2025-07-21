# RevShells Project

A modular reverse shell generator designed for cybersecurity education and penetration testing labs. Provides both command-line and GUI interfaces for generating various reverse shell payloads and corresponding listeners.

⚠️ **Educational Use Only**: This tool is intended for authorized security testing, educational purposes, and personal lab environments only.

## Features

- **25+ Payload Types**: Supports Bash, C, C#, PHP, Perl, Python, PowerShell, and more
- **17+ Listener Types**: Including netcat variants, socat, openssl, msfconsole, and custom implementations
- **Multi-Platform**: Linux, Windows, and macOS payload generation
- **Encoding Options**: Base64, URL encoding, and double URL encoding
- **Dual Interface**: Both CLI and Qt6 GUI applications
- **Modular Architecture**: Extensible design for adding new payloads and listeners

## Project Structure

```
src/
├── core/           # Shared interfaces and data structures
├── payloads/       # 25 payload implementations (Bash, C, PHP, Perl, etc.)
├── listeners/      # 17 listener implementations (nc, socat, openssl, etc.)
├── app/            # Command-line interface
└── ui/             # Qt6 GUI interface
```

## Supported Payloads

The project includes implementations for:
- **Shell Types**: Bash (multiple variants), C, C#, PHP, Perl, Python
- **Network Tools**: Netcat variants, Ncat, Rustcat, Socat
- **Encryption**: OpenSSL, TLS-enabled connections
- **Platforms**: Linux, Windows, macOS specific payloads
- **Encoding**: URL, Base64, and double encoding support

## Building

### Prerequisites
- CMake 3.19+
- Qt6 (6.5+)
- C++17 compatible compiler

### Build Commands
```bash
mkdir build && cd build
cmake ..
make
```

This produces two executables:
- `revshells-cli`: Command-line interface
- `revshells-gui`: Qt6 graphical interface

### Qt Creator Integration
- Open the root CMakeLists.txt in Qt Creator
- Configure with Qt6 kit
- Build targets available: `revshells-cli` and `revshells-gui`

## Usage

### Command Line
```bash
./revshells-cli --host 192.168.1.100 --port 4444 --payload bash_i
```

### GUI Interface
Launch the Qt6 application for an interactive interface:
```bash
./revshells-gui
```

## Architecture Principles

1. **Factory Pattern**: PayloadFactory and ListenerFactory for dynamic creation
2. **Interface Segregation**: Clear separation between payload and listener interfaces
3. **Platform Abstraction**: Unified API across different operating systems
4. **Extensibility**: Easy addition of new payload types and listeners
5. **Encoding Support**: Built-in encoding capabilities for payload obfuscation