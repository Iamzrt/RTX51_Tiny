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
#include "./mcu_it.h"

/*-- defined -----------------------------------------------------------------*/

/*-- private variables -------------------------------------------------------*/
static    SysTickCallback   sysTickCallback = NULL;
static    Pin0IntCallback   pin0IntCallback = NULL;
static    WtdIntCallback    wtdIntCallback = NULL;

static    bit    BIT_TMP;


/*-- functions ---------------------------------------------------------------*/

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   systick_callback_register(SysTickCallback func)
{
  sysTickCallback = func;
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   pin0_int_callback_register(Pin0IntCallback func)
{
  pin0IntCallback = func;
}

void   wtd_int_callback_register(WtdIntCallback func)
{
  wtdIntCallback = func;
}


/**           
  * @brief     WDT interrupt sub-routine        
  * @param    
  * @return  
  * @note
  */
void  mcu_wdt_ISR (void)   interrupt 10
{
  if(wtdIntCallback != NULL)
  {
    wtdIntCallback();
  }

  clr_WDTF;

  mcu_reset();
}


/**           
  * @brief    TIMER 3 interrupt subroutine        
  * @param    
  * @return  
  * @note
  */
void   mcu_timer3_ISR (void) interrupt 16 
{
  clr_TF3;

  if(sysTickCallback != NULL)
  {
    sysTickCallback();
  }
}



/**           
  * @brief    Pin interrupt subroutine        
  * @param    
  * @return  
  * @note
  */
void  mcu_pin_interrupt_ISR (void) interrupt 7
{
  if(PIF == 0x01)
  {
    PIF = 0x00;                             /* clear interrupt flag */
	
    if(pin0IntCallback != NULL)
    {
      pin0IntCallback();
    }		
  }
}



/*---------------------- end of file -----------------------------------------*/
