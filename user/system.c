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
#include "./system.h"
#include "./led.h"
#include "./button.h"
#include "./print.h"


/*-- defined -----------------------------------------------------------------*/
#define      DB_LOG(x)             LOG("[SYS]");LOG(x)

#define      TIME_MS(x)                 (x)


/*-- private variables -------------------------------------------------------*/
static  bit    BIT_TMP;

static  volatile   tick_size_t DATA _sysTickCnt = 0;

static   tick_size_t XDATA systemTaskBaseTr = 0; 


/*-- functions ---------------------------------------------------------------*/
static    void    mcu_clk_init(void);

static    void    system_task_timer_schedule(void);
static    void    system_task_logic_schedule(void);



/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   _systick_increase(void)
{
  _sysTickCnt++;
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
u8_t   get_systick(void)
{
  return  _sysTickCnt;
}


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
void   mcu_wdt_init(void)
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

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   mcu_gpio_all_deinit(void)
{
  Set_All_GPIO_Quasi_Mode;
}


/**           
  * @brief   HIRC enable         
  * @param    
  * @return  
  * @note	   MCU power on system clock is HIRC (16 MHz).
             Please keep P3.0 HIGH before you want to modify Fsys to LIRC.
  */
static   void  mcu_clk_init(void)
{
  clr_EA;				         /* disable interrupts*/

  set_HIRCEN;  /* HIRC 16MHz */
  while((CKSWT&SET_BIT5)==0);				/* check ready */
  clr_OSC1;
  clr_OSC0;
  while((CKEN&SET_BIT0)==1);				/* check system clock switching OK or NG */

	set_EA;                        /* enable interrupts*/
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */ 
static  void  system_task_timer_schedule(void)
{
	TASK_TIMER_BEGIN(systemTaskBaseTr, TIME_MS(100));



	TASK_TIMER_END(systemTaskBaseTr);
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  system_task_logic_schedule(void)
{		 
  mcu_wdt_feed();	


}

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  system_task (void)  _task_   SYSTEM_TASK_PRIORITY
{
  mcu_clk_init();
	mcu_gpio_all_deinit();

	mcu_wdt_init();
	mcu_wdt_feed();

	os_create_task(BUTTON_TASK_PRIORITY);
	os_create_task(LED_TASK_PRIORITY);
	os_create_task(PRINT_TASK_PRIORITY);
	os_create_task(CONSOLE_TASK_PRIORITY);

	DB_LOG("System init finish.\r\n");

	while(1)
	{
	  system_task_timer_schedule();
		system_task_logic_schedule();
	}
}





/*---------------------- end of file -----------------------------------------*/
