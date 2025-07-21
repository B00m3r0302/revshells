# Listener factory and implementations
cmake_minimum_required(VERSION 3.19)

# Create library for listeners (header-only)
add_library(revshells-listeners INTERFACE)

# Include directories
target_include_directories(revshells-listeners INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/implementations
)

# Link to core interfaces
target_link_libraries(revshells-listeners INTERFACE
    revshells-core
)

# All listener headers
target_sources(revshells-listeners INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        ListenerFactory.h
        implementations/Hoaxshell_Listener.h
        implementations/Msfconsole_Listener.h
        implementations/NcBusyBox_Listener.h
        implementations/NcFreeBsd_Listener.h
        implementations/Nc_Listener.h
        implementations/NcatExe_Listener.h
        implementations/NcatTLS_Listener.h
        implementations/Ncat_Listener.h
        implementations/Openssl_Listener.h
        implementations/Powercat_Listener.h
        implementations/PwncatWindows_Listener.h
        implementations/Pwncat_Listener.h
        implementations/RlwrapNc_Listener.h
        implementations/Rustcat_Listener.h
        implementations/SocatTTY_Listener.h
        implementations/Socat_Listener.h
        implementations/WindowsConPty_Listener.h
)

# Source groups for IDE organization
source_group("Listener Factory" FILES
    ListenerFactory.h
)

source_group("Listener Implementations" FILES
    implementations/Hoaxshell_Listener.h
    implementations/Msfconsole_Listener.h
    implementations/NcBusyBox_Listener.h
    implementations/NcFreeBsd_Listener.h
    implementations/Nc_Listener.h
    implementations/NcatExe_Listener.h
    implementations/NcatTLS_Listener.h
    implementations/Ncat_Listener.h
    implementations/Openssl_Listener.h
    implementations/Powercat_Listener.h
    implementations/PwncatWindows_Listener.h
    implementations/Pwncat_Listener.h
    implementations/RlwrapNc_Listener.h
    implementations/Rustcat_Listener.h
    implementations/SocatTTY_Listener.h
    implementations/Socat_Listener.h
    implementations/WindowsConPty_Listener.h
)