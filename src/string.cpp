/**---------------------------------------------------------------------------
 *
 * @file   printer.hpp
 * @brief  Functions for handling strings with small footprint
 *
 * @date   20250818
 * @author Maximilian Seesslen <src@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <pharao/string.h>


/*--- Implementation -------------------------------------------------------*/


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


/*--- Fin ------------------------------------------------------------------*/
