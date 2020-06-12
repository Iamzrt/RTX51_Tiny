/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date   
  * @brief    
              %d               ʮ�����з�������
              %u               ʮ�����޷�������
              %f               ������
              %s               �ַ���
              %c               �����ַ�
              %p               ָ���ֵ
              %e               ָ����ʽ�ĸ�����
              %x, %X           �޷�����ʮ�����Ʊ�ʾ������
              %0               �޷����԰˽��Ʊ�ʾ������
              %g               �Զ�ѡ����ʵı�ʾ��
			        %lf              ��ʾ���double������
  ******************************************************************************  
  * 
  * 
  ******************************************************************************
  */
/*-- includes ----------------------------------------------------------------*/
#include "./print.h"


/*-- defined -----------------------------------------------------------------*/
#define      DB_LOG(x)             LOG("[PRINTF]");LOG(x)




/*-- private variables -------------------------------------------------------*/
static  bit    BIT_TMP;



/*-- functions ---------------------------------------------------------------*/
#if     LOG_ENABLE


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
	  if(dat == 0xAA)  P12 = !P12;
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

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  printf_task (void)  _task_   PRINT_TASK_PRIORITY
{
#if     LOG_ENABLE
  mcu_uart0_timer1(115200);
#endif

  while(1)
	{
	
	}
}

/*---------------------- end of file -----------------------------------------*/
