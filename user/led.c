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
#include "./led.h"



/*-- defined -----------------------------------------------------------------*/


#define        TIME_MS(x)                 (x)
																					
																					                     

#define        LED1_PORT		               PORT1
#define        LED1_PIN								     PIN1
#define        LED1_MODE                   PP_MODE

#define        LED2_PORT		               PORT1
#define        LED2_PIN								     PIN2
#define        LED2_MODE                   PP_MODE

#define        LED3_PORT		               PORT1
#define        LED3_PIN								     PIN3
#define        LED3_MODE                   PP_MODE

#define        LED4_PORT		               PORT1
#define        LED4_PIN								     PIN4
#define        LED4_MODE                   PP_MODE



/*-- private variables -------------------------------------------------------*/
static   tick_size_t XDATA ledTaskBaseTr = 0;



/*-- functions ---------------------------------------------------------------*/
static    void    led_task_timer_schedule(void);
static    void    led_task_logic_schedule(void);


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   led_ctrl(LedDef led, LedWrType ctrl)
{
  GpioMode level;

  if(ctrl == LED_OFF)
	{
		level = IO_LOW;
	}
	else if(ctrl == LED_ON)
	{
		level = IO_HIGH;
	}

  switch(led)
	{
	  case LED1:
		{
			mcu_gpio_write(LED1_PORT, LED1_PIN, level);
		}break;

	  case LED2:
		{
			mcu_gpio_write(LED2_PORT, LED2_PIN, level);
		}break;

	  case LED3:
		{
		  mcu_gpio_write(LED3_PORT, LED3_PIN, level);
		}break;

	  case LED4:
		{
		  mcu_gpio_write(LED4_PORT, LED4_PIN, level);
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
static  void  led_task_timer_schedule(void)
{
	TASK_TIMER_BEGIN(ledTaskBaseTr, TIME_MS(100));


	

	TASK_TIMER_END(ledTaskBaseTr);
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  led_task_logic_schedule(void)
{
 
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   led_task(void)	 _task_   LED_TASK_PRIORITY
{
  led_ctrl(LED1, LED_OFF);
	led_ctrl(LED2, LED_OFF);
	led_ctrl(LED3, LED_OFF);
	led_ctrl(LED4, LED_OFF);

  while(1)
	{
	  led_task_timer_schedule();
	  led_task_logic_schedule(); 

    os_switch_task();
	}
}




/*---------------------- end of file -----------------------------------------*/



