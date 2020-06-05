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
#include "./button.h"



/*-- defined -----------------------------------------------------------------*/
#define     DB_LOG(x)     LOG("[BTN]");LOG(x)





/*-- private variables -------------------------------------------------------*/



/*-- functions ---------------------------------------------------------------*/

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
//unsigned char Trg;
//unsigned char Cont;
//
//void KeyRead( void )
//{
//    unsigned char ReadData = PINB^0xff;   
//    Trg = ReadData & (ReadData ^ Cont);      
//    Cont = ReadData;                                
//}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   button_task(void)	 _task_   BUTTON_TASK_PRIORITY
{
  while(1)
	{
    os_switch_task();	
	}
}




/*---------------------- end of file -----------------------------------------*/



