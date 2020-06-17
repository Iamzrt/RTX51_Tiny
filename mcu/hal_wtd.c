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

#include "./hal_wtd.h"

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
void   mcu_wdt_start(void)
{
#if   WDT_ENABLE
  TA=0xAA; 
  TA=0x55; 
  WDCON |= 0x07;				 /* Setting WDT prescale,1.638 s */

  set_WDTR;              /* WDT run */
  set_WDCLR;             /* Clear WDT timer	*/
  set_EWDT;				       /* Enable wdt interrupt. */
#endif
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   mcu_wdt_feed(void)
{
#if   WDT_ENABLE
  set_WDCLR;
#endif
}


#if   WDT_ENABLE

/**           
  * @brief     WDT interrupt sub-routine        
  * @param    
  * @return  
  * @note
  */
void  mcu_wdt_ISR (void)   interrupt 10
{
  clr_WDTF;
}

#endif

/*---------------------- end of file -----------------------------------------*/



