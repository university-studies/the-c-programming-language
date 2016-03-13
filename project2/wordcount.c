/**
 * Encoding:    utf8
 * File:        wordcount.h
 * Compiled:    gcc 4.4
 * Name:        Pavol Loffay, xloffa00@stud.fit.vutbr.cz
 * Faculty:     FIT VUTBR
 * Project:     DU2/b for IJC
 * Date:        6.4.2011
*/

//printf, fprintf
#include <stdio.h>
//exit, NULL, calloc
#include <stdlib.h>
//bool
#include <stdbool.h>
//fgetword
#include "io.h"
//htable_init, htable_lookup, htable_free, htable_begin,htable_end,
//htable_iter_deref, htable_iter_eq, htable_iter_next
#include "htable.h"

//zadanie = 255 + '\0' = 256 znakov
#define WORDLENGTHMAX 256

/**
 * Velkost tabulky som experimentalne zistoval, tak
 * ze som meral cas pomocou programu time, 
 * na spracovani textoveho subora
 * o velkosti 114.6MB, dospel som k vysledkom:
 * velkost tabulky, priemrny cas (real time)
 * 32                 28.5s                  
 * 64                 14.7s
 * 128                10.2s
 * 256                 7.9s
 * 512                 6.7s
 * 1024                6.1s
 * 2048                5.8s
 * 4096                5.6s
 * 8192                5.5s
 * 16384               5.4s
 * 32768               5.35s
 * 
 * dalej som vyskusal ako dlho bude spracovavat ten
 * isty subor program zo zadania napisany v C++,
 * vysledok bol v priemere 28.5s
 * 
 * vsetky testy som robil na skolskom servery merlin
 * 
 * Nakoniec som sa rozhodol pre velkost 1024, kde program
 * dosahuje velmi dobre casove vysledky, vacsia velkost
 * si myslim ze by uz bola zbytocna, alokovalo by sa dvojnasobne
 * viac miesta a vysledny cas behu programu , by uz nebol o moc mensi.
 */
//velkost tabulky
#define TABLESIZE 1024

void printError(char *mesg, Th_table *htable);

/**
 * funkcia vytlaci retazec a ak htable != NULL, tak
 * uvolni hash table z pamete, ukonci program s exit(1)
 * @param *mesg ukazatel na spravu ktoru ma vytlacit
 * @param *htable ukazatel na hash table
 * @return exit(1)
 */
void printError(char *mesg, Th_table *htable)
{
	fprintf(stderr, "%s\n", mesg);
	if (htable != NULL)
		htable_free(htable);
	exit(1);
}

/**
 * Zaciatok programu
 */
int main(void)
{	
	Th_table *htable = htable_init(TABLESIZE);
	if (htable == NULL)
		printError("Nepodarilo sa alokovat pamet pre hash table!", htable);
	
	//alokujem si do ktoreho budem ukladat slova z funkcie fgetword
	char *word = (char *)calloc(WORDLENGTHMAX, sizeof(char));	
	if (word == NULL)
		printError("Nepodarilo sa alokovat pamet pre pole!", htable);
	
	Thtable_listitem *item = NULL;
	
	//nacitanie slov do hash table
	while(fgetword(word, WORDLENGTHMAX, stdin) != 0)
	{
		item = htable_lookup(htable, word);
		if (item == NULL)
		{
			free(word);
			printError("Nepodarilo sa alokovat pamet pre novu polozku!", htable);
		}
		
		//pocita vyskity slova
		item->data++;
	}
	//vypis slovo pocetVyskitov
	/////////////////////////////////////////////
	//nastavim iterator na prvu polozku
	Thtable_iterator iteratorBegin = htable_begin(htable);
	//nastavim iterator na poslednu polozku
	Thtable_iterator iteratorEnd = htable_end(htable);
	//vypis key  data
	while (htable_iter_eq(iteratorBegin, iteratorEnd) == false)
	{
		item = htable_iter_deref(iteratorBegin);
		printf("%s\t%d\n", item->key, item->data);
		iteratorBegin = htable_iter_next(iteratorBegin);
	}
	
	//uvolnit alokovane polia..
	htable_free(htable);
	free(word);
	
	return EXIT_SUCCESS;
}