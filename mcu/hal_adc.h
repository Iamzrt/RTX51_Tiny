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
#ifndef    HAL_ADC_H
#define    HAL_ADC_H


/*-- includes  ---------------------------------------------------------------*/
#include "../includes/_sys_config.h"



/*-- defined  ----------------------------------------------------------------*/
#define      ADC_FULL_SCALE         (u32_t)4095


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
	ADC_BANDGAP,
}AdcChannelEnum;




/*-- functions  ---------------------------------------------------------------*/
extern   u32_t   mcu_adc_read_bandgap_volt(void);
extern   u32_t   mcu_adc_get(AdcChannelEnum ch);




#endif   /* HAL_ADC_H */

/*---------------------- end of file -----------------------------------------*/
