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

#include "./hal_gpio.h"


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
void   mcu_gpio_set_all_default(void)
{
  Set_All_GPIO_Quasi_Mode;

}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  mcu_gpio_write(GpioPort port, GpioPin pin, GpioLevel level)
{	
  switch(port)
	{
	  case PORT0:
		{
	    P0 &= ~(1<<pin);
	    P0 |=  (level<<pin);		
		}break;

    case PORT1:
		{
	    P1 &= ~(1<<pin);
	    P1 |=  (level<<pin);		
		}break;

	  case PORT2:
		{
	    P2 &= ~(1<<pin);
	    P2 |=  (level<<pin);		
		}break;

    case PORT3:
		{
	    P3 &= ~(1<<pin);
	    P3 |=  (level<<pin);		
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
GpioLevel  mcu_gpio_read(GpioPort port, GpioPin pin)
{	
  GpioLevel ret;

  switch(port)
	{
	  case PORT0:
		{
	    ret = (P0 & (1 << pin)) >> pin;				
		}break;

    case PORT1:
		{
      ret = (P1 & (1 << pin)) >> pin;				
		}break;

	  case PORT2:
		{
      ret = (P2 & (1 << pin)) >> pin;			
		}break;

    case PORT3:
		{
      ret = (P3 & (1 << pin)) >> pin;				
		}break;

		default:
		  break;
	}

	return ret;
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  mcu_gpio_set_mode(GpioPort port, GpioPin pin, GpioMode mode)
{
  switch(port)
	{
	  case PORT0:
		{
		  if(mode == QUASI_MODE)
			{
        P0M1 &= ~(1<<pin); 
			  P0M2 &= ~(1<<pin);	
			}
			else if(mode == PP_MODE)
			{
			  P0M1 &= ~(1<<pin);
				P0M2 |=  (1<<pin);
			}	
			else if(mode == INPUT_MODE)
			{
			  P0M1 |=  (1<<pin);
				P0M2 &= ~(1<<pin);
			}	
			else if(mode == OD_MODE)
			{
				P0M1 |= (1<<pin);
				P0M2 |= (1<<pin);
			}	
		}break;

    case PORT1:
		{
		  if(mode == QUASI_MODE)
			{
        P1M1 &= ~(1<<pin); 
			  P1M2 &= ~(1<<pin);	
			}
			else if(mode == PP_MODE)
			{
			  P1M1 &= ~(1<<pin);
				P1M2 |=  (1<<pin);
			}	
			else if(mode == INPUT_MODE)
			{
			  P1M1 |=  (1<<pin);
				P1M2 &= ~(1<<pin);
			}	
			else if(mode == OD_MODE)
			{
				P1M1 |= (1<<pin);
				P1M2 |= (1<<pin);
			}	
		}break;

	  case PORT2:
		{
	
		}break;

    case PORT3:
		{
		  if(mode == QUASI_MODE)
			{
        P3M1 &= ~(1<<pin); 
			  P3M2 &= ~(1<<pin);	
			}
			else if(mode == PP_MODE)
			{
			  P3M1 &= ~(1<<pin);
				P3M2 |=  (1<<pin);
			}	
			else if(mode == INPUT_MODE)
			{
			  P3M1 |=  (1<<pin);
				P3M2 &= ~(1<<pin);
			}	
			else if(mode == OD_MODE)
			{
				P3M1 |= (1<<pin);
				P3M2 |= (1<<pin);
			}		
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
//void  mcu_gpio_interrupt_config(GpioPort port, GpioPin pin, GpioTrig trig, GpioTrigPhase phase)
//{
//  switch(port)
//	{
//	  case PORT0:
//		{
//	   	clr_PIPS1;
//			clr_PIPS0;	
//		}break;
//
//    case PORT1:
//		{
//	   	clr_PIPS1;
//			set_PIPS0;      			
//		}break;
//
//	  case PORT2:
//		{
//	   	set_PIPS1;
//			clr_PIPS0;       			
//		}break;
//
//    case PORT3:
//		{
//	   	set_PIPS1;
//			set_PIPS0;       			
//		}break;
//
//		default:
//		  break;
//	}  
//}


/*---------------------- end of file -----------------------------------------*/



