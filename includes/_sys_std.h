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


/* C++֧�� */
#ifdef __cplusplus
extern "C" {
#endif
 


//#define   USE_IAR_IDE
#define   USE_KEIL_IDE
  

/* ��ͬIDE��Ҫ�޸��������Ͷ��� */
#if defined(USE_IAR_IDE)
  
/*!< Signed integer types  */
typedef         signed char             s8_t;
typedef         signed int              s16_t;
typedef         signed long             s32_t;

/*!< Unsigned integer types  */
typedef         unsigned char           u8_t;
typedef         unsigned int            u16_t;
typedef         unsigned long           u32_t;

#elif defined(USE_KEIL_IDE)

/*!< Signed integer types  */
typedef         signed char             s8_t;
typedef         signed int              s16_t;
typedef         signed long             s32_t;

/*!< Unsigned integer types  */
typedef         unsigned char           u8_t;
typedef         unsigned int            u16_t;
typedef         unsigned long           u32_t;

#endif


#define   		XDATA		 xdata
#define   		IDATA		 idata
#define   		BDATA		 bdata
#define   		DATA		 data
#define   		CODE		 code


/* �Ѻ������Ϊһ���ַ��� */
#define     _STRING(x)                  #x
#define     STRING(x)                   _STRING(x)

/* �Ѻ����������һ�� */
#define     _CONNECT_MACRO(x,y)         x##y
#define     CONNECT_MACRO(x,y)          _CONNECT_MACRO(x,y)


/* ״̬���� */
typedef  enum
{
  OPERATE_OK  = 0,
  OPERATE_BUSY,
  OPERATE_TIMEOUT,
  OPERATE_FAIL,
}SysStatusType;


#ifndef  _IN_LINE_
  #define  _IN_LINE_   inline
#endif

#ifndef   BOOL
  #define   BOOL   u8_t
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

/* ���麯���ؼ��� */
#ifndef   VIRTUAL
  #define   VIRTUAL
#endif


/* �ⲿ���������ؼ��� */
#ifndef   EXTERN_FUNC
  #define   EXTERN_FUNC         extern
#endif





#ifdef __cplusplus
}
#endif

#endif    /* _SYS_STD_H */

/*------------------ end of file ---------------------------------------------*/
