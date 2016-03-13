// Encoding utf-8
//error.c
//Riesenie IJC-DU1, priklad a) 2.3.2011
//Autor: Pavol Loffay, xloffa00, FIT Brno
//Prelozene: gcc 4.4

//fprintf, vfprintf
#include <stdio.h>
//va_list, va_start, va_end
#include <stdarg.h>
//exit, EXIT_FAILURE
#include <stdlib.h>

#include "error.h"

void Error(const char *fmt, ...)
{	
	va_list ap;    
	//nastavi ukazatel na prvy volny argumenty                 
	va_start(ap,fmt);                     
	fprintf(stderr,"CHYBA: ");
	vfprintf(stderr,fmt,ap); 
	//uzavre zpracovanie argumentov            
	va_end(ap);
	exit(EXIT_FAILURE);	
}
