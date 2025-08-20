//----------------------------------------------------------------------------
//
// \brief   functions for printing text with small footprint
//
//----------------------------------------------------------------------------


//---Includes-----------------------------------------------------------------


#include <pharao/print.h>
#include <stdio.h>                     // FILE
#include <stdarg.h>
#include <stdint.h>
#include <string.h>


//---Implementation-----------------------------------------------------------


class CPrinter
{
   private:

   public:
      FILE* m_stream;
      char* m_dest;
      int m_last;
      int m_base;
      int m_count;
      bool m_signed;

      // For alignment:
      char m_fillChar;
      int m_alignment;

      constexpr CPrinter( FILE * stream, char *__s, size_t __n )
         :m_stream( stream )
         ,m_dest( __s )
         ,m_last( __n - 1 )
         ,m_base( 10 )
         ,m_count( 0 )
         ,m_signed( true )
         ,m_fillChar(' ')
         ,m_alignment(0)
      {};

      int getDigits( uint32_t  val )
      {
         int digits=1;
         while( ( val /= m_base ) )
         {
            digits++;
         }
         return( digits );
      }

      void addCh(const char c)
      {
         if(m_stream)
         {
            fputc(c, m_stream);
         }
         if( m_dest )
         {
            if( m_count >= m_last )
            {
               return;
            }
            *m_dest++=c;
         }
         m_count++;
      };

      int puts(const char* str)
      {
         int i1=0;
         for(; str[i1]; i1++ )
         {
            addCh( str[i1] );
         }

         if( m_dest )
         {
            addCh( 0 );
         }

         return( i1 );
      }

      int printInt( uint32_t val )
      {
         int digits;
         char c;
         if(m_signed)
         {
            if((int)val<0)
            {
               addCh('-');
               val=-val;
               m_alignment--;
            }
         }
         digits=getDigits( val );
         int max=m_last - m_count;
         int maxLen=digits < max ? digits: max;

         for(int i1=0; i1 < ( m_alignment - digits ); i1++ )
         {
            addCh( m_fillChar );
         }
         for(int i1=0; i1< maxLen; i1++)
         {
            int divider = 1;
            for(int i2=0; i2 < (digits-1-i1 ); i2++)
               divider*=m_base;
            int digit=(val / divider) & 0xF;
            if( digit <= 9 )
               c='0'+digit;
            else
               c=('A'-0xA)+digit;
            addCh(c);
            val-=(digit*divider);
         }
         resetAlignment();
         return(m_count);
      }

      int vprintf(const char *format, va_list args);

      /**
       * @brief Parse the numbers specifien number alignment and fill character
       * @param pos
       * @return
       */
      void parseAlignment(const char* format, int& pos)
      {
         if( format[pos]=='0' )
         {
            m_fillChar='0';
            pos++;
         }

         while( isDigit( format[pos] ) )
         {
            m_alignment*=10;
            m_alignment+=format[pos++]-'0';
         }
      }
      void resetAlignment()
      {
         m_fillChar=' ';
         m_alignment=0;
      }
      static bool isDigit( const char c )
      {
         return( ( c >= '0' ) && ( c <= '9' ) );
      }
};


//---fin----------------------------------------------------------------------
