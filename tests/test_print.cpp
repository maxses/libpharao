//----------------------------------------------------------------------------
///
/// \file   main.cpp
///
/// \brief  main file for pinmux
///
/// \date   20220619
/// \author Maximilian Seesslen <mes@seesslen.net>
///
//----------------------------------------------------------------------------


//---Documentation------------------------------------------------------------


//---Includes -----------------------------------------------------------------


//---General--------------------------

#if defined ( CATCH_V3 )
   #include <catch2/catch_test_macros.hpp>
#elif defined ( CATCH_V2 )
   #include <catch2/catch.hpp>
#elif defined ( CATCH_V1 )
   #include <catch/catch.hpp>
#else
   #error "Either 'catch' or 'catch2' has to be installed"
#endif

#include <pharao/print.h>
#include <stdarg.h>
#include <QString>

//--- Own ----------------------------

#define TEST_ALL
#define STOP_ON_FAIL


//---Implementation------------------------------------------------------------


TEST_CASE( "Print", "[default]" )
{
   char dest[0x100];
   SECTION( "Print" )
   {
      QString str=QString("%1").arg(1234567890);
      int size;

      pharao_snprintf( dest, 0x100, "%d", 1234567890 );
      REQUIRE ( str == dest );
      REQUIRE ( str != "Hallo Welt" );

      memset(dest, '#', 0x100);
      str=QString("%1").arg(0x1234AFFE, 0, 16).toUpper();
      pharao_snprintf( dest, 0x100, "%x", 0x1234AFFE );
      REQUIRE ( str == dest );

      memset(dest, '#', 0x100);
      str=QString("0x123");
      size=pharao_snprintf( dest, 6, "0x%x", 0x1234AFFE );
      printf("Size: %d\n", size);
      REQUIRE ( str == dest );
      REQUIRE ( size == 5 );

      memset(dest, '#', 0x100);
      str=QString(" -12390- ");
      size=pharao_snprintf( dest, 20, " -%d- ", 12390 );
      REQUIRE ( str == dest );

      memset(dest, '#', 0x100);
      str=QString("Hallo Wel");
      size=pharao_snprintf( dest, 10, "Hallo %s da draussen", "Welt!" );
      printf("Size: %d\n", size);
      REQUIRE ( str == dest );

      memset(dest, '#', 0x100);
      str=QString("Hallo Welt und so!");
      size=pharao_snprintf( dest, 19, "Hallo %s und so!", "Welt" );
      printf("Size: %d\n", size);
      REQUIRE ( str == dest );

      memset(dest, '#', 0x100);
      str=QString(" -12390- ");
      size=pharao_snprintf( dest, 20, " -%d- ", 12390 );
      REQUIRE ( str == dest );

      memset(dest, '#', 0x100);
      str=QString("X-5129988X");
      size=pharao_snprintf( dest, 0x80, "X%dX", -5129988 );
      REQUIRE ( str == dest );

      memset(dest, '#', 0x100);
      str=QString("XMUHX 99088 ");
      size=pharao_snprintf( dest, 0x80, "X%c%c%cX %d ", 'M', 'U', 'H', 99088 );
      REQUIRE ( str == dest );

      memset(dest, '#', 0x100);
      str=QString("1234%");
      size=pharao_snprintf( dest, 6, "1234%", 1212 );
      REQUIRE ( str == dest );

      // Alignment
      memset(dest, '#', 0x100);
      str=QString("      36");
      size=pharao_snprintf( dest, 9, "%8d", 36 );
      REQUIRE ( str == dest );

      // Padding zeros
      memset(dest, '#', 0x100);
      str=QString("36:06:01");
      size=pharao_snprintf( dest, 9, "%02d:%02d:%02d", 36, 6, 1 );
      REQUIRE ( str == dest );

      // Alignment too small
      memset(dest, '#', 0x100);
      str=QString("85936");
      size=pharao_snprintf( dest, 9, "%02d", 85936, 6, 1 );
      REQUIRE ( str == dest );

      // Rellay no space for the '-'
      memset(dest, '#', 0x100);
      str=QString(" ");
      size=pharao_snprintf( dest, 2, " %d", -12345678 );
      REQUIRE ( str == dest );

      // Print base for pointers
      memset(dest, '#', 0x100);
      str=QString("0x11223344");
      size=pharao_snprintf( dest, 64, "%p", 0x11223344 );
      REQUIRE ( str == dest );
   }
}


//---fin-----------------------------------------------------------------------
