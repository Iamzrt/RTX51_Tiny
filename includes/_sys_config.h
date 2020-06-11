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
#ifndef    _SYS_CONFIG_H
#define    _SYS_CONFIG_H


/* C++ support */
#ifdef __cplusplus
extern "C" {
#endif


#include "./_sys_std.h"


/*< Configure the watchdog function.  0: disable; 1:enable. >*/
#define     WDT_ENABLE                                 1

/*< Log output configuration. 0: disable; 1:enable. >*/
#define     LOG_ENABLE                                 1

/*< Console configuration. 0: disable; 1:enable. >*/
#define     CONSOLE_ENABLE                             0




/* C++ support */
#ifdef __cplusplus
}
#endif


#endif   /* _SYS_CONFIG_H */

/*---------------------- end of file -----------------------------------------*/
