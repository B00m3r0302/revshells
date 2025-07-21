# UI Module - Qt6 Graphical Interface

This module provides the Qt6-based graphical user interface for the RevShells reverse shell generator.

## Overview

The GUI module offers an intuitive interface for:
- **Payload Selection**: Choose from 25+ available reverse shell payload types
- **Configuration**: Set host, port, platform, encoding options
- **Listener Setup**: Select and configure corresponding listeners
- **Code Generation**: Generate and display payload code with syntax highlighting
- **Copy/Export**: Easy copying of generated payloads to clipboard

## Architecture

### Qt6 Integration
- **Modern Qt Framework**: Uses Qt6 6.5+ with CMake integration
- **Native Look & Feel**: Platform-appropriate UI styling (Windows/Linux/macOS)
- **Responsive Design**: Scalable interface supporting various screen sizes
- **Accessibility**: Keyboard navigation and screen reader support

### Component Structure

```
src/ui/
├── CMakeLists.txt          # Qt6-specific build configuration
├── README.md               # This documentation
├── mainwindow.h            # Main window class declaration
├── mainwindow.cpp          # Main window implementation 
└── mainwindow.ui           # Qt Designer UI layout file
```

### Key Components

- **MainWindow**: Primary application window with payload configuration
- **Qt Designer Integration**: Visual UI design with `.ui` file
- **Factory Integration**: Direct access to PayloadFactory and ListenerFactory
- **Cross-Platform Support**: Native behavior on Windows, Linux, and macOS

## Features

### Payload Configuration Interface
- **Dropdown Selection**: Easy payload type selection from available implementations
- **Platform Targeting**: Linux, Windows, macOS payload generation options
- **Encoding Options**: Base64, URL, double URL encoding support
- **Advanced Options**: Custom interpreters, special flags, listener types

### User Experience
- **Real-time Preview**: Live payload generation as options change
- **Syntax Highlighting**: Code syntax highlighting for generated payloads
- **Copy to Clipboard**: One-click copying of generated code
- **Export Options**: Save payloads to files with proper extensions

### Integration Features
- **Factory Pattern Access**: Direct integration with payload/listener factories
- **Validation**: Real-time input validation with error feedback
- **Help System**: Context-sensitive help and payload documentation
- **Theme Support**: Light/dark theme options

## Build Configuration

### CMake Integration
The UI module uses Qt6's modern CMake integration:

```cmake
# Qt6 executable with proper resource handling
qt_add_executable(revshells-gui WIN32 MACOSX_BUNDLE
    mainwindow.cpp mainwindow.h mainwindow.ui
    ../app/main.cpp  # Shared main entry point
)

# Qt6 module linking
target_link_libraries(revshells-gui PRIVATE 
    Qt6::Core Qt6::Widgets
    revshells-core revshells-payloads revshells-listeners
)
```

### Build Process
1. **MOC Processing**: Qt's Meta-Object Compiler processes signals/slots
2. **UIC Generation**: User Interface Compiler converts `.ui` to C++ headers  
3. **Resource Compilation**: Qt resources embedded in executable
4. **Library Linking**: Links against core business logic libraries
5. **Platform Packaging**: Creates native app bundles (macOS) or executables

## Development Workflow

### Qt Creator Integration
- **Project Recognition**: Open root `CMakeLists.txt` in Qt Creator
- **UI Designer**: Directly edit `mainwindow.ui` with visual designer
- **Debugging**: Full Qt debugging support with object inspection
- **Preview**: Live preview of UI changes during development

### Adding New UI Features

1. **Update UI Layout**: Modify `mainwindow.ui` in Qt Designer
2. **Extend MainWindow**: Add new slots and signal handlers in `mainwindow.h/cpp`
3. **Factory Integration**: Connect UI elements to payload/listener factories
4. **Testing**: Test across different platforms and Qt themes

## Security Considerations

### Input Validation
- **Host Validation**: Ensures valid IP addresses or hostnames
- **Port Validation**: Validates port ranges (1-65535)
- **Injection Prevention**: Sanitizes all user inputs before payload generation
- **Error Handling**: Graceful error handling with user-friendly messages

### Educational Use Disclaimer
- **Prominent Warnings**: Clear educational use warnings in the interface
- **Context Help**: Documentation emphasizing responsible use
- **License Information**: Easy access to license and usage terms

## Future Enhancements

### Planned Features
- **Payload History**: Save and recall previously generated payloads
- **Batch Generation**: Generate multiple payloads with different configurations
- **Template System**: Save and load payload configuration templates
- **Testing Integration**: Built-in connection testing capabilities
- **Advanced Encoding**: Additional encoding methods and chaining options

### UI Improvements
- **Dark Theme**: Complete dark theme implementation
- **Keyboard Shortcuts**: Comprehensive keyboard navigation support
- **Accessibility**: Enhanced screen reader and high contrast support
- **Internationalization**: Multi-language support using Qt's translation system

⚠️ **Educational Purpose**: This GUI is designed for cybersecurity education, authorized penetration testing, and security research in controlled lab environments only.