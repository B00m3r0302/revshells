# Qt GUI Application
cmake_minimum_required(VERSION 3.19)

# Find required Qt components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Create the GUI executable
qt_add_executable(revshells-gui
    WIN32 MACOSX_BUNDLE
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${CMAKE_SOURCE_DIR}/main.cpp  # Main file from root
)

# Link libraries
target_link_libraries(revshells-gui PRIVATE
    Qt::Core
    Qt::Widgets
    revshells-core
    revshells-payloads
    revshells-listeners
)

# Include directories
target_include_directories(revshells-gui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)