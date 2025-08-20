//----------------------------------------------------------------------------
//
// \brief   functions for printing text with small footprint
//
//----------------------------------------------------------------------------


//---Includes-----------------------------------------------------------------


#include <pharao/print.h>
#include <stdio.h>                     // FILE
#include <stdarg.h>
#include <pharao/printer.hpp>

// Does not make much difference, 4 bytes
#define PHARAO_GLOBAL_STDOUT_PRINTER   1


//---Implementation-----------------------------------------------------------


#if defined PHARAO_GLOBAL_STDOUT_PRINTER
   CPrinter pr(stdout, nullptr, 6000);
#endif

int pharao_vfprintf ( FILE * stream, const char * format, va_list args )
{
   #if !defined PHARAO_GLOBAL_STDOUT_PRINTER
      CPrinter pr( stream, nullptr, 6000);
   #endif
   return( pr.vprintf( format, args) );
}

int pharao_vsnprintf(char *__s, size_t __n, const char *format, va_list args)
{
   CPrinter p(nullptr, __s, __n);

   return( p.vprintf( format, args) );
}


int pharao_snprintf(char* dest, size_t len, const char *format, ... )
{
   va_list argp;
   va_start(argp, format);

   int ilen=pharao_vsnprintf(dest, len, format, argp);

   va_end(argp);

   return( ilen );
}


int pharao_printf(const char *format, ... )
{
   va_list argp;
   va_start(argp, format);

   // Don't use stdout; It may get interpreted from 'struct _reent *_impure_ptr'
   // which may be garbage.
   int ilen=pharao_vfprintf((FILE*)0x12345678, format, argp);

   va_end(argp);

   return( ilen );
}


//---fin----------------------------------------------------------------------
