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

// Global printer makes small overhead
//#define PHARAO_GLOBAL_STDOUT_PRINTER   1
#undef PHARAO_GLOBAL_STDOUT_PRINTER


//---Implementation-----------------------------------------------------------


#if defined PHARAO_GLOBAL_STDOUT_PRINTER
   CPrinter pr(stdout, nullptr, 0x7F);
#endif
   
   
int pharao_vfprintf ( FILE * stream, const char * format, va_list args )
{
   #if !defined PHARAO_GLOBAL_STDOUT_PRINTER
      CPrinter pr( stream, nullptr, 0x7f);
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
   // Don't use '0'; this is handled as 'no stream'
   int ilen=pharao_vfprintf( (FILE*)0x01, format, argp );

   va_end(argp);

   return( ilen );
}


//---fin----------------------------------------------------------------------
