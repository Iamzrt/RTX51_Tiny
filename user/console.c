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
#include <string.h>
#include "./console.h"




#if  CONSOLE_ENABLE


/*-- defined -----------------------------------------------------------------*/
#define      CONSOLE_LOG(x)								 LOG("-->"); LOG(x)

#define      RX_BUFFER_MAX_SIZE				     128


typedef  struct
{
  rb_depth_t     dealCnt;
	rb_data_type*  dealBuff;  
}ConsoleDeal;



/*-- private variables -------------------------------------------------------*/
static   rb_data_type  XDATA    conRxBuff[RX_BUFFER_MAX_SIZE];
static   rb_data_type  XDATA    conDealBuff[RX_BUFFER_MAX_SIZE];

static   RingBuffObj   XDATA    consoleRxObj;
static   ConsoleDeal   XDATA    consoleDealObj;



/*-- functions ---------------------------------------------------------------*/
static   void   console_buffer_in(u8_t dat);


/*< Add user commands. >*/
static    void    help(void);
static    void    reset(void);
static    void    sleep(void);

ConsoleItemDef  CODE cmdList[] = 
{
  { "?HELP",            "--Lists all user commands",       help              },
  { "?RESET",           "--Reset system",                  reset             },
	{ "?SLEEP",           "--System goto sleep",             sleep             },
};

#define   CONSOLE_CMD_SIZE   sizeof(cmdList)/sizeof(ConsoleItemDef)




/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static   void   console_buffer_in(u8_t dat)
{
  put_ring_buff_data(&consoleRxObj, dat);
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  console_analysis(void)
{
  rb_depth_t XDATA remain = 0;
	u8_t XDATA step = 0;
	rb_data_type XDATA dat = 0;
	u8_t XDATA i = 0;

	remain = check_ring_buff(&consoleRxObj);
  if(remain)
	{
    while(remain--)
		{
		  dat = get_ring_buff_data(&consoleRxObj);

      switch(step)
			{
			  case 0:
				{
				  if(dat == '?')
					{		
					  consoleDealObj.dealCnt = 0;
						consoleDealObj.dealBuff[consoleDealObj.dealCnt++] = dat;
					  step = 1;
					}
				}break;

				case 1:
				{
					if(dat == '\n')
					{		
					  /* Check Whether to contain substrings. */
						for(i=0; i<CONSOLE_CMD_SIZE; i++)
						{
					    if(strstr(consoleDealObj.dealBuff, cmdList[i].name))
						  {
							  /* Cmd matching. */
						    cmdList[i].call();
								break;
						  }
						}												
					}	

					consoleDealObj.dealBuff[consoleDealObj.dealCnt++] = dat;		
				}break;

				default:
				  break;
			} 		
		} 	
	} 
}

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  console_task_timer_schedule(void)
{

}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  console_task_logic_schedule(void)
{
  XDATA MsgDef* msgHandle;

  console_analysis();
	
	msgHandle = get_system_broadcast_handle();
	
	if(msg_check(msgHandle, CONSOLE_TASK_PRIORITY, SYS_RESET) == MSG_MATCH)
	{
	  //LOG("-->reset anser\r\n");
	}	
	
	if(msg_check(msgHandle, CONSOLE_TASK_PRIORITY, SYS_SLEEP) == MSG_MATCH)
	{
	  //LOG("-->sleep anser\r\n");
	}   
}

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  console_task (void)  _task_   CONSOLE_TASK_PRIORITY
{
	ring_buff_create(&consoleRxObj, RX_BUFFER_MAX_SIZE, conRxBuff);

	consoleDealObj.dealCnt  = 0;
	consoleDealObj.dealBuff = conDealBuff;

	uart0_rx_callback_register(console_buffer_in);

  while(1)
	{
	  console_task_timer_schedule();
	  console_task_logic_schedule();
		
		os_switch_task();																 
	}
}


/*-- commands -----------------------------------------------------------------*/
static  void  help(void)
{
  u8_t XDATA i = 0;

  LOG("\r\n/*----------------------- Cmd List -------------------------*/\r\n");
	for(i=0; i<CONSOLE_CMD_SIZE; i++)
  {
    LOG("[%bu]   %s\t%s\r\n", i, cmdList[i].name, cmdList[i].brief);    
  }		
}

static  void  reset(void)
{				
	XDATA MsgDef* msgHandle;

	msgHandle = get_system_broadcast_handle();
  msg_broadcast(msgHandle, SYS_RESET);
	LOG("-->reset notify\r\n");
}

static  void  sleep(void)
{	
  XDATA MsgDef*  msgHandle;

	msgHandle = get_system_broadcast_handle();
  msg_broadcast(msgHandle, SYS_SLEEP);
  LOG("-->sleep notify\r\n");
}

#endif   /* endif CONSOLE_ENABLE */

/*---------------------- end of file -----------------------------------------*/
