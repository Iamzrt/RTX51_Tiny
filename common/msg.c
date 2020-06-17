/**
  ******************************************************************************
  * @file    
  * @author   
  * @version  
  * @date     
  * @attention  
	* @warning	
  ******************************************************************************  
  * 
  * 
  ******************************************************************************
  */
/*-- includes ----------------------------------------------------------------*/
#include "./msg.h"


/*-- defined -----------------------------------------------------------------*/    





/*-- private variables -------------------------------------------------------*/


/*-- private functions -------------------------------------------------------*/


/*-- functions ---------------------------------------------------------------*/

/** @function  
  * @brief   
  * @param       
  * @return  
  */
s8_t  msg_create(MsgDef* obj, msg_size_t* array, msg_len_t len)
{
  s8_t  XDATA  ret = 0;

  if(obj)
	{
	  obj->len    = len;
		obj->array  = array;
	}
	else
	{
    ret = -1;	  
	} 

	return ret;
}
	

/** @function  
  * @brief   
  * @param       
  * @return  
  */		
void  msg_broadcast(MsgDef* obj, msg_size_t msg)
{
  msg_len_t  XDATA  num = 0;

  for(num=0; num<obj->len; num++)
	{
	  obj->array[num] = msg;
	}
}


/** @function  
  * @brief   
  * @param       
  * @return  
  */		
MsgMatch  msg_check(MsgDef* obj, msg_len_t index, msg_size_t msg)
{
  MsgMatch XDATA ret;

	if(obj->array[index] == msg)
	{
	  obj->array[index] = NO_MSG_DEF;
	  ret = MSG_MATCH;
	}
	else
	{
	  ret = MSG_MIS_MATCH;
	}

  return 	ret;
}

/*------------------ end of file ---------------------------------------------*/
