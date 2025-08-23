//----------------------------------------------------------------------------
//
// \brief   functions for handling strings with small footprint
//
//----------------------------------------------------------------------------


//---Includes-----------------------------------------------------------------


#include <pharao/string.h>


//---Implementation-----------------------------------------------------------


// Absolutely no benefit
size_t pharao_strlen(const char *str)
{
   size_t i1;
   
   for (i1 = 0; str[i1]; ++i1)
   {
      // avoid replacing the construct with another 'strlen' by optimization
      // resulting in an infinite loop
      asm(""); 
   };
   
   return(i1);
}


//---fin----------------------------------------------------------------------
