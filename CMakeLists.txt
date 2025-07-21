cmake_minimum_required(VERSION 3.19)
project(revshells LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

# Qt setup
qt_standard_project_setup()

# Add subdirectories
add_subdirectory(src/core)
add_subdirectory(src/listeners)
add_subdirectory(src/payloads)
add_subdirectory(src/app)
add_subdirectory(src/ui)

# Translation files
qt_add_translations(
    TARGETS revshells-gui
    TS_FILES translations/revshells_en_US.ts
)

include(GNUInstallDirs)

# Install targets
install(TARGETS revshells-cli revshells-gui
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Qt deployment script for GUI
qt_generate_deploy_app_script(
    TARGET revshells-gui
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})