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

#include "./hal_uart.h"


#if     LOG_ENABLE

/*-- defined -----------------------------------------------------------------*/



/*-- private variables -------------------------------------------------------*/
static  bit    BIT_TMP;

static    Uart0tRxCallbackPt   ptUart0RxFunc = NULL;


/*-- functions ---------------------------------------------------------------*/


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   uart0_rx_callback_register(Uart0tRxCallbackPt  func)
{
  ptUart0RxFunc = func;
}


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
void  mcu_uart0_init(u32_t u32Baudrate)   
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
		if(ptUart0RxFunc)
		{
		  ptUart0RxFunc(dat);
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

#endif




/*---------------------- end of file -----------------------------------------*/



