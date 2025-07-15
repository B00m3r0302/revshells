cmake_minimum_required(VERSION 3.10)
project(RevShells VERSION 1.0.0 LANGUAGES CXX)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Debug/Release configurations
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

# Source files
set(CORE_SOURCES
    src/core/Options.h
    src/core/InterfacePayload.h
    src/core/InterfaceListener.h
)

set(PAYLOAD_SOURCES
    src/payloads/PayloadFactory.cpp
    src/payloads/implementations/Bash_I_Payload.cpp
    src/payloads/implementations/Bash_196_Payload.cpp
    src/payloads/implementations/Bash_RL_Payload.cpp
    src/payloads/implementations/Bash_5_Payload.cpp
    src/payloads/implementations/Nc_Mkfifo_Payload.cpp
    src/payloads/implementations/Nc_E_Payload.cpp
    src/payloads/implementations/Nc_Exe_Payload.cpp
    src/payloads/implementations/Busybox_Nc_Payload.cpp
    src/payloads/implementations/Nc_C_Payload.cpp
    src/payloads/implementations/Ncat_E_Payload.cpp
    src/payloads/implementations/Ncat_Exe_E_Payload.cpp
    src/payloads/implementations/Ncat_UDP_Payload.cpp
    src/payloads/implementations/Curl_Payload.cpp
    src/payloads/implementations/Rustcat_Payload.cpp
    src/payloads/implementations/C_Payload.cpp
    src/payloads/implementations/C_Windows_Payload.cpp
    src/payloads/implementations/C_Sharp_TCP_Client_Payload.cpp
    src/payloads/implementations/C_Sharp_Bash_I_Payload.cpp
    src/payloads/implementations/Haskell_Payload.cpp
    src/payloads/implementations/OpenSSL_Payload.cpp
    src/payloads/implementations/Perl_Payload.cpp
    src/payloads/implementations/Perl_No_Sh_Payload.cpp
    src/payloads/implementations/Perl_PentestMonkey_Payload.cpp
    src/payloads/implementations/PHP_PentestMonkey_Payload.cpp
)

set(LISTENER_SOURCES
    src/listeners/ListenerFactory.h
)

set(APP_SOURCES
    src/app/main.cpp
)

# Create executable
add_executable(revshells
    ${CORE_SOURCES}
    ${PAYLOAD_SOURCES}
    ${LISTENER_SOURCES}
    ${APP_SOURCES}
)

# Include directories
target_include_directories(revshells PRIVATE src)

# Platform-specific settings
if(WIN32)
    target_compile_definitions(revshells PRIVATE WINDOWS_PLATFORM)
elseif(APPLE)
    target_compile_definitions(revshells PRIVATE MACOS_PLATFORM)
else()
    target_compile_definitions(revshells PRIVATE LINUX_PLATFORM)
endif()

# Optional: Link threading library
find_package(Threads REQUIRED)
target_link_libraries(revshells Threads::Threads)

# Install target
install(TARGETS revshells DESTINATION bin)

# CPack configuration for packaging
include(CPack)
set(CPACK_PACKAGE_NAME "RevShells")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ Reverse Shell Generator")
set(CPACK_PACKAGE_VENDOR "RevShells Project")

# Testing (optional)
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()