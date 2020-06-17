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
#include <stdio.h>

#include "./lib/N76E003.h"
#include "./lib/SFR_Macro.h"
#include "./lib/Function_define.h"

#include "./hal_adc.h"


/*-- defined -----------------------------------------------------------------*/
#define			 READ_UID					    0x04

#define      ADC_FILTER_NUM       8
#define      ADC_START_POS        6


#define      set_IAPEN      BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON|=SET_BIT0 ;EA=BIT_TMP
#define      set_IAPGO      BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPTRG|=SET_BIT0 ;EA=BIT_TMP
#define      clr_IAPEN      BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON&=~SET_BIT0;EA=BIT_TMP


/*-- private variables -------------------------------------------------------*/
static  bit    BIT_TMP;


static u8_t XDATA  adcDataH[ADC_FILTER_NUM+ADC_START_POS]; 
static u8_t XDATA  adcDataL[ADC_FILTER_NUM+ADC_START_POS];

/*-- functions ---------------------------------------------------------------*/

/**           
  * @brief          
  * @param    
  * @return  
  * @note
  */
u32_t   mcu_adc_read_bandgap_volt(void)
{
  XDATA u8_t   bgHigh = 0;
  XDATA u8_t   bgLow = 0;
  XDATA u8_t   bgMark = 0;
  XDATA u32_t  bgValue = 0;
	XDATA u32_t  bgVoltTmp = 0;
  XDATA u32_t  ret;
	
  set_IAPEN;	         /* Enable IAPEN */
  IAPCN = READ_UID;	   /* READ_UID = 0x04 */
  IAPAL = 0x0d;
  IAPAH = 0x00;
  set_IAPGO;		      /* Trig set IAPGO */
  bgLow = IAPFD;
  bgMark = bgLow&0xF0;
	
  if (bgMark==0x80)
  {
    bgLow = bgLow&0x0F;
    IAPAL = 0x0C;
    IAPAH = 0x00;
    set_IAPGO;
    bgHigh = IAPFD;		   
    bgValue = (bgHigh<<4)+bgLow;
    bgVoltTmp = (bgValue*100)*3/4/100;
    ret = bgVoltTmp - 33;			/* the actually banggap voltage value is similar this value. */
  }
  else if (bgMark==0x00)
  {
    bgLow = bgLow&0x0F;
    IAPAL = 0x0C;
    IAPAH = 0x00;
    set_IAPGO;
    bgHigh = IAPFD;
    bgValue = (bgHigh<<4)+bgLow;
    ret = (bgValue*100)*3/4/100;
  }
  else if (bgMark==0x90)
  {
    IAPAL = 0x0E;
    IAPAH = 0x00;
    set_IAPGO;
    bgHigh = IAPFD;
    IAPAL = 0x0F;
    IAPAH = 0x00;
    set_IAPGO;
    bgLow = IAPFD;		    /* Trig set IAPGO */
    bgLow = bgLow&0x0F;
    bgValue = (bgHigh<<4)+bgLow;
    ret = (bgValue*100)*3/4/100;
  }

  clr_IAPEN;

  return ret;
}




/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
u32_t   mcu_adc_get(AdcChannelEnum ch)
{
  XDATA u8_t  i = 0;
  XDATA u8_t  adcavgH = 0;
  XDATA u8_t  adcavgL = 0;
  XDATA u32_t value = 0;
  XDATA u32_t adcSumH=0; 
  XDATA u32_t adcSumL=0;
  XDATA u32_t adcSum=0;

	/* IMPORTANT!! Modify system clock to 4MHz ,then add the ADC sampling clock base to add the sampling timing. */
  CKDIV = 0x02;	

  switch(ch)
  {
    case ADC_CH0:
    {
      Enable_ADC_AIN0;
    }break;

    case ADC_CH1:
    {
	    Enable_ADC_AIN1;
	  }break;

	  case ADC_CH2:
	  {
	    Enable_ADC_AIN2;
	  }break;

	  case ADC_CH3:
	  {
	    Enable_ADC_AIN3;
	  }break;

	  case ADC_CH4:
	  {
	    Enable_ADC_AIN4;
	  }break;

	  case ADC_CH5:
	  {
	    Enable_ADC_AIN5;
	  }break;

	  case ADC_CH6:
	  {
	    Enable_ADC_AIN6;
	  }break;

	  case ADC_CH7:
	  {
	    Enable_ADC_AIN7;
	  }break;

		case ADC_BANDGAP:
		{
			Enable_ADC_BandGap;
		}break;

		default:
      break;
  }

	/* All following ADC detect timing is 200uS run under 4MHz.	*/
  for(i=0; i<(ADC_FILTER_NUM+ADC_START_POS); i++)	
  {
    clr_ADCF;
    set_ADCS;																
    while(ADCF == 0);
    adcDataH[i] = ADCRH;
    adcDataL[i] = ADCRL;
  }
  
	/* After ADC sampling, modify system clock back to 16MHz to run next code. */	
  CKDIV = 0x00;			
  Disable_ADC;

  adcSumH = 0;
  adcSumL = 0; 

	/* use the last 3 times data to make average  */
  for(i=ADC_START_POS; i<(ADC_FILTER_NUM+ADC_START_POS); i++)	
  {
    adcSumH = adcDataH[i];
    adcSumH = (adcSumH<<4);
    adcSumH = adcSumH + adcDataL[i];
    adcSum = adcSum + adcSumH;
  }	  	
			
  value = adcSum/ADC_FILTER_NUM;
 
  return value;
}



/*---------------------- end of file -----------------------------------------*/



