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
	%bd              ʮ�����з�������(signed char)
	%bu              ʮ�����޷�������(unsigned char)
	%lu              ʮ�����޷�������(unsigned long)
	%f               ������
	%s               �ַ���
	%c               �����ַ�
	%p               ָ���ֵ
	%e               ָ����ʽ�ĸ�����
	%x, %X           �޷�����ʮ�����Ʊ�ʾ������
	%0               �޷����԰˽��Ʊ�ʾ������
	%g               �Զ�ѡ����ʵı�ʾ��
	%lf              ��ʾ���double������
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
