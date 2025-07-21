# Payload factory and implementations
cmake_minimum_required(VERSION 3.19)

# Collect all payload implementation files
file(GLOB_RECURSE PAYLOAD_SOURCES
    "implementations/*.cpp"
)

file(GLOB_RECURSE PAYLOAD_HEADERS
    "implementations/*.h"
)

# Create library for payloads
add_library(revshells-payloads STATIC
    PayloadFactory.cpp
    PayloadFactory.h
    ${PAYLOAD_SOURCES}
    ${PAYLOAD_HEADERS}
)

# Include directories
target_include_directories(revshells-payloads PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/implementations
)

# Link to core interfaces
target_link_libraries(revshells-payloads PUBLIC
    revshells-core
)

# Source groups for IDE organization
source_group("Payload Factory" FILES
    PayloadFactory.cpp
    PayloadFactory.h
)

source_group("Bash Payloads" FILES
    implementations/Bash_196_Payload.cpp
    implementations/Bash_196_Payload.h
    implementations/Bash_5_Payload.cpp
    implementations/Bash_5_Payload.h
    implementations/Bash_I_Payload.cpp
    implementations/Bash_I_Payload.h
    implementations/Bash_RL_Payload.cpp
    implementations/Bash_RL_Payload.h
    implementations/Bash_UDP_Payload.h
    implementations/Busybox_Nc_Payload.cpp
    implementations/Busybox_Nc_Payload.h
)

source_group("C/C++ Payloads" FILES
    implementations/C_Payload.cpp
    implementations/C_Payload.h
    implementations/C_Windows_Payload.cpp
    implementations/C_Windows_Payload.h
)

source_group("C# Payloads" FILES
    implementations/C_Sharp_Bash_I_Payload.cpp
    implementations/C_Sharp_Bash_I_Payload.h
    implementations/C_Sharp_TCP_Client_Payload.cpp
    implementations/C_Sharp_TCP_Client_Payload.h
)

source_group("Network Tool Payloads" FILES
    implementations/Nc_C_Payload.cpp
    implementations/Nc_C_Payload.h
    implementations/Nc_E_Payload.cpp
    implementations/Nc_E_Payload.h
    implementations/Nc_Exe_Payload.cpp
    implementations/Nc_Exe_Payload.h
    implementations/Nc_Mkfifo_Payload.cpp
    implementations/Nc_Mkfifo_Payload.h
    implementations/Ncat_E_Payload.cpp
    implementations/Ncat_E_Payload.h
    implementations/Ncat_Exe_E_Payload.cpp
    implementations/Ncat_Exe_E_Payload.h
    implementations/Ncat_UDP_Payload.cpp
    implementations/Ncat_UDP_Payload.h
    implementations/Rustcat_Payload.cpp
    implementations/Rustcat_Payload.h
)

source_group("Scripting Language Payloads" FILES
    implementations/PHP_Ivan_Payload.cpp
    implementations/PHP_Ivan_Payload.h
    implementations/PHP_PentestMonkey_Payload.cpp
    implementations/PHP_PentestMonkey_Payload.h
    implementations/Perl_No_Sh_Payload.cpp
    implementations/Perl_No_Sh_Payload.h
    implementations/Perl_Payload.cpp
    implementations/Perl_Payload.h
    implementations/Perl_PentestMonkey_Payload.cpp
    implementations/Perl_PentestMonkey_Payload.h
)

source_group("Other Language Payloads" FILES
    implementations/Haskell_Payload.cpp
    implementations/Haskell_Payload.h
)

source_group("Security Tool Payloads" FILES
    implementations/Curl_Payload.cpp
    implementations/Curl_Payload.h
    implementations/OpenSSL_Payload.cpp
    implementations/OpenSSL_Payload.h
)