# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/OP_Lab1_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/OP_Lab1_autogen.dir/ParseCache.txt"
  "OP_Lab1_autogen"
  )
endif()
