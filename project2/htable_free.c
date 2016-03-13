/**
 * Encoding:    utf8
 * File:        htable_free.c
 * Compiled:    gcc 4.4
 * Name:        Pavol Loffay, xloffa00@stud.fit.vutbr.cz
 * Faculty:     FIT VUTBR
 * Project:     DU2/b for IJC
 * Date:        6.4.2011
*/

//free, NULL
#include <stdlib.h>

#include "htable.h"

/**
 * funnkcia uvolni hash table z pameti
 * @param *t ukazatel na hash table
 */
void htable_free(Th_table *t)
{
	//uvolnenie zaznamov
	htable_clear(t);
	//uvolnenie pola tabulky
	free(t->data);
	//uvolnenie celej tabulky
	free(t);
}