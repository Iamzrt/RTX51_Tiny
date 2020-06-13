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
typedef    u8_t     rb_depth_t;
typedef    u8_t     rb_data_type;


//struct  RingBuffStruct;

struct  RingBuffStruct  
{
  rb_depth_t      posPut;    /* The current location of the ring buffer. */
	rb_depth_t      posGet;    /* The current fetch position of the buffer. */
	rb_depth_t      depth;     /* The total number of elements in the ring buffer. */
	rb_depth_t      remain;
	
	rb_data_type*   ptBuffer;  /* Ring buffer pointer. */
};

typedef  struct  RingBuffStruct  RingBuffObj;


/*-- functions ---------------------------------------------------------------*/
extern    void            ring_buff_create(RingBuffObj* obj, rb_depth_t depth, \
                                           rb_data_type* ptBuffer);
extern    rb_depth_t      check_ring_buff(RingBuffObj* thiz);
extern    rb_data_type    get_ring_buff_data(RingBuffObj* thiz);
extern    void            put_ring_buff_data(RingBuffObj* thiz, rb_data_type dat);


#endif    /* RING_BUFFER_H */

/*------------------ end of file ---------------------------------------------*/