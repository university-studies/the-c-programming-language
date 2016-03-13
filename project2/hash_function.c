/**
 * Encoding:    utf8
 * File:        hash_function.c
 * Compiled:    gcc 4.4
 * Name:        Pavol Loffay, xloffa00@stud.fit.vutbr.cz
 * Faculty:     FIT VUTBR
 * Project:     DU2/b for IJC
 * Date:        6.4.2011
*/

#include "htable.h"

/**
 * funkcia zo zadania projektu, vrati index do hash table 
 * @param *str ukazatel na retazec
 * @param htable_size velkost tabulky
 * @return index do hash table
 */
unsigned int hash_function(const char *str, unsigned htable_size)
{
	unsigned int h = 0;
	unsigned char *p;
	for (p = (unsigned char *)str; *p != '\0'; p++)
		h = 31 * h + *p;
	return h % htable_size;
}
