# Core interfaces and common structures
cmake_minimum_required(VERSION 3.19)

# Create a header-only library for core interfaces
add_library(revshells-core INTERFACE)

# Include directories for the core interfaces
target_include_directories(revshells-core INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Core headers (header-only, so no source files to compile)
target_sources(revshells-core INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        InterfaceListener.h
        InterfacePayload.h
        Options.h
)

# Source groups for IDE organization
source_group("Core Interfaces" FILES
    InterfaceListener.h
    InterfacePayload.h
    Options.h
)