/**---------------------------------------------------------------------------
 *
 * @file   stdio.cpp
 * @brief  Sloppy implementation of stdio functions
 *
 * @date   20250818
 * @author Maximilian Seesslen <src@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <sys/stat.h>
#include <stdio.h>                     // stdout
#include <unistd.h>                    // _exit, _write
#include <stdlib.h>                    // abort
#include <string.h>                    // memset, strlen

#if ! __x86_64__
#include <newlib.h>
#endif

#if ! defined _PICOLIBC__
   #define pharao_write       _write
   #define pharao_read        _read
#else
   #define pharao_write       pharao_write_picolibc
   #define pharao_read        pharao_read_picolibc
#endif


/*--- Implementation -------------------------------------------------------*/


extern "C"
{
   // This should be the unistd functions:
   int _read (int __fd, void *__buf, size_t __nbyte);
   int _write (int __fd, const void *__buf, size_t __nbyte);

   //int pharao_putc(char ch, FILE* f);
   int pharao_fputc ( int character, FILE * stream );
   int pharao_fgetc ( FILE * stream );
   
   int pharao_fputs ( const char * str, FILE * stream );
   char	*pharao_fgets(char *__str, int __size, FILE *__stream);
   
   int pharao_fflush ( FILE * stream );
   
   int pharao_puts ( const char * str );
   int pharao_getchar ( void );
   int pharao_putchar ( int character );
   size_t pharao_fwrite( const void* buffer, size_t size, size_t count,
                  FILE* stream );
   void pharao_setbuf (FILE *__restrict, char *__restrict);
   int pharao_setvbuf (FILE *__restrict, char *__restrict, int, size_t);
   
   #if defined _PICOLIBC__
      int pharao_write_picolibc(int __fd, const void *__buf, size_t __nbyte);
      int pharao_read_picolibc(int __fd, const void *__buf, size_t __nbyte);
      
      // These are needed for picolibc. Name could be different, there is an
      // pointer in FILE. But assume stdout does not exit.
      int _putc(char c, struct __file *f);
      int _getc(struct __file *f);
   #endif
}


int pharao_fputc ( int character, FILE * stream )
{
   return( pharao_write(0, &character, 1) );
}


int pharao_fgetc ( FILE * stream )
{
   char c;
   int sta;
   sta=pharao_read(0, &c, 1);
   if(sta>=0)
      return((int)c);
   return( -1 );
}


int pharao_fputs ( const char * str, FILE * stream )
{
   return( pharao_write(0, str, strlen(str)) );
}


char *pharao_fgets(char *str, int size, FILE *__stream)
{
   int sta=pharao_read(0, str, size);
   if(sta<0)
       return( nullptr );
   
   return( str );
}


int pharao_puts ( const char * str )
{
   int ret=pharao_write(0, str, strlen(str));
   pharao_write(0, "\n", 1);
   return( ret );
}


size_t pharao_fwrite( const void* buffer, size_t size, size_t count,
         FILE* stream )
{
   return( pharao_write(0, buffer, size*count) );
}
 

int pharao_getchar ( void )
{
   char c;
   int sta;
   sta=pharao_read(0, &c, 1);
   if(sta>=0)
      return((int)c);
   return( -1 );
}


int pharao_putchar ( int character )
{
   int sta;
   sta=pharao_write(0, &character, 1);
   if(sta>0)
      return( character );
   return( -1 );
}


int pharao_fflush ( FILE * stream )
{
   return(0);
}


void pharao_setbuf (FILE *__restrict, char *__restrict)
{

};


int pharao_setvbuf (FILE *__restrict, char *__restrict, int, size_t)
{
   return(0);
};

#if defined _PICOLIBC__

// unistd write command not available on picolibc
int pharao_write_picolibc(int __fd, const void *__buf, size_t __nbyte)
{
   for(int i1=0; i1<__nbyte; i1++)
   {
      // Correct: stdout->put
      _putc(((char*)__buf)[i1], stdout);
   } 
   
   return(0);
}


// unistd read command not available on picolibc
int pharao_read_picolibc(int __fd, const void *__buf, size_t __nbyte)
{
   int sta;
   for(int i1=0; i1<__nbyte; i1++)
   {
      // Correct: stdout->put
      if( ( sta = _getc(stdin) ) < 0 )
      {
         return( sta );
      }
      ((char*)__buf)[i1] = (char) sta;
   } 
   
   return( __nbyte );
}

#endif

#if __x86_64__

   int _read (int __fd, void *__buf, size_t __nbyte)
   {
      return( __nbyte );
   }

   int _write (int __fd, const void *__buf, size_t __nbyte)
   {
      return( __nbyte );
   }

#endif


/*--- Fin ------------------------------------------------------------------*/
