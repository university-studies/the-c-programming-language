/**
 * Encoding:    utf8
 * File:        htable_iter_next.c
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
 * @param i nastaveny iterator na lubovolny index tabulky a lubovolnu polozku
 * linearneho zaznamu
 * @return iterator na dalsi zaznam linearneho zoznamu, alebo dalsiu polozku 
 * tabulky, alebo nastavi iterator.ptr na NULL
 */
Thtable_iterator htable_iter_next(Thtable_iterator i)
{
	//ak ukazatel na dalsi prvok lin zoznamu sa != NULL tak sa na neho posuniem
	if ( i.ptr->next != NULL)
	{
		i.ptr = i.ptr->next;
		return i;
	}
	
	//hladam dalsiu polozku tabulky ktora nie je NULL
	for (unsigned int index = i.index + 1; index < i.htptr->htable_size; index++)
	{
		if (i.htptr->data[index] != NULL)
		{
			i.index = index;
			i.ptr = i.htptr->data[index];
			return i;
		}
	}

	//ak nenasiel dalsi prvok tabulky ktory != NULL, tak nastavi ukazatel na NULL
	i.ptr = NULL;
	return i;
}