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
#ifndef    HAL_CORE_H
#define    HAL_CORE_H


/*-- includes  ---------------------------------------------------------------*/
#include "../includes/_sys_config.h"

#include "./hal_clk.h"
#include "./hal_adc.h"
#include "./hal_gpio.h"
#include "./hal_uart.h"
#include "./hal_wtd.h"
#include "./hal_timer.h"

/*-- defined  ----------------------------------------------------------------*/





/*-- functions  ---------------------------------------------------------------*/
extern     void           mcu_reset(void);
extern     void           mcu_power_down(void);




#endif   /* HAL_CORE_H */

/*---------------------- end of file -----------------------------------------*/
