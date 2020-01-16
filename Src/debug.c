/**
  ******************************************************************************
  * @file    debug.c 
  * @author  Georg Stroh 
  * @version V1.0.0
  * @date    09.10.2014 
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "debug.h"

/** @addtogroup DEBUG
  * @{
  */
 FILE __stdout;
 FILE __stdin;	
 /* cppcheck-suppress unusedStructMember */
 struct __FILE { int handle; /* Add whatever you need here */ };
 
 
int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}
/**
  * @}
  */ 
