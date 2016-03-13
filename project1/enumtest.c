// Encoding utf-8
//enumtest.c
//Riesenie IJC-DU1, priklad a) 2.3.2011
//Autor: Pavol Loffay, xloffa00, FIT Brno
//Prelozene: gcc 4.4

//printf,
#include <stdio.h>
//setlocale
#include <locale.h>
//Error
#include "error.h"
//ReadMonth, PrintMonth, PrintMonthShort
#include "enum.h"

//testovaci program zo zadania DU.
int main(void) 
{
	/* test - NEMĚNIT! */
	char *l = setlocale(LC_ALL,"cs_CZ.iso-8859-2");
	if(l == NULL)
		Error("setlocale: Nelze nastavit českou lokalizaci\n");
	enum months m;
	m = ReadMonth();     // čte měsíc
	PrintMonthShort(m);  // tiskne krátké jméno
	printf("\n");
	PrintMonth(m);       // tiskne dlouhé jméno
	printf("\n\n");
	for( m = Leden; m < 15; m++ ) 
	{ // úmyslná chyba
		PrintMonthShort(m);
		printf("\n");
	}
	return 0;
}
