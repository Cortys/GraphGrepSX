cmake_minimum_required(VERSION 3.5)
project(vflib2)

set(CMAKE_CXX_STANDARD 11)

set(SRC_FILES
  src/argedit.cc
  src/argraph.cc
  src/argloader.cc
  src/error.cc
  src/gene.cc
  src/gene_mesh.cc
  src/match.cc
  src/ull_state.cc
  src/ull_sub_state.cc
  src/vf_mono_state.cc
  src/vf_state.cc
  src/vf_sub_state.cc
  src/vf2_state.cc
  src/vf2_sub_state.cc
  src/vf2_mono_state.cc
  src/sd_state.cc
  src/sortnodes.cc
  src/xsubgraph.cc
)

set(INC_FILES
  include/allocpool.h
  include/argedit.h
  include/argloader.h
  include/argraph.h
  include/error.h
  include/gene.h
  include/sd_state.h
  include/state.h
  src/sortnodes.h
  include/ull_state.h
  include/ull_sub_state.h
  include/vf_mono_state.h
  include/vf_state.h
  include/vf_sub_state.h
  include/vf2_state.h
  include/vf2_sub_state.h
  include/vf2_mono_state.h
  include/xsubgraph.h
)

add_library(vf STATIC ${SRC_FILES} ${INC_FILES})
target_include_directories(vf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(vf PRIVATE -w -O6)

add_custom_command(TARGET vf POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/lib
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:vf> ${CMAKE_CURRENT_SOURCE_DIR}/lib/
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_LINKER_FILE:vf> ${CMAKE_CURRENT_SOURCE_DIR}/lib/
)
