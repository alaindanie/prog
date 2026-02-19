# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\prog_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\prog_autogen.dir\\ParseCache.txt"
  "prog_autogen"
  )
endif()
