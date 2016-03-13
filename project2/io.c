/**
 * Encoding:    utf8
 * File:        io.c
 * Compiled:    gcc 4.4
 * Name:        Pavol Loffay, xloffa00@stud.fit.vutbr.cz
 * Faculty:     FIT VUTBR
 * Project:     DU2/b for IJC
 * Date:        6.4.2011
*/

//isspace, isalpha
#include <ctype.h>
//FILE 
#include <stdio.h>

#include "io.h"

/**
 * funkcia cita z FILE po znakoch, preskoci vsetky biele znaky{isspace}
 * a potom nacita slovo z urcenou maximalnou dlzkou.
 * @param *s ukazatel na retazec do ktoreho ulozi nacitane slovo
 * @param max maximalna mozna dlzka slova
 * @param *f ukazatel na miesto v subore
 * @return dlzku slova, alebo 0 ak narazil na EOF
 */
int fgetword(char *s, int max, FILE *f)
{
	int c = 0;
	int i = 0;
	
	while( (c = fgetc(f)) != EOF && i < max - 1)
	{
		if(isspace(c) && i == 0)
			continue;
		else
			if (!isspace(c))
			{
				s[i] = c;
				i++;
			}
			else
				break;
	}
	
	if(c != EOF && isspace(c) == 0 )
	{
		//ak narazi na prvy znak co nie je slovo tak sa zastavi.
		while((c = fgetc(f)) != EOF)
			if (isspace(c))
				break;
		fprintf(stderr, "Bol zadany subor, ktory obsahuje dlhsie slovo ako limit %d!\n", max - 1);
		return max - 1;
	}
	if (c == EOF)
		return 0;
	
	s[i] = '\0';
	
	//vrati dlzku slova
	return i;
}