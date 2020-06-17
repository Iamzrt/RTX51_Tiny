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
#ifndef  _SYS_STD_H
#define  _SYS_STD_H


/* C++支持 */
#ifdef __cplusplus
extern "C" {
#endif
 


/*!< Signed integer types  */
typedef         signed char             s8_t;
typedef         signed int              s16_t;
typedef         signed long             s32_t;

/*!< Unsigned integer types  */
typedef         unsigned char           u8_t;
typedef         unsigned int            u16_t;
typedef         unsigned long           u32_t;



#define   		XDATA		 xdata
#define   		IDATA		 idata
#define   		BDATA		 bdata
#define   		DATA		 data
#define   		CODE		 code


/* 把宏参数变为一个字符串 */
#define     _STRING(x)                  #x
#define     STRING(x)                   _STRING(x)

/* 把宏参数连接在一起 */
#define     _CONNECT_MACRO(x,y)         x##y
#define     CONNECT_MACRO(x,y)          _CONNECT_MACRO(x,y)



/* 状态类型 */
typedef  enum
{
  OPERATE_OK  = 0,
  OPERATE_BUSY,
  OPERATE_TIMEOUT,
  OPERATE_FAIL,
}OpsStatus;


#ifndef  _IN_LINE_
  #define  _IN_LINE_   inline
#endif

#ifndef   BOOL
  #define   BOOL      bool
#endif

#ifndef   NULL
  #define   NULL     (void*)0
#endif


#ifndef  TRUE
  #define   TRUE    1
#endif

#ifndef  FALSE
  #define   FALSE    0
#endif

/* 纯虚函数关键字 */
#ifndef   VIRTUAL
  #define   VIRTUAL
#endif




#ifdef __cplusplus
}
#endif

#endif    /* _SYS_STD_H */

/*------------------ end of file ---------------------------------------------*/
