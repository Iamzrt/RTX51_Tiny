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
#ifndef    HAL_GPIO_H
#define    HAL_GPIO_H


/*-- includes  ---------------------------------------------------------------*/
#include "../includes/_sys_config.h"



/*-- defined  ----------------------------------------------------------------*/
/*< IO defined. >*/
typedef  enum
{
  PORT0 = 0,
	PORT1,
	PORT2,
	PORT3,
}GpioPort;

typedef  enum
{
  PIN0 = 0,
  PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}GpioPin;


/*< IO level defined. >*/
typedef  enum
{
  IO_LOW = 0,
	IO_HIGH,
}GpioLevel;


/*< IO mode defined. >*/
typedef  enum
{
  QUASI_MODE,
	PP_MODE,
	INPUT_MODE,
	OD_MODE,
}GpioMode;


/*< IO interrupt trig type defined. >*/
typedef  enum
{
  LEVEL_TRIG,
	EDGE_TRIG,
}GpioTrig;


/*< IO interrupt phase type defined. >*/
typedef  enum
{
  RISING_H_TRIG,
	FALLING_L_TRIG,
}GpioTrigPhase;


/*-- functions  ---------------------------------------------------------------*/
extern     void           mcu_gpio_set_all_default(void);

extern     void           mcu_gpio_write(GpioPort port, GpioPin pin, \
                                         GpioLevel level);
extern     GpioLevel      mcu_gpio_read(GpioPort port, GpioPin pin);
extern     void           mcu_gpio_set_mode(GpioPort port, GpioPin pin, \
                                            GpioMode mode);


#endif   /* HAL_GPIO_H */

/*---------------------- end of file -----------------------------------------*/
