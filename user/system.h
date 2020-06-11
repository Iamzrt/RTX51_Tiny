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
#ifndef    SYSTEM_H
#define    SYSTEM_H


/*-- includes  ---------------------------------------------------------------*/
#include <stdio.h>
#include "../includes/_sys_config.h"
#include "../mcu/N76E003.h"
#include "../mcu/SFR_Macro.h"
#include "../mcu/Function_define.h"

#include "../common/task_def.h"
#include "../common/ring_buffer.h"




/*-- defined  ----------------------------------------------------------------*/
typedef      u8_t                             tick_size_t;


#define      SYSTEM_TASK_PRIORITY             0
#define      BUTTON_TASK_PRIORITY             1
#define      LED_TASK_PRIORITY                2
#define      PRINT_TASK_PRIORITY              3




/*-- functions  ---------------------------------------------------------------*/
extern     tick_size_t    get_systick(void);

extern     void           mcu_reset(void);
extern     void           mcu_wdt_init(void);
extern     void           mcu_wdt_feed(void);


#endif   /* SYSTEM_H */

/*---------------------- end of file -----------------------------------------*/
