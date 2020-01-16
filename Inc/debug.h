/**
  ******************************************************************************
  * @file    Debug_Pring.h
  * @author  Georg Stroh
  * @version V1.0.0
  * @date    26-August-2014
  * @brief   
	* 
  */ 

#ifndef __DEBUG_PRINT_H
#define __DEBUG_PRINT_H 


#include <string.h>
#include <stdio.h>


 /** DEBUG**/
 /* Printf Implementation*/
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000 



/**Enables Trace debugging*/
#define _SYSTEM_DEBUG_TRACE 1

/** Enables Error Debugging */
#define _SYSTEM_DEBUG_ERROR 1


/** Error Printout */
#ifdef _SYSTEM_DEBUG_ERROR
/** Defenition of Trace output */
#define _SYSTEM_ERROR(...)      printf("SYSTEM_ERROR: ") ;\
														  	printf(__VA_ARGS__);\
														  	printf("\n");
#else
/** Defenition of Trace output */
#define _SYSTEM_ERROR  (...)  ((void)0)
#endif 


#ifdef _SYSTEM_DEBUG_TRACE
/** Defenition of Trace output */
#define _SYSTEM_TRACE(...)      printf("SYSTEM_TRACE: ") ;\
														  	printf(__VA_ARGS__);\
														  	printf("\n");
#else
/** Defenition of Trace output */
#define _SYSTEM_TRACE(...)  ((void)0)
#endif 
#endif 
