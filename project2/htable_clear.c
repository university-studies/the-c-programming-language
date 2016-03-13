/**
 * Encoding:    utf8
 * File:        htable_clear.c
 * Compiled:    gcc 4.4
 * Name:        Pavol Loffay, xloffa00@stud.fit.vutbr.cz
 * Faculty:     FIT VUTBR
 * Project:     DU2/b for IJC
 * Date:        6.4.2011
*/

//free
#include <stdlib.h>

#include "htable.h"

/**
 * funkcia uvolny vsetky polozky hash table
 * @param *t ukazatel na hash table
 */
void htable_clear(Th_table *t)
{
	for (unsigned int index = 0; index < t->htable_size; index++)
	{
		
			Thtable_listitem *temp = NULL;
		for (Thtable_listitem *item = t->data[index]; item != NULL; item = temp)
		{
			temp = item->next;
			//uvolnim pole char
			free(item->key);
			//uvolnim celu polozky
			free(item);
		}
	}
}