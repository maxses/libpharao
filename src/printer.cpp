//----------------------------------------------------------------------------
//
// \brief   functions for printing text with small footprint
//
//----------------------------------------------------------------------------


//---Includes-----------------------------------------------------------------


#include <pharao/printer.hpp>


//---Implementation-----------------------------------------------------------


int CPrinter::vprintf(const char *format, va_list args)
{
   int pos=0;

   while( format[pos] && ( m_count < m_last ) )
   {
      switch(format[pos])
      {
         case '%':
         {
            bool done=false;
            m_base=10;
            m_signed=true;

            while(!done)
            {
               pos++;
               switch(format[pos])
               {
                  case 'X':
                  case 'x':
                  case 'p':
                     m_base=16;
                     m_signed=false;
                  case 'd':
                     if ( format[pos] == 'p' )
                     {
                        addCh('0');
                        addCh('x');
                     }
                     printInt( va_arg(args, uint32_t) );
                     done=true;
                     break;
                  case 's':
                  {
                     const char *str=va_arg(args, const char *);
                     if(m_dest)
                     {
                        while( ( m_count < m_last ) && *str )
                        {
                           addCh( *str++ );
                        }
                     }
                     if(m_stream)
                     {
                        fputs( str, m_stream );
                     }
                     m_count+=strlen(str);
                     done=true;
                     break;
                  }
                  case 'c':
                  {
                     char _ch=va_arg(args, int);
                     addCh( _ch );
                     done=true;
                     break;
                  }
                  case '%':
                  {
                     addCh( format[pos] );
                     done=true;
                     break;
                  }
                  case '0'...'9':
                  {
                     parseAlignment( format, pos );
                     pos--;   // It gets increased automatically
                     break;
                  }
                  // Fields to be ignored
                  case 'l':
                     continue;
                     break;
                  default:
                     addCh( '%' );
                     addCh( format[pos] );
                     done=true;
                     break;
               }
            }
            break;
         }
         case '\n':
            addCh( format[pos] );
            addCh( '\r' );
            break;
         default:
            addCh( format[pos] );
            break;
      }
      pos++;
   }
   if( m_dest )
   {
      // don't use addCh; it will avoid setting it when limitation is reached
      *m_dest++=0;
   }

   return(m_count);
};


//---fin----------------------------------------------------------------------
