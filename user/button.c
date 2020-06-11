/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date   
  * @brief   	 Support 8 buttons.
  ******************************************************************************  
  * 
  * 
  ******************************************************************************
  */
/*-- includes ----------------------------------------------------------------*/
#include "./button.h"
#include "./led.h"


/*-- defined -----------------------------------------------------------------*/
#define        DB_LOG(x)                  LOG("[BTN]");LOG(x)
#define        TIME_MS(x)                 (x)



#define        IO_BTN1_MODE()     		      P30_Input_Mode


/*< User defined. Max button = 8. 0: not use. >*/
#define        GET_BTN1_STATE()                 P30
#define        GET_BTN2_STATE()                 0
#define        GET_BTN3_STATE()                 0
#define        GET_BTN4_STATE()                 0
#define        GET_BTN5_STATE()                 0
#define        GET_BTN6_STATE()                 0
#define        GET_BTN7_STATE()                 0
#define        GET_BTN8_STATE()                 0



typedef   struct
{
  u8_t    currState;
  u8_t    lastState;
  u8_t    trigDown;
	u8_t    trigUp;
	u8_t    prevTrig;
}BtnDetectDef;


/*-- private variables -------------------------------------------------------*/
static   tick_size_t  XDATA  buttonTaskBaseTr = 0;

static   BtnDetectDef  XDATA    buttonList;



/*-- functions ---------------------------------------------------------------*/
static    void    button_task_timer_schedule(void);
static    void    button_task_logic_schedule(void);


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */ 
static  void  read_button_status(BtnDetectDef* ptBtn, u8_t  buttonArray)
{
  ptBtn->lastState = ptBtn->currState;
	ptBtn->currState = buttonArray^0xff;			/* reverse */
	
	if(ptBtn->lastState ^ ptBtn->currState)
	{
	  /* Filt pulse. */
	  return;
	} 
	else
	{
	  ptBtn->trigDown = ptBtn->currState & (ptBtn->currState ^ ptBtn->prevTrig); /* button down, trig once. */
	  //ptBtn->trigUp = ptBtn->prevTrig & (ptBtn->currState ^ ptBtn->prevTrig);	   /* button up, trig once. */
	  ptBtn->prevTrig = ptBtn->currState;
	}                            
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  button_task_timer_schedule(void)
{
  u8_t XDATA  buttonArray = 0; 
	u8_t XDATA  ioState = 0;

	TASK_TIMER_BEGIN(buttonTaskBaseTr, TIME_MS(20));

	/* Read IO state. */
	ioState = GET_BTN1_STATE();
	buttonArray |= (ioState << 0);
	ioState = GET_BTN2_STATE();
	buttonArray |= (ioState << 1);
	ioState = GET_BTN3_STATE();
	buttonArray |= (ioState << 2);
	ioState = GET_BTN4_STATE();
	buttonArray |= (ioState << 3);
	ioState = GET_BTN5_STATE();
	buttonArray |= (ioState << 4);
	ioState = GET_BTN6_STATE();
	buttonArray |= (ioState << 5);
	ioState = GET_BTN7_STATE();
	buttonArray |= (ioState << 6);
	ioState = GET_BTN8_STATE();
	buttonArray |= (ioState << 7);
  read_button_status(&buttonList, buttonArray);

	/* Button 1 trig action. */
	if(buttonList.trigDown & (1<<0)) 
	{
	 	LED1_TOGGLE();
	}

	/* Button 2 trig action. */
	if(buttonList.trigDown & (1<<1)) 
	{
	  
	}

	/* Button 3 trig action. */
	if(buttonList.trigDown & (1<<2)) 
	{
	  
	}

  /* Button 4 trig action. */
	if(buttonList.trigDown & (1<<3)) 
	{
	  
	}

	/* Button 5 trig action. */
	if(buttonList.trigDown & (1<<4)) 
	{

	}

	/* Button 6 trig action. */
	if(buttonList.trigDown & (1<<5)) 
	{

	}

	/* Button 7 trig action. */
	if(buttonList.trigDown & (1<<6)) 
	{

	}

	/* Button 8 trig action. */
	if(buttonList.trigDown & (1<<7)) 
	{

	}

	TASK_TIMER_END(buttonTaskBaseTr);
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  button_task_logic_schedule(void)
{		 
	


}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void   button_task(void)	 _task_   BUTTON_TASK_PRIORITY
{  
  /* Button pin configuration. */
  IO_BTN1_MODE();

  while(1)
	{
    button_task_timer_schedule();
		button_task_logic_schedule();
	}
}




/*---------------------- end of file -----------------------------------------*/



