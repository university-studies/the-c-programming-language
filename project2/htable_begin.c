/**
 * Encoding:    utf8
 * File:        htable_begin.c
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
 * funkcia nastavi iterator na prvu polozku tabulky
 * ktora nie je NULL
 * @param *t ukazatel na hash table
 * @return iterator, pokial nenajde ziadny ne-NULL polozky tabulky
 * tak iterator nastavi na 0-ltu polozku tabulky a index na zaznam na NULL
 */
Thtable_iterator htable_begin(Th_table *t)
{
	Thtable_iterator iterator;
	//ukazatel na tabulku
	iterator.htptr = t;
	
	//prejde polozky tabulky a ak najde prvy zaznam tak vrati na neho iterator
	for (unsigned int i = 0; i < t->htable_size; i++)
	{
		if (t->data[i] != NULL)
		{
			iterator.index = i;
			iterator.ptr = t->data[i];
			return iterator;
		}
	}
	
	//ak nenasiel ziadnu polozku tabulky obsadenu nastavi sa na 0;
	iterator.index = 0;
	iterator.ptr = NULL;
	
	return iterator;
}