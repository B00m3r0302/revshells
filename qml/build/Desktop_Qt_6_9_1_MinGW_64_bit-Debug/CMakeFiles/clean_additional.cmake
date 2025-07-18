# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\qml_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\qml_autogen.dir\\ParseCache.txt"
  "qml_autogen"
  )
endif()
