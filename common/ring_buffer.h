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
#ifndef  RING_BUFFER_H
#define  RING_BUFFER_H

/*-- includes ----------------------------------------------------------------*/
#include "../includes/_sys_std.h"


/*-- defined -----------------------------------------------------------------*/




/*-- typedef -----------------------------------------------------------------*/
typedef    u32_t    rb_depth_t;
typedef    u16_t    rb_data_type;

typedef   struct
{
  rb_depth_t      posPut;    /* The current location of the ring buffer. */
	rb_depth_t      posGet;    /* The current fetch position of the buffer. */
	rb_depth_t      depth;     /* The total number of elements in the ring buffer. */
	rb_depth_t      remain;
	
	rb_data_type*   ptBuffer;  /* Ring buffer pointer. */
}RingBuffObj;


/*-- functions ---------------------------------------------------------------*/
extern    rb_depth_t      check_ring_buff(RingBuffObj* thiz);
extern    rb_data_type    get_ring_buff_data(RingBuffObj* thiz);
extern    void            put_ring_buff_data(RingBuffObj* thiz, rb_data_type dat);


#endif    /* RING_BUFFER_H */

/*------------------ end of file ---------------------------------------------*/