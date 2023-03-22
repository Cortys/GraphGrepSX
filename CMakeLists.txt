cmake_minimum_required(VERSION 3.10)

project(GraphGrepSX)

add_executable(ggsx GraphGrepSXConsole.cpp)

find_path(DIRENT_INCLUDE_DIRS "dirent.h")
target_include_directories(ggsx PRIVATE ${DIRENT_INCLUDE_DIRS})
target_include_directories(ggsx PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vflib2/include" "${CMAKE_CURRENT_SOURCE_DIR}/GGSXLib")

add_subdirectory(vflib2)
target_link_libraries(ggsx PRIVATE vf)

set_target_properties(ggsx PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

# if (CMAKE_COMPILER_IS_GNUCXX)
#   target_compile_options(ggsx PRIVATE -Wall -Wextra)
# endif()

# Set optimization and threading flags
if (MSVC)
  target_compile_options(ggsx PRIVATE /O2 /MT)
  # Disable runtime checks for stack frame integrity
  string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
else()
  target_compile_options(ggsx PRIVATE -O3 -pthread)
endif()
