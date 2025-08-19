#------------------------------------------------------------------------------
#
# \brief	CMakeLists.txt file for "libpharao"
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.11)

project ( pharao C CXX )

add_library(
   ${PROJECT_NAME}
   STATIC
      src/stdio.cpp
      src/impure.cpp
      src/malloc.cpp
      src/print.cpp
      src/printer.cpp
      include/pharao/printer.hpp
      include/pharao/print.h
)

target_include_directories(
   ${PROJECT_NAME}
   PRIVATE
      include
   INTERFACE
      include
)

if( NOT ( "${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" OR HOST ) )
   target_link_options(
      ${PROJECT_NAME}
      PUBLIC
         -Wl,--just-symbols=${CMAKE_CURRENT_LIST_DIR}/cmake/symbolsMalloc.map
         -Wl,--just-symbols=${CMAKE_CURRENT_LIST_DIR}/cmake/symbolsMisc.map
         -Wl,--just-symbols=${CMAKE_CURRENT_LIST_DIR}/cmake/symbolsImpure.map
         -Wl,--just-symbols=${CMAKE_CURRENT_LIST_DIR}/cmake/symbolsSignal.map
         -Wl,--just-symbols=${CMAKE_CURRENT_LIST_DIR}/cmake/symbolsStdio.map
   )
endif()

if( "${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" OR HOST )
    add_subdirectory( tests )
endif()


#---fin.-----------------------------------------------------------------------
