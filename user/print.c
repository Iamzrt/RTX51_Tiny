/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date   
  * @brief    
              %bd              十进制有符号整数
              %bu              十进制无符号整数
              %f               浮点数
              %s               字符串
              %c               单个字符
              %p               指针的值
              %e               指数形式的浮点数
              %x, %X           无符号以十六进制表示的整数
              %0               无符号以八进制表示的整数
              %g               自动选择合适的表示法
			        %lf              表示输出double浮点数
  ******************************************************************************  
  * 
  * 
  ******************************************************************************
  */
/*-- includes ----------------------------------------------------------------*/
#include <stdarg.h>
#include "./print.h"


#if     LOG_ENABLE

/*-- defined -----------------------------------------------------------------*/




/*-- private variables -------------------------------------------------------*/
static  bit    BIT_TMP;

static    PrintRxCallbackFunc   rxCallbackPt = NULL;

/*-- functions ---------------------------------------------------------------*/


/**           
  * @brief      for UART_printf      
  * @param    
  * @return  
  * @note
  */
char putchar (char c)
{
  while (!TI);
  TI = 0;
  return (SBUF = c);
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  mcu_uart0_timer1(u32_t u32Baudrate)   
{
  clr_EA;

  P06_Quasi_Mode;	  /* Setting UART pin as Quasi mode for transmit */
  P07_Quasi_Mode;	  /* Setting UART pin as Quasi mode for transmit */
	
  SCON = 0x50;     	/* UART0 Mode1,REN=1,TI=0 */
  TMOD |= 0x20;    	/* Timer1 Mode1	*/
    
  set_SMOD;        	/* UART0 Double Rate Enable	*/
  set_T1M;
  clr_BRCK;        	/* Serial port 0 baud rate clock source = Timer1 */
 
  TH1 = 256 - (1000000/u32Baudrate+1);          /*16 MHz */ 	

	clr_ET1;
  set_TR1;					/* Enable timer1. */
	
  set_TI;		        /* For printf function must setting TI = 1 */

	set_ES;           /* Enable Uart interrupt. */
	set_EA;           /* Enable global interrupt */ 
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  uart0_interrupt_ISR(void)  interrupt  4
{
  u8_t  dat = 0;  

  /* if reception occur */
  if(RI)
	{
    clr_RI;	

		dat = SBUF;
		if(rxCallbackPt)
		{
		  rxCallbackPt(dat);
		}
	}

	 /* if transmit occur */
#if  0	   /* When use <stdio.h> printf function, this function must remove.  */
	if(TI)
	{
    clr_TI;	
	}
#endif
}



/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   print_rx_callback_register(PrintRxCallbackFunc  func)
{
  rxCallbackPt = func;
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  print_task (void)  _task_   PRINT_TASK_PRIORITY
{
#if     LOG_ENABLE
  mcu_uart0_timer1(115200);
#endif

  while(1)
	{
	  os_switch_task();
	}
}


#endif   /* endif  LOG_ENABLE */



/*---------------------- end of file -----------------------------------------*/
