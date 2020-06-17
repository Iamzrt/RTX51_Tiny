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

#include "./hal_timer.h"

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
void  hal_timer_disable_interrupt(HwTrDef tr)
{
  switch(tr)
	{
    case TIMER0:
		{
      clr_ET0;		
		}break;	 

    case TIMER1:
		{
      clr_ET1;		
		}break;

    case TIMER2:
		{
      clr_ET2;		
		}break;

    case TIMER3:
		{
      clr_ET3;		
		}break;

		default:
		  break;
	}
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  hal_timer_stop(HwTrDef tr)
{
  switch(tr)
	{
    case TIMER0:
		{
      clr_TR0;		
		}break;	 

    case TIMER1:
		{
      clr_TR1;		
		}break;

    case TIMER2:
		{
      clr_TR2;		
		}break;

    case TIMER3:
		{
      clr_TR3;		
		}break;

		default:
		  break;
	}
}

/*---------------------- end of file -----------------------------------------*/



