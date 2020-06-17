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
#ifndef  MSG_H
#define  MSG_H

/*-- includes ----------------------------------------------------------------*/
#include "../includes/_sys_std.h"


/*-- defined -----------------------------------------------------------------*/


typedef   u8_t   msg_size_t;
typedef   u8_t   msg_len_t;

typedef  enum
{
  MSG_MIS_MATCH,
	MSG_MATCH,
}MsgMatch;

typedef  struct
{
  msg_len_t     len;
	msg_size_t*   array;  
}MsgDef;

#define          NO_MSG_DEF     (msg_size_t)0

/*-- functions ---------------------------------------------------------------*/
extern s8_t        msg_create(MsgDef* obj, msg_size_t* array, msg_len_t len);

extern void        msg_broadcast(MsgDef* obj, msg_size_t msg);	
																	
extern MsgMatch    msg_check(MsgDef* obj, msg_len_t index, msg_size_t msg);



#endif    /* MSG_H */

/*------------------ end of file ---------------------------------------------*/