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
static  void  mcu_uart0_timer1(u32_t u32Baudrate)    //T1M = 1, SMOD = 1
{
  P06_Quasi_Mode;	/* Setting UART pin as Quasi mode for transmit */
  P07_Quasi_Mode;	/* Setting UART pin as Quasi mode for transmit */
	
  SCON = 0x50;     	/* UART0 Mode1,REN=1,TI=1 */
  TMOD |= 0x20;    	/* Timer1 Mode1	*/
    
  set_SMOD;        	/* UART0 Double Rate Enable	*/
  set_T1M;
  clr_BRCK;        	/* Serial port 0 baud rate clock source = Timer1 */
 
  TH1 = 256 - (1000000/u32Baudrate+1);          /*16 MHz */ 	

  set_TR1;
  set_TI;		    /* For printf function must setting TI = 1 */
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
