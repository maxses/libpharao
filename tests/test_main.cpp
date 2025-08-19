//----------------------------------------------------------------------------
///
/// \file   test_main.cpp
///
/// \brief  main file for liblepto tests
///
/// \date   20220619
/// \author Maximilian Seesslen <mes@seesslen.net>
///
//----------------------------------------------------------------------------


//---Documentation------------------------------------------------------------


//---Includes -----------------------------------------------------------------


//---General--------------------------

#define CATCH_CONFIG_MAIN

#if defined ( CATCH_V3 )
   #include <catch2/catch_test_macros.hpp>
#elif defined ( CATCH_V2 )
   #include <catch2/catch.hpp>
#elif defined ( CATCH_V1 )
   #include <catch/catch.hpp>
#else
   #error "Either 'catch' or 'catch2' has to be installed"
#endif


//---fin-----------------------------------------------------------------------
