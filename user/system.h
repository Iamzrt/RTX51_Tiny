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
#include "../mcu/hal_core.h"

#include "../common/task_def.h"
#include "../common/ring_buffer.h"
#include "../common/msg.h"



/*-- defined  ----------------------------------------------------------------*/
typedef      u8_t                             tick_size_t;


#define      SYSTEM_TASK_PRIORITY             0
#define      BUTTON_TASK_PRIORITY             1
#define      LED_TASK_PRIORITY                2
#define      BMS_TASK_PRIORITY								3
#define      CONSOLE_TASK_PRIORITY            4


typedef  enum
{
  SYS_RESET         = (msg_size_t)1,
	SYS_POWER_DOWN    = (msg_size_t)2,
	SYS_IDLE          = (msg_size_t)3,
	SYS_SLEEP         = (msg_size_t)4,
}SysMsgType;


/*< Log configuration. >*/
/** 
	%bd              十进制有符号整数(signed char)
	%bu              十进制无符号整数(unsigned char)
	%lu              十进制无符号整数(unsigned long)
	%f               浮点数
	%s               字符串
	%c               单个字符
	%p               指针的值
	%e               指数形式的浮点数
	%x, %X           无符号以十六进制表示的整数
	%0               无符号以八进制表示的整数
	%g               自动选择合适的表示法
	%lf              表示输出double浮点数
  */
#if   LOG_ENABLE
  #define         LOG              printf 
#else 
  #define         LOG 
#endif 



/*-- functions  ---------------------------------------------------------------*/
extern     tick_size_t    get_systick(void);
extern     MsgDef*        get_system_broadcast_handle(void);

extern     void           system_power_on(void);
extern     void           system_power_off(void);


#endif   /* SYSTEM_H */

/*---------------------- end of file -----------------------------------------*/
