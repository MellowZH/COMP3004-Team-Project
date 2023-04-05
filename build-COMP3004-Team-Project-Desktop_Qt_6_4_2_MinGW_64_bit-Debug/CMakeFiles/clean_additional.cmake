# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\COMP3004-Team-Project_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\COMP3004-Team-Project_autogen.dir\\ParseCache.txt"
  "COMP3004-Team-Project_autogen"
  )
endif()
