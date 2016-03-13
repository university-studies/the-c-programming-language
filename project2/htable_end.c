/**
 * Encoding:    utf8
 * File:        htable_end.c
 * Compiled:    gcc 4.4
 * Name:        Pavol Loffay, xloffa00@stud.fit.vutbr.cz
 * Faculty:     FIT VUTBR
 * Project:     DU2/b for IJC
 * Date:        6.4.2011
*/

//NULL
#include <stdlib.h>

#include "htable.h"

/**
 * funkcia nastavi iterator za poslednu polozku, cize na NULL
 * @param *t ukazatel na tabulku
 * @return iterator zaposlednu polozku tabulky
 */
Thtable_iterator htable_end(Th_table *t)
{
	Thtable_iterator iterator;
	//ukazatel na tabulku
	iterator.htptr = t;
	for (unsigned int index = t->htable_size - 1; index > 0; index--)
	{
		if (t->data[index] != NULL)
		{
			iterator.index = index;
			//pretoze kazdy linearny zoznam je ukonceny NULL
			iterator.ptr = NULL;
			return iterator;
		}
	}
	//tento stav by sa teoreticky nemal stat
	//pretoze lin. zoznam je vzdy ukonceny NULL
	iterator.index = 0;
	iterator.ptr = NULL;
	
	return iterator;
}