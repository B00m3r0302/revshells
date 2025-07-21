# CLI Application
cmake_minimum_required(VERSION 3.19)

# Create the CLI executable
add_executable(revshells-cli
    main.cpp
)

# Link libraries
target_link_libraries(revshells-cli PRIVATE
    revshells-core
    revshells-payloads
    revshells-listeners
)

# Include directories
target_include_directories(revshells-cli PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

# Source groups for IDE organization
source_group("CLI Application" FILES
    main.cpp
)