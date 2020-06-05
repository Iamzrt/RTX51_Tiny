/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date   
  * @brief    
              %d               十进制有符号整数
              %u               十进制无符号整数
              %f               浮点数
              %s               字符串
              %c               单个字符
              %p               指针的值
              %e               指数形式的浮点数
              %x, %X           无符号以十六进制表示的整数
              %0               无符号以八进制表示的整数
              %g               自动选择合适的表示法
			  %lf              表示输出double浮点数
  ******************************************************************************  
  * 
  * 
  ******************************************************************************
  */
/*-- includes ----------------------------------------------------------------*/
#include "./mcu.h"

/*-- defined -----------------------------------------------------------------*/
#define      DB_LOG(x)     LOG("[MCU]");LOG(x)

#define      ADC_FILTER_NUM    32
#define      ADC_START_POS     20

static  bit    BIT_TMP;

#define set_IAPEN BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON|=SET_BIT0 ;EA=BIT_TMP
#define set_IAPGO BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPTRG|=SET_BIT0 ;EA=BIT_TMP
#define clr_IAPEN BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON&=~SET_BIT0;EA=BIT_TMP

#define     CFG_READ            0xC0
#define     CFG_ERASE           0xE2
#define     CFG_BYTE_PROGRAM    0xE1

#define			READ_UID					  0x04


/*-- private variables -------------------------------------------------------*/
static    u32_t   bandgapVolt;
		
u8_t XDATA ADCdataH[ADC_FILTER_NUM+ADC_START_POS], ADCdataL[ADC_FILTER_NUM+ADC_START_POS];



/*-- functions ---------------------------------------------------------------*/
static    void     mcu_clk_init(void);
static    void     mcu_gpio_init(void);
//static    void     mcu_gpio_deinit(void);
static    void     mcu_time3_init(u16_t period);

#ifdef        PRINT_ENABLE 
static    void     mcu_uart0_timer1(u32_t u32Baudrate);
#endif

static    u32_t   read_bandgap(void);


#ifdef        PRINT_ENABLE 
/**           
  * @brief      for UART_printf      
  * @param    
  * @return  
  * @note
  */
char putchar (char c)
{
  while (!TI);
  TI = 0;
  return (SBUF = c);
}

#endif


/**           
  * @brief          
  * @param    
  * @return  
  * @note
  */
