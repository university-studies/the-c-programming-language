// Encoding ISO-8859-2
//enum.c
//Riesenie IJC-DU1, priklad a) 2.3.2011
//Autor: Pavol Loffay, xloffa00, FIT Brno
//Prelozene: gcc 4.4

//getchar, printf
#include <stdio.h>
//isalpa, isspace, toupper, tolower
#include <ctype.h>
//strlen, strncpy, strcoll
#include <string.h>
//Error
#include "error.h"
#include "enum.h"

const char months[13][9] = {"und", "Leden", "Unor", "Brezen", "Duben", "Kveten",
"Cerven", "Cervenec", "Srpen", "Zari", "Rijen", "Listopad", "Prosinec" };

const char monthsShortCz[13][4] = {"und", "Led", "Úno", "Bøe", "Dub", "Kvì", "Èen", "Èec", "Srp", "Záø", "Øíj", "Lis", "Pro"};

const char monthsShort[13][4] = {"und", "Led", "Uno", "Bre", "Dub", "Kve", "Cen", "Cec", "Srp", "Zar", "Rij", "Lis", "Pro"}; 

const char monthsLongCz[13][9] = {"und", "Leden", "Únor", "Bøezen", "Duben", "Kvìten",
"Èerven", "Èervenec", "Srpen", "Záøi", "Øíjen", "Listopad", "Prosinec" };

//funkcia vytlaci kratku formu mesiaca
void PrintMonthShort(enum months d)
{
	if (d < 1 || d > 12)
		Error("PrintMonth*: Hodnota %d je mimo rozsah\n", d);
	else
		printf("%s", monthsShortCz[d]);
}

//funkcia vytlaci dlhu formu mesiaca
void PrintMonth(enum months d)
{
	if (d < 1 || d > 12)
		Error("PrintMonth*: Hodnota %d je mimo rozsah\n", d);
	else
		printf("%s", monthsLongCz[d]);
}

//funkcia cita zo stdin znaky. vsetky biele znaky preskoci
//potom nacita slovo po dalsi biely znka alebo do dlzky 9znakov-najdlhsi mesiac
enum months ReadMonth(void)
{
	int c;
	int i = 0;
	char arr[9] = {0};
	//cyklus nacita retazec do pola arr[9] preskakuje biele znaky,
	//maximalna dlzka retazca je 9 znakov prosinec=8znakov najdlhsi retazec
	while ( (c = getchar()) != EOF && i < 9)
	{
		if (isalpha(c))
			arr[i++] = c;		
		else
		{
			if(isspace(c) && i == 0)
				continue;
			else
				break;
		}
	}
	
	//ak je retazec dlhsi ako 9 znakov, tak to nie je ziadny mesiac
	if (i == 9)
		return 0;
	
	int length = strlen(arr);
	//prevediem velke pismena na male, prve prevediem na velke
	arr[0] = toupper(arr[0]);
	for ( i = 1; i < length; i++)
		arr[i] = tolower(arr[i]);
	
	
	if (strlen(arr) == 3)
	{
		//porovnavanie skratenych nazvov XXX
		for ( int i = 1; i < 13; i++)
			if (strcoll(monthsShort[i], arr) == 0 || strcoll(monthsShortCz[i], arr) == 0)
				return i;
	}
	
	//porovnacanie celych nazvov
	for ( int i = 1; i < 13; i++)
		if (strcoll(months[i], arr) == 0 || strcoll(monthsLongCz[i], arr) == 0)
			return i;
	return 0;
}
