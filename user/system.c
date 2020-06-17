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




/*-- defined -----------------------------------------------------------------*/
#define      TIME_MS(x)                 (x)

#define      SYS_POWER_PORT		          PORT0
#define      SYS_POWER_PIN							PIN3
#define      SYS_POWER_MODE							PP_MODE


/*-- private variables -------------------------------------------------------*/

static  volatile   tick_size_t DATA _sysTickCnt = 0;

static   tick_size_t XDATA systemTaskBaseTr = 0; 


#define  SYS_BROADCAST_TASK_LEN   15
static   msg_size_t  XDATA	 sysBroadcastTask[SYS_BROADCAST_TASK_LEN];
static   MsgDef      XDATA   sysBroadcastMsg;

/*-- functions ---------------------------------------------------------------*/

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
MsgDef*  get_system_broadcast_handle(void)
{
  return &sysBroadcastMsg;
}

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  system_power_on(void)
{
  mcu_gpio_write(SYS_POWER_PORT, SYS_POWER_PIN, IO_HIGH);
}

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  system_power_off(void)
{
  mcu_gpio_write(SYS_POWER_PORT, SYS_POWER_PIN, IO_LOW);
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
	XDATA MsgDef* msgHandle;

	mcu_wdt_feed();

	msgHandle = get_system_broadcast_handle();
	
	if(msg_check(msgHandle, SYSTEM_TASK_PRIORITY, SYS_RESET) == MSG_MATCH)
	{
	  //LOG("[SYS]reset anser\r\n");
	}	
	
	if(msg_check(msgHandle, SYSTEM_TASK_PRIORITY, SYS_SLEEP) == MSG_MATCH)
	{
	  //LOG("[SYS]sleep anser\r\n");
	} 

	 
}

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  system_task (void)  _task_   SYSTEM_TASK_PRIORITY
{
  mcu_clk_init(0);
	mcu_gpio_set_all_default();
	mcu_gpio_set_mode(SYS_POWER_PORT, SYS_POWER_PIN, SYS_POWER_MODE);

#if     LOG_ENABLE
  mcu_uart0_init(115200);
#endif
  
	mcu_wdt_start();
	mcu_wdt_feed();

	/* Create user task. */
	os_create_task(BUTTON_TASK_PRIORITY);
	os_create_task(LED_TASK_PRIORITY);
	os_create_task(BMS_TASK_PRIORITY);

#if  CONSOLE_ENABLE
	os_create_task(CONSOLE_TASK_PRIORITY);
#endif

	system_power_on();

	/* Task message queue create. */
	msg_create(&sysBroadcastMsg, sysBroadcastTask, SYS_BROADCAST_TASK_LEN);

	/* System task run. */
	while(1)
	{
	  system_task_timer_schedule();
		system_task_logic_schedule();

    os_switch_task();
	}
}





/*---------------------- end of file -----------------------------------------*/