void  mcu_reset(void)
{
  TA = 0xAA;
  TA = 0x55;
  set_SWRST;
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
u8_t    mcu_init(void)
{
  clr_EA;				         /* disable interrupts*/

  mcu_clk_init();

  mcu_gpio_init();
  mcu_time3_init(1000);			 /* 1ms */

#ifdef        PRINT_ENABLE
  mcu_uart0_timer1(115200);
#endif

  bandgapVolt =  read_bandgap();
//  printf("Bandgap=%ld\r\n", bandgapVolt);

  set_EA;                        /* enable interrupts*/

  return 1;
}


/**           
  * @brief   HIRC enable         
  * @param    
  * @return  
  * @note	 MCU power on system clock is HIRC (16 MHz).
             Please keep P3.0 HIGH before you want to modify Fsys to LIRC.
  */
static   void  mcu_clk_init(void)
{
  set_HIRCEN;  /* HIRC 16MHz */
  while((CKSWT&SET_BIT5)==0);				/* check ready */
  clr_OSC1;
  clr_OSC0;
  while((CKEN&SET_BIT0)==1);				/* check system clock switching OK or NG */
}


#ifdef       WTD_ENABLE
/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   mcu_wdt_init(void)
{
  TA=0xAA; 
  TA=0x55; 
  WDCON|=0x07;					                    /* Setting WDT prescale,1.638 s */

  set_WDTR;              /* WDT run */
  set_WDCLR;             /* Clear WDT timer	*/
  set_EWDT;				 /* Enable wdt interrupt. */
}



/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   mcu_feed_wdt(void)
{
  set_WDCLR;
}

#endif


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static   void  mcu_gpio_init(void)
{
  Set_All_GPIO_Quasi_Mode;

  /* Power lock pin. */
  P03_PushPull_Mode;
	P03 = 0;

  /* Key pin. */
  P30_Input_Mode;

  /* AD pin. */
  P04_Input_Mode;
  //P05_OpenDrain_Mode;//P05_Input_Mode;
  //P05 = 1;
  set_P04DIDS;           /* Close digital input buffer. 关闭数字输入缓冲区 */
  //set_P05DIDS;

  /* Led pin. */
  P11 = 0;
  P12 = 0;
  P13 = 0;
  P14 = 0;
  P11_PushPull_Mode;
  P12_PushPull_Mode;
  P13_PushPull_Mode;
  P14_PushPull_Mode;
}



/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static    void    mcu_time3_init(u16_t period)
{
  /* Timer prescale. 
     000=1/1
	 001=1/2
	 010=1/4
	 011=1/8
	 100=1/16	   V
	*/
  set_T3PS2;
  clr_T3PS1;
  clr_T3PS0;

  RH3 = (65536-period)/256;                   /* initial counter values */
  RL3 = (65536-period)%256;  

  set_ET3;                                    /* enable Timer3 interrupt*/
  set_TR3;                                    /* Timer3 run	*/
}


/**           
  * @brief          
  * @param    
  * @return  
  * @note
  */
static  u32_t   read_bandgap(void)
{
  XDATA u8_t   bandgapHigh = 0;
  XDATA u8_t   bandgapLow = 0;
  XDATA u8_t   bandgapMark = 0;
  XDATA u32_t bandgapValue,bandgapVoltageTemp;
  XDATA u32_t retValue;
	
  set_IAPEN;	       /* Enable IAPEN */
  IAPCN = READ_UID;	   /* READ_UID = 0x04 */
  IAPAL = 0x0d;
  IAPAH = 0x00;
  set_IAPGO;		   /* Trig set IAPGO */
  bandgapLow = IAPFD;
  bandgapMark = bandgapLow&0xF0;
	
  if (bandgapMark==0x80)
  {
    bandgapLow = bandgapLow&0x0F;
    IAPAL = 0x0C;
    IAPAH = 0x00;
    set_IAPGO;
    bandgapHigh = IAPFD;		   
    bandgapValue = (bandgapHigh<<4)+bandgapLow;
    bandgapVoltageTemp = (bandgapValue*100)*3/4/100;
    retValue = bandgapVoltageTemp - 33;			/* the actually banggap voltage value is similar this value. */
  }
  else if (bandgapMark==0x00)
  {
    bandgapLow = bandgapLow&0x0F;
    IAPAL = 0x0C;
    IAPAH = 0x00;
    set_IAPGO;
    bandgapHigh = IAPFD;
    bandgapValue = (bandgapHigh<<4)+bandgapLow;
    retValue = (bandgapValue*100)*3/4/100;
  }
  else if (bandgapMark==0x90)
  {
    IAPAL = 0x0E;
    IAPAH = 0x00;
    set_IAPGO;
    bandgapHigh = IAPFD;
    IAPAL = 0x0F;
    IAPAH = 0x00;
    set_IAPGO;
    bandgapLow = IAPFD;		    /* Trig set IAPGO */
    bandgapLow = bandgapLow&0x0F;
    bandgapValue = (bandgapHigh<<4)+bandgapLow;
    retValue = (bandgapValue*100)*3/4/100;
  }

  clr_IAPEN;

  return retValue;
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
u32_t    get_mcu_vdd_volt(void)
{
  XDATA u8_t  i  = 0;
  XDATA u8_t  adcavgH = 0;
  XDATA u8_t  adcavgL = 0;
  XDATA u32_t adcSumH = 0; 
  XDATA u32_t adcSumL = 0; 
  XDATA u32_t adcSum=0;
  XDATA u32_t bgvalue = 0;
  XDATA u32_t vddVolt = 0;

  Enable_ADC_BandGap;										
  CKDIV = 0x02;			/* IMPORTANT!! Modify system clock to 4MHz ,then add the ADC sampling clock base to add the sampling timing. */

  for(i=0; i<(ADC_FILTER_NUM+ADC_START_POS); i++)	/* All following ADC detect timing is 200uS run under 4MHz.	*/
  {
    clr_ADCF;
    set_ADCS;																
    while(ADCF == 0);
    ADCdataH[i] = ADCRH;
    ADCdataL[i] = ADCRL;
  }	
  	
  CKDIV = 0x00;			/* After ADC sampling, modify system clock back to 16MHz to run next code. */
  Disable_ADC;

  for(i=ADC_START_POS; i<(ADC_FILTER_NUM+ADC_START_POS); i++)	/* use the last 3 times data to make average  */
  {
    adcSumH =  ADCdataH[i];
		adcSumH = (adcSumH <<4);
		adcSumH =  adcSumH + ADCdataL[i];
    adcSum  =  adcSum + adcSumH;
  }				
  bgvalue = adcSum/ADC_FILTER_NUM;
	
  vddVolt =  (ADC_FULL_SCALE*bandgapVolt/bgvalue);
  //printf ("\n bgvalue = %ld\n", bgvalue); 
  //Timer0_Delay1ms(500);
  adcSumH = 0;
  adcSum = 0; 

  return vddVolt;
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
u32_t    get_mcu_adc(AdcChannelEnum ch)
{
  XDATA u8_t  i = 0;
  XDATA u8_t  adcavgH = 0;
  XDATA u8_t  adcavgL = 0;
  XDATA u32_t value = 0;
  XDATA u32_t adcSumH=0; 
  XDATA u32_t adcSumL=0;
  XDATA u32_t adcSum=0;

  CKDIV = 0x02;	/* IMPORTANT!! Modify system clock to 4MHz ,then add the ADC sampling clock base to add the sampling timing. */
  switch(ch)
  {
    default:
      break;
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
  }

  for(i=0; i<(ADC_FILTER_NUM+ADC_START_POS); i++)	/* All following ADC detect timing is 200uS run under 4MHz.	*/
  {
    clr_ADCF;
    set_ADCS;																
    while(ADCF == 0);
    ADCdataH[i] = ADCRH;
    ADCdataL[i] = ADCRL;
  }
  	
  CKDIV = 0x00;			/* After ADC sampling, modify system clock back to 16MHz to run next code. */
  Disable_ADC;

  adcSumH = 0;
  adcSumL = 0; 

  for(i=ADC_START_POS; i<(ADC_FILTER_NUM+ADC_START_POS); i++)	/* use the last 3 times data to make average  */
  {
    adcSumH = ADCdataH[i];
    adcSumH = (adcSumH<<4);
    adcSumH = adcSumH + ADCdataL[i];
    adcSum = adcSum + adcSumH;
  }	  			
  value = adcSum/ADC_FILTER_NUM;

 
  return value;
}


#ifdef        PRINT_ENABLE

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  mcu_uart0_timer1(u32_t u32Baudrate)    //T1M = 1, SMOD = 1
{
  P06_Quasi_Mode;	/* Setting UART pin as Quasi mode for transmit */
  P07_Quasi_Mode;	/* Setting UART pin as Quasi mode for transmit */
	
  SCON = 0x50;     	/* UART0 Mode1,REN=1,TI=1 */
  TMOD |= 0x20;    	/* Timer1 Mode1	*/
    
  set_SMOD;        	/* UART0 Double Rate Enable	*/
  set_T1M;
  clr_BRCK;        	/* Serial port 0 baud rate clock source = Timer1 */
 
#ifdef FOSC_160000
  TH1 = 256 - (1000000/u32Baudrate+1);              /*16 MHz */
#endif    	
#ifdef FOSC_166000
  TH1 = 256 - (1037500/u32Baudrate);         		/*16.6 MHz */
#endif

  set_TR1;
  set_TI;		    /* For printf function must setting TI = 1 */
}
#endif


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  mcu_goto_sleep(void)
{
#ifdef       WTD_ENABLE
  mcu_feed_wdt();
  clr_WDTEN;
  //disable_wdt_reset_config();
#endif

  set_PIPS1;  /* Select P3 port */
  set_PIPS0;  
  Enable_BIT0_FallEdge_Trig; /* P3.0 fallEdge trig. */
  PIF = 0;
  set_EPI;   /* Enable pin interrupt. 开启管脚中断使能 */

  clr_ET3;   /* disable Timer3 interrupt*/
  clr_TR3;   /* Timer3 stop	*/
  clr_TF3;

  clr_BODEN; /* Disable under volt detect.关闭欠压检测 */
  set_PD;    /* Enter power down mode. 进入掉电模式 */
}
 
void  mcu_exit_sleep(void)
{
  clr_EPI;   /* Disable pin interrupt. 关闭管脚中断使能 */
  PIF = 0;

  clr_TF3;
  set_ET3;                                    /* enable Timer3 interrupt*/
  set_TR3;                                    /* Timer3 run	*/

#ifdef       WTD_ENABLE
  //enable_wdt_reset_config();
  mcu_feed_wdt();
  set_WDTR;
#endif
}

/*---------------------- end of file -----------------------------------------*/
