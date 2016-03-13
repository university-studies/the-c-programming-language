/**
 * Encoding:    utf8
 * File:        htable_lookup
 * Compiled:    gcc 4.4
 * Name:        Pavol Loffay, xloffa00@stud.fit.vutbr.cz
 * Faculty:     FIT VUTBR
 * Project:     DU2/b for IJC
 * Date:        6.4.2011
*/

//strncpy, strlen
#include <string.h>
//malloc, NULL
#include <stdlib.h>

#include "htable.h"

/**
 * funkcia vyhlada v hash table zaznam, v ktorom je ulozeny retazec key,
 * ak nenajde vytvory novy zaznam.
 * @param *t ukazatel na hash table
 * @param *key ukazatel na retazec - slovo
 * @return ukazatel na stary/novy zaznam, alebo NULL ak sa nepodaril malloc
 */
Thtable_listitem *htable_lookup(Th_table *t, const char *key)
{
	//ziskanie indexu z tabulky pomocou rozptylovacej funkcie
	unsigned int index = hash_function(key, t->htable_size);	
	
	Thtable_listitem *item = t->data[index];
	
	//prejde cely zaznam, ak najde zhody "key" tak vrati ukazatel
	for (; item != NULL; item = item->next)
	{
		if (strcmp(key, item->key) == 0)
			return item;
		if (item->next == NULL)
			break;
	}
	
	//alokovanie polozky
	Thtable_listitem *new = (Thtable_listitem *)malloc(sizeof(Thtable_listitem));
	if (new == NULL)
			return NULL;
	
	int length = strlen(key);
	
	//alokovanie miesta pre retazez v polozke + nulovanie
	new->key = (char *)calloc((length + 1), sizeof(char));
	if (new->key == NULL)
	{
		free(new);
		return NULL;
	}
	
	strncpy(new->key, key, length);
	new->next = NULL;
	new->data = 0;
	
	//zaradenie do zaznamu	
	if (t->data[index] == NULL)
		t->data[index] = new;
	else
		item->next = new;
		
	return new;
}