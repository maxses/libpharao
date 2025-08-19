/**---------------------------------------------------------------------------
 *
 * @file   impure.cpp
 * @brief  Override existing impure structure and hope no one will try to use it
 *
 *         MCU shal throw an error when tried to write impure data.
 *
 * @date   20250818
 * @author Maximilian Seesslen <src@seesslen.net>
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <stdint.h>                    // uint32_t


/*--- Implementation -------------------------------------------------------*/


const uint32_t pharao_impure_data = 0x12345678;
// biwak_impure_ptr has to point to something valid (0x0 is valid). The word at
// this address is handed over.
const uint32_t* pharao_impure_ptr = (uint32_t*)&pharao_impure_data;


/*--- Fin ------------------------------------------------------------------*/
