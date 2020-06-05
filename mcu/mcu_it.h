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
#ifndef    MCU_IT_H
#define    MCU_IT_H


/*-- includes  ---------------------------------------------------------------*/
#include "./mcu.h"


/*-- typedef  ----------------------------------------------------------------*/
typedef    void  (*SysTickCallback)(void);
typedef    void  (*Pin0IntCallback)(void);
typedef    void  (*WtdIntCallback)(void);


/*-- functions  --------------------------------------------------------------*/
void     systick_callback_register(SysTickCallback func);
void     pin0_int_callback_register(Pin0IntCallback func);
void     wtd_int_callback_register(WtdIntCallback func);


#endif   /* MCU_IT_H */

/*---------------------- end of file -----------------------------------------*/
