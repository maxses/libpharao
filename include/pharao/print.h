#ifndef PHARAO_PRINT_H
#define PHARAO_PRINT_H
//----------------------------------------------------------------------------
//
// \brief   functions for printing text with small footprint
//
//----------------------------------------------------------------------------


//---Includes------------------------------------------------------------------


#include <stdio.h>                     // FILE


//---Declaration---------------------------------------------------------------


extern "C"
{
   int pharao_vsnprintf(char *__s, size_t __n, const char *__fmt, va_list ap);
   int pharao_vfprintf ( FILE * stream, const char * format, va_list arg )
                  _ATTRIBUTE ((__format__ (__printf__, 2, 0)));
   int pharao_snprintf(char* dest, size_t len, const char *format, ... )
                  _ATTRIBUTE ((__format__ (__printf__, 3, 0)));
   int pharao_printf (const char *__restrict, ...)
                  _ATTRIBUTE ((__format__ (__printf__, 1, 2)));
}


//---fin----------------------------------------------------------------------
#endif // ? ! PHARAO_PRINT_H
