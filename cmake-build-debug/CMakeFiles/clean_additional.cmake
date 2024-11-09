# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Plants_Vs__Zombies_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Plants_Vs__Zombies_autogen.dir/ParseCache.txt"
  "Plants_Vs__Zombies_autogen"
  )
endif()
