/**
 * Encoding:    utf8
 * File:        htable_init.c
 * Compiled:    gcc 4.4
 * Name:        Pavol Loffay, xloffa00@stud.fit.vutbr.cz
 * Faculty:     FIT VUTBR
 * Project:     DU2/b for IJC
 * Date:        6.4.2011
*/

//malloc, free, NULL
#include <stdlib.h>

#include "htable.h"

/**
 * funckia alokuje dinamicky pamet pre htable
 * @param size pocet riadkov tabulky (linearnych zoznamov)
 * @return vrati ukazatel na htable, ak sa nepodari malloc tak vrati NULL
 */
Th_table *htable_init(unsigned int size)
{
	//alokujem tabulku
	Th_table *htable = (Th_table*)malloc(sizeof(Th_table));
	
	if (htable == NULL)
		return NULL;

	//alokujem riadky tabulky
	htable->data = (Thtable_listitem **) malloc(size * sizeof(Thtable_listitem));
	if (htable->data == NULL)
	{
		free(htable);
		return NULL;
	}
	
	//inicializacia zaznamov
	for (int i = 0; i < size; i++)
		htable->data[i] = NULL;	
	
	//priradim velkost tabulky do htable->size 
	htable->htable_size = size;
	//vratim ukazatel na tabulku
	return htable;
}