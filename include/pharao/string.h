#ifndef PHARAO_STRING_H
#define PHARAO_STRING_H
/**---------------------------------------------------------------------------
 *
 * @file   printer.hpp
 * @brief  Functions for handling strings
 *
 * @date   20250818
 * @author Maximilian Seesslen <src@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <string.h>                    // FILE


/*--- Declarations ---------------------------------------------------------*/


extern "C"
{
   size_t pharao_strlen(const char *string);
}


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! PHARAO_STRING_H
