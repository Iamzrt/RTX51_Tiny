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
#ifndef  PLATFORM_CONFIG_H
#define  PLATFORM_CONFIG_H


/* C++支持 */
#ifdef __cplusplus
extern "C" {
#endif
 
   

/* 平台选择，只能选其一 */
/* #define    N76E003_PLATFORM  */
#define    STM8S003_PLATFORM 
/* #define    STM8L05X_PLATFORM */
 


/*-- includes ----------------------------------------------------------------*/
#if defined(N76E003_PLATFORM)


#include "../component/hal/n76e003/hal_mcu.h"

#elif defined(STM8S003_PLATFORM)

#include "../component/hal/stm8s003/hal_mcu.h"  
  
#elif defined(STM8L05X_PLATFORM)
  
#include "../component/hal/stm8l05x/hal_mcu.h"
  
#else
  
#endif



#ifdef __cplusplus
}
#endif

#endif    /* PLATFORM_CONFIG_H */

/*------------------ end of file ---------------------------------------------*/
