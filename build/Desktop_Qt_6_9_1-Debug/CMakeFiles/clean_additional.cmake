# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/revshells_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/revshells_autogen.dir/ParseCache.txt"
  "revshells_autogen"
  )
endif()
