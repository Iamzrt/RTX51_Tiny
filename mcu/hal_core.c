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

#include "./hal_core.h"


/*-- defined -----------------------------------------------------------------*/



/*-- private variables -------------------------------------------------------*/
static  bit    BIT_TMP;



/*-- functions ---------------------------------------------------------------*/



/**           
* @brief          
* @param    
* @return  
* @note
*/
void  mcu_reset(void)
{
  TA = 0xAA;
  TA = 0x55;
  set_SWRST;
}


/**           
* @brief          
* @param    
* @return  
* @note
*/
void  mcu_power_down(void)
{
  clr_BODEN; /* Disable under volt detect.关闭欠压检测 */
  set_PD;    /* Enter power down mode. 进入掉电模式 */
}

/*---------------------- end of file -----------------------------------------*/



