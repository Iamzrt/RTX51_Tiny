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
#ifndef    MCU_H
#define    MCU_H


/*-- Conofiguration  ---------------------------------------------------------*/
//#define            PRINT_ENABLE
#define            WTD_ENABLE


/*-- includes  ---------------------------------------------------------------*/
#include <stdio.h>
#include "../../includes/_sys_std.h"
#include "../includes/N76E003.h"
#include "../includes/SFR_Macro.h"
#include "../includes/Function_define.h"



/*-- defined  ---------------------------------------------------------------*/
#ifdef        PRINT_ENABLE 
#define         LOG(x)              printf(x) 
#else 
#define         LOG(x) 
#endif  /* endif PRINT_ENABLE */



#define      ADC_FULL_SCALE         (u32_t)4095

/*-- typedef  ----------------------------------------------------------------*/
typedef  enum
{
  ADC_CH0 = (u8_t)0,
  ADC_CH1,
  ADC_CH2,
  ADC_CH3,
  ADC_CH4,
  ADC_CH5,
  ADC_CH6,
  ADC_CH7,
}AdcChannelEnum;

/*-- functions  ---------------------------------------------------------------*/
u8_t                mcu_init(void);
void                mcu_reset(void);

#ifdef   WTD_ENABLE
void                mcu_wdt_init(void);
//void                enable_wdt_reset_config(void);
//void                disable_wdt_reset_config(void);
void                mcu_feed_wdt(void);
#endif

u32_t               get_mcu_vdd_volt(void);
u32_t               get_mcu_adc(AdcChannelEnum ch);
void                mcu_goto_sleep(void);
void                mcu_exit_sleep(void);

#endif   /* MCU_H */

/*---------------------- end of file -----------------------------------------*/
