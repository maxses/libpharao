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
      src/string.cpp
      include/pharao/printer.hpp
      include/pharao/print.h
      include/pharao/string.h
)

target_include_directories(
   ${PROJECT_NAME}
   PRIVATE
      include
   INTERFACE
      include
)

if( NOT PHARAO_FEATURES )
   list( APPEND PHARAO_FEATURES remove_signal remove_impure
            replace_stdio malloc )
endif( NOT PHARAO_FEATURES )

if( PHARAO_ADD_FEATURES )
   list( APPEND PHARAO_FEATURES "${PHARAO_ADD_FEATURES}" )
endif( PHARAO_ADD_FEATURES )

foreach( feature IN LISTS PHARAO_REMOVE_FEATURES )
    message(STATUS "Remove feature=${feature}")
    list( REMOVE_ITEM PHARAO_FEATURES ${feature} )
endforeach()
list( REMOVE_DUPLICATES PHARAO_FEATURES )

message( STATUS "Pharao features: ${PHARAO_FEATURES}" )


function( check_feature feature mapFile)
   message( DEBUG "Checking for feature ${feature} -> ${mapFile}")
   if( "${feature}" IN_LIST PHARAO_FEATURES )
      set( PHARAO_FLAGS ${PHARAO_FLAGS}
         -Wl,--just-symbols=${CMAKE_CURRENT_LIST_DIR}/cmake/${mapFile}
         PARENT_SCOPE
      )
      if( NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/cmake/${mapFile}" )
         message ( FATA_ERROR "Map file does not exist: ${CMAKE_CURRENT_LIST_DIR}/cmake/${mapFile}" )
      endif()
   endif()
endfunction()


check_feature( "remove_free" "symbolsFree.map" )
check_feature( "replace_stdio" "symbolsStdio.map" )
check_feature( "remove_impure" "symbolsImpure.map" )
check_feature( "remove_signal" "symbolsSignal.map" )
check_feature( "malloc" "symbolsMalloc.map" )
check_feature( "remove_divide" "symbolsDivide.map" )
# No benefit:
check_feature( "replace_string" "symbolsString.map" )


if( NOT ( "${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" OR HOST ) )
   target_link_options(
      ${PROJECT_NAME}
      PUBLIC
         -Wl,--just-symbols=${CMAKE_CURRENT_LIST_DIR}/cmake/symbolsMisc.map
         ${PHARAO_FLAGS}
   )
endif()

if( "${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" OR HOST )
    add_subdirectory( tests )
endif()


#---fin.-----------------------------------------------------------------------
