/**
  ******************************************************************************
  * @file    			main.c
  * @author  			ZRT
  * @version 		  V1.0
  * @date   			20200605
  * @brief   
  ******************************************************************************  
  * 
  * 
  ******************************************************************************
  */
/*-- includes ----------------------------------------------------------------*/
#include "./main.h"
#include "./led.h"
#include "./button.h"
			

/*-- defined -----------------------------------------------------------------*/
#define          DB_LOG(x)         LOG("[MAIN]");LOG(x)


/*-- private variables -------------------------------------------------------*/
static  volatile   u8_t  DATA _sysTickCnt = 0;   


/*-- functions ---------------------------------------------------------------*/
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
void  startup_task (void)  _task_  STARTUP_TASK_PRIORITY
{
  os_create_task (BUTTON_TASK_PRIORITY);     /* Create button Task */
	os_create_task (LED_TASK_PRIORITY);        /* Create led Task */

  os_delete_task (STARTUP_TASK_PRIORITY);    /* Delete the Startup Task */
}


/*---------------------- end of file -----------------------------------------*/



