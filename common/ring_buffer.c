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


/*-- typedef -----------------------------------------------------------------*/
//struct  RingBuffStruct  
//{
//  rb_depth_t      posPut;    /* The current location of the ring buffer. */
//	rb_depth_t      posGet;    /* The current fetch position of the buffer. */
//	rb_depth_t      depth;     /* The total number of elements in the ring buffer. */
//	rb_depth_t      remain;
//	
//	rb_data_type*   ptBuffer;  /* Ring buffer pointer. */
//};


/*-- private variables -------------------------------------------------------*/


/*-- private functions -------------------------------------------------------*/


/*-- functions ---------------------------------------------------------------*/
	
/** @function  
  * @brief   
  * @param       
  * @return  
  */
static  rb_depth_t location(RingBuffObj* thiz, rb_depth_t i)
{
  rb_depth_t  j = 0;

	//ASSERT(thiz);
	
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
  //ASSERT(thiz);

  return  thiz->remain;
}

/** @function  
  * @brief   
  * @param       
  * @return  
  */
rb_data_type  get_ring_buff_data(RingBuffObj* thiz)
{
	rb_data_type XDATA ret = 0;
  rb_depth_t   XDATA pos = 0;

	//ASSERT(thiz);
	//ASSERT(thiz->ptBuffer);
	
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
		//DB_LOG("Ring buffer is empty.\r\n");
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
	//ASSERT(thiz);
	//ASSERT(thiz->ptBuffer);
	
  if(thiz->remain < thiz->depth)
  {
    thiz->ptBuffer[thiz->posPut] = dat;
    thiz->posPut = location(thiz, thiz->posPut);
    thiz->remain++;
  }
  else
  {
	  //DB_LOG("buffer is full.\r\n");
  }
}

/** @function  
  * @brief   
  * @param       
  * @return  
  */
void  ring_buff_create(RingBuffObj* obj, rb_depth_t  depth, \
                       rb_data_type* ptBuffer)
{
  if(obj)
	{
    obj->depth = depth;
		obj->posPut = 0;
		obj->posGet = 0;
		obj->remain = 0;
		obj->ptBuffer = ptBuffer;	
	}
}

/*------------------ end of file ---------------------------------------------*/
