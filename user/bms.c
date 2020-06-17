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
#include "./bms.h"
#include "./led.h"
#include "./button.h"

/*-- defined -----------------------------------------------------------------*/
#define        TIME_MS(x)                 (x)


#define        VPACK_RES_SCALE                   (u32_t)13
#define        VPACK_COMPENSION                  0 //(u32_t)300  /* mV	*/


typedef  struct
{
  u8_t 	   	readDataInv;
}BmsTime;


typedef  struct
{
  u32_t 	  bandgapVolt;
	u32_t     mcuVdd;
	u32_t     battVolt;
}BmsData;


/*-- private variables -------------------------------------------------------*/
static   tick_size_t XDATA bmsTaskBaseTr = 0;

static  ButtonState  XDATA btnState = BTN_UP;

static   BmsTime  XDATA  bmsTime;
static   BmsData  XDATA  bmsData;

/*-- functions ---------------------------------------------------------------*/
static    void    bms_task_timer_schedule(void);
static    void    bms_task_logic_schedule(void);




/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  bms_task_timer_schedule(void)
{
	TASK_TIMER_BEGIN(bmsTaskBaseTr, TIME_MS(20));

	if(bmsTime.readDataInv > 0)
	{
	  bmsTime.readDataInv--;
	}

	TASK_TIMER_END(bmsTaskBaseTr);
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  bms_task_logic_schedule(void)
{
	XDATA u32_t  adcTmp = 0;
	
	btnState = button_read();

	if(bmsTime.readDataInv == 0)
	{
	  bmsTime.readDataInv = 25;

    adcTmp = mcu_adc_get(ADC_BANDGAP);
    bmsData.mcuVdd = (ADC_FULL_SCALE*bmsData.bandgapVolt/adcTmp);

		adcTmp = mcu_adc_get(ADC_CH5);   
    bmsData.battVolt = VPACK_COMPENSION + (bmsData.mcuVdd*adcTmp*VPACK_RES_SCALE)/ADC_FULL_SCALE;

		LOG("VDD=%lu mV, Bat=%lu mV\r\n", bmsData.mcuVdd, bmsData.battVolt);
	}
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   bms_task(void)	 _task_   BMS_TASK_PRIORITY
{
	bmsData.bandgapVolt = mcu_adc_read_bandgap_volt();

  while(1)
	{
	  bms_task_timer_schedule();
	  bms_task_logic_schedule(); 

		os_switch_task();
	}
}




/*---------------------- end of file -----------------------------------------*/



