/**
  ******************************************************************************
  * @file     ring_buffer.c
  * @author   ZRT
  * @version  V1.0
  * @date     2020/04/11
  * @attention  
	* @warning	
  ******************************************************************************  
  * 
  * 
  ******************************************************************************
  */
/*-- includes ----------------------------------------------------------------*/
#include "./ring_buffer.h"


/*-- defined -----------------------------------------------------------------*/    
#define   DB_LOG(fmt)      
#define   ASSERT(fmt)


/*-- typedef -----------------------------------------------------------------*/



/*-- private variables -------------------------------------------------------*/


/*-- private functions -------------------------------------------------------*/


/*-- functions ---------------------------------------------------------------*/
	
/** @function  
  * @brief   
  * @param       
  * @return  
  */
static  u32_t location(RingBuffObj* thiz, rb_depth_t i)
{
  rb_depth_t  j = 0;

	ASSERT(thiz);
	
  j = ((i+1) >= thiz->depth) ? 0 : (i+1);

  return j;
}


/** @function  
  * @brief   
  * @param       
  * @return  
  */
rb_depth_t  check_ring_buff(RingBuffObj* thiz)
{
  ASSERT(thiz);

  return  thiz->remain;
}

/** @function  
  * @brief   
  * @param       
  * @return  
  */
rb_data_type  get_ring_buff_data(RingBuffObj* thiz)
{
	rb_data_type  ret = 0;
  rb_depth_t    pos = 0;

	ASSERT(thiz);
	ASSERT(thiz->ptBuffer);
	
  if(thiz->remain > 0)
  {
    pos = thiz->posGet;
    thiz->posGet = location(thiz, thiz->posGet);
    thiz->remain--;
    ret = thiz->ptBuffer[pos];
  }
  else 
  {
    ret = 0;
		DB_LOG("Ring buffer is empty.\r\n");
  }
	
	return ret;
}

 
/** @function  
  * @brief   
  * @param       
  * @return  
  */
void  put_ring_buff_data(RingBuffObj* thiz, rb_data_type dat)
{
	ASSERT(thiz);
	ASSERT(thiz->ptBuffer);
	
  if(thiz->remain < thiz->depth)
  {
    thiz->ptBuffer[thiz->posPut] = dat;
    thiz->posPut = location(thiz, thiz->posPut);
    thiz->remain++;
  }
  else
  {
	  DB_LOG("buffer is full.\r\n");
  }
}

/*------------------ end of file ---------------------------------------------*/