/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date   
  * @brief   	 Support 8 buttons.
  ******************************************************************************  
  * 
  * 
  ******************************************************************************
  */
/*-- includes ----------------------------------------------------------------*/
#include "./button.h"


/*-- defined -----------------------------------------------------------------*/
#define        TIME_MS(x)                 (x)


#define        BTN_PORT		                 PORT3
#define        BTN_PIN								     PIN0
#define        BTN_MODE                    INPUT_MODE


typedef  enum
{
  BTN_CHECK_STATE0 = (u8_t)0,
	BTN_CHECK_STATE1,
	BTN_CHECK_STATE2,
	BTN_CHECK_STATE3
}BtnCheckStateEnum;


/*-- private variables -------------------------------------------------------*/
static   tick_size_t  XDATA  buttonTaskBaseTr = 0;

static   ButtonState   buttonState = BTN_UP;


/*-- functions ---------------------------------------------------------------*/
static    void    button_task_timer_schedule(void);
static    void    button_task_logic_schedule(void);



/** @function  
  * @brief   
  * @param    	
  * @return  
  */
ButtonState  button_read(void)
{
  return buttonState;
}


/** @function  
  * @brief   
  * @param    	
  * @return  
  */
static   ButtonState  button_check_state(void)
{
	static   u8_t   XDATA buttonStep = 0;
	static   u32_t  XDATA buttonTimeCnt = 0;
	ButtonState  XDATA result = BTN_UP;
	GpioLevel   XDATA   ioState;
	
	ioState = mcu_gpio_read(BTN_PORT, BTN_PIN);  
	
	switch(buttonStep)
	{
		case BTN_CHECK_STATE0:
		{
			if(ioState == IO_LOW)
			{
				/* When the button is pressed, the status transitions to the status of button elimination and confirmation. */
				buttonTimeCnt = 0;
				buttonStep = BTN_CHECK_STATE1; 			
			}
		}break;
			
		case BTN_CHECK_STATE1:
		{
			if(ioState == IO_LOW)
			{
				/* The button is still pressed. Filt finish, start the timer.  */
				buttonTimeCnt = 0;
				buttonStep = BTN_CHECK_STATE2;
			}
			else
			{
				/* The button has been lifted and returned to the initial state of the button. */
				buttonStep = BTN_CHECK_STATE0;
			}
		}break;  
			
		case BTN_CHECK_STATE2:
		{
			if(ioState == IO_HIGH) 
			{
				/* The button is lifted to create a click operation. */
				result = BTN_DOWN;  
				buttonStep = BTN_CHECK_STATE0;  
			}
			else if((++buttonTimeCnt) >= 100)  /* 2000ms */
			{
				/* Press the button again and the time exceeds xx ms. */
				result = BTN_HOLD;  
				buttonStep = BTN_CHECK_STATE3;   /* Switch to wait for button release. */
			}
		}break;
			
		case BTN_CHECK_STATE3: 
		{
			/* Waiting for button release. */
			if(ioState == IO_HIGH)  
			{
				buttonStep = BTN_CHECK_STATE0;  
			}
		}break;
	}
	
	return result;
}


/** @function  
  * @brief   
  * @param    	
  * @return  
  */
static  ButtonState  button_identify(void)
{
	static u8_t  XDATA buttonStep = BTN_CHECK_STATE0;
	static u32_t XDATA buttonTimeCnt = 0;
	ButtonState XDATA  result = BTN_UP;
	ButtonState XDATA  state;
	
	state = button_check_state();
	
	switch(buttonStep)
	{
		case BTN_CHECK_STATE0:
		{
			if(state == BTN_DOWN)
			{
				/* The first click, do not return, to the next state to determine whether there will be a double click. */
				buttonTimeCnt = 0;  
				buttonStep = BTN_CHECK_STATE1;
			}
			else 
			{
				/* For buttonless, long press, return the original event. */
				result = state; 
			}
		}break;
			
		case BTN_CHECK_STATE1:
		{
			if(state == BTN_DOWN)  
			{
				result = BTN_DOUBLE;  
				buttonStep = BTN_CHECK_STATE0;				
			}
			else if((++buttonTimeCnt) >= 25)  /* 500ms */
			{					
        /* Click event does not occur again within 500ms, return click event. */				
				result = BTN_DOWN;  
				buttonStep = BTN_CHECK_STATE0;         			
			}
		}break;
		
		default:
			break;
	}
	
	return result;
}

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  button_task_timer_schedule(void)
{
	TASK_TIMER_BEGIN(buttonTaskBaseTr, TIME_MS(20));

	buttonState = button_identify();

	TASK_TIMER_END(buttonTaskBaseTr);
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  button_task_logic_schedule(void)
{		 

}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   button_task(void)	 _task_   BUTTON_TASK_PRIORITY
{  
  mcu_gpio_set_mode(BTN_PORT, BTN_PIN, BTN_MODE);	

  while(1)
	{
    button_task_timer_schedule();
		button_task_logic_schedule();	

		os_switch_task();
	}
}




/*---------------------- end of file -----------------------------------------*/



