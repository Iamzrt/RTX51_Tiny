/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date   
  * @brief   os_switch_task() 	
	            --When TIMESHARING=0, it must call this function to switch task.
  ******************************************************************************  
  * 
  * 
  ******************************************************************************
  */
#ifndef    TASK_DEF_H
#define    TASK_DEF_H


/*-- includes  ---------------------------------------------------------------*/
#include "../includes/_sys_config.h"

#include <rtx51tny.h>


/*-- defined  ----------------------------------------------------------------*/
/*< User defined. >*/
#define      GET_SYS_TICK()			              get_systick()



/*< Task run period. >*/
#define      TASK_PERIOD                      TIMESHARING



/*< Task timer defined. >*/
#define      TASK_TIMER_BEGIN(tick, period)		                                 \
             do{                                                               \
                 if((GET_SYS_TICK()-tick) >= period)                           \
								 {                                                             \
									 tick = GET_SYS_TICK();                                       

#define      TASK_TIMER_END(tick)		                                           \ 
                 }                                                             \                
						 }while(0)





#endif   /* MAIN_H */

/*---------------------- end of file -----------------------------------------*/
