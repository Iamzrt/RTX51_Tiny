/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date   
  * @brief   
  ******************************************************************************  
  * 
  * 
  ******************************************************************************
  */
/*-- includes ----------------------------------------------------------------*/
#include <stdio.h>

#include "./lib/N76E003.h"
#include "./lib/SFR_Macro.h"
#include "./lib/Function_define.h"

#include "./hal_clk.h"

/*-- defined -----------------------------------------------------------------*/



/*-- private variables -------------------------------------------------------*/
static  bit    BIT_TMP;


/*-- functions ---------------------------------------------------------------*/


/**           
  * @brief   HIRC enable         
  * @param    
  * @return  
  * @note	   MCU power on system clock is HIRC (16 MHz).
             Please keep P3.0 HIGH before you want to modify Fsys to LIRC.
  */
void  mcu_clk_init(u32_t freq)
{
  clr_EA;				                    /* disable interrupts*/

  set_HIRCEN;                       /* HIRC 16MHz */
  while((CKSWT&SET_BIT5)==0);				/* check ready */
  clr_OSC1;
  clr_OSC0;
  while((CKEN&SET_BIT0)==1);				/* check system clock switching OK or NG */

	set_EA;                           /* enable interrupts*/
}





/*---------------------- end of file -----------------------------------------*/



