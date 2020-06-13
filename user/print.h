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
#ifndef    PRINT_H
#define    PRINT_H


/*-- includes  ---------------------------------------------------------------*/
#include "./system.h"



/*-- defined  ----------------------------------------------------------------*/


/*< Log configuration. >*/
#if   LOG_ENABLE
  #define         LOG              printf 
#else 
  #define         LOG 
#endif 



typedef   void  (*PrintRxCallbackFunc)(u8_t dat);



/*-- functions  ---------------------------------------------------------------*/
extern   void     print_rx_callback_register(PrintRxCallbackFunc  func);
extern   void     my_printf(char * c, ...);


#endif   /* PRINT_H */

/*---------------------- end of file -----------------------------------------*/
