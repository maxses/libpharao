/**---------------------------------------------------------------------------
 *
 * @file   malloc.cpp
 * @brief  Sloppy implementation of some malloc functions
 *
 * @date   20250818
 * @author Maximilian Seesslen <src@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <unistd.h>


/*--- Implementation -------------------------------------------------------*/


extern "C"
{
   void __malloc_lock(struct _reent *);
   void __malloc_unlock(struct _reent *);
}


void __malloc_lock(struct _reent *)
{
   return;
}


void __malloc_unlock(struct _reent *)
{
   return;
}


/*--- Fin ------------------------------------------------------------------*/
