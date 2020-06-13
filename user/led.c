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
#include "./print.h"


/*-- defined -----------------------------------------------------------------*/


#define        TIME_MS(x)                 (x)

																					 
#define        IO_LED1_MODE()     		     P11_PushPull_Mode
#define        IO_LED2_MODE()     		     P12_PushPull_Mode
#define        IO_LED3_MODE()     		     P13_PushPull_Mode
#define        IO_LED4_MODE()     		     P14_PushPull_Mode
																					                     

#define        LED1_ON()                   P11 = 1
#define        LED1_OFF()                	 P11 = 0
#define        LED1_TOGGLE()               P11 = !P11    

#define        LED2_ON()                   P12 = 1
#define        LED2_OFF()                	 P12 = 0
#define        LED2_TOGGLE()               P12 = !P12 

#define        LED3_ON()                   P13 = 1
#define        LED3_OFF()                	 P13 = 0
#define        LED3_TOGGLE()               P13 = !P13 

#define        LED4_ON()                   P14 = 1
#define        LED4_OFF()                	 P14 = 0
#define        LED4_TOGGLE()               P14 = !P14


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
void   led_write(LedDef led, LedWrType wr)
{
  switch(led)
	{
    case LED1:
		{
      if(wr == LED_OFF)		          LED1_OFF(); 
			else if(wr == LED_ON)		      LED1_ON();
			else if(wr == LED_TOGGLE)		  LED1_TOGGLE(); 
		}break;

    case LED2:
		{
			if(wr == LED_OFF)		          LED2_OFF(); 
			else if(wr == LED_ON)		      LED2_ON();
			else if(wr == LED_TOGGLE)		  LED2_TOGGLE();
		}break;

    case LED3:
		{
      if(wr == LED_OFF)		          LED3_OFF(); 
			else if(wr == LED_ON)		      LED3_ON();
			else if(wr == LED_TOGGLE)		  LED3_TOGGLE();		
		}break;

    case LED4:
		{
      if(wr == LED_OFF)		          LED4_OFF(); 
			else if(wr == LED_ON)		      LED4_ON();
			else if(wr == LED_TOGGLE)		  LED4_TOGGLE();		
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
  /* Led pin configure. */
  IO_LED1_MODE(); IO_LED2_MODE(); IO_LED3_MODE(); IO_LED4_MODE();

  while(1)
	{
	  led_task_timer_schedule();
	  led_task_logic_schedule();  
		
		os_switch_task(); 
	}
}




/*---------------------- end of file -----------------------------------------*/



