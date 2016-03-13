/**
 * Encoding:    utf8
 * File:        htable.h
 * Compiled:    gcc 4.4
 * Name:        Pavol Loffay, xloffa00@stud.fit.vutbr.cz
 * Faculty:     FIT VUTBR
 * Project:     DU2/b for IJC
 * Date:        6.4.2011
*/

//bool
#include <stdbool.h>

typedef struct htable_listitem Thtable_listitem;

struct htable_listitem
{
	char *key;
	int data;
	Thtable_listitem *next;
};

typedef struct h_table 
{
	unsigned int htable_size;
	Thtable_listitem **data;
}Th_table;

typedef struct htable_iterator
{
	Th_table *htptr;
	unsigned int index;
	Thtable_listitem *ptr;
}Thtable_iterator;


//FUNKCIE
Th_table *htable_init(unsigned int size);
unsigned int hash_function(const char *str, unsigned htable_size);
Thtable_listitem *htable_lookup(Th_table *t, const char *key);
void htable_clear(Th_table *t);
void htable_free(Th_table *t);
Thtable_iterator htable_begin(Th_table *t);
Thtable_iterator htable_end(Th_table *t);
Thtable_iterator htable_iter_next(Thtable_iterator i);

static inline bool htable_iter_eq(Thtable_iterator i1, Thtable_iterator i2);
static inline Thtable_listitem *htable_iter_deref(Thtable_iterator i);


//INLINE FUNKCIE
/**
 * funkcia porovna dva iteratory na zhodu
 * @param i1 iterator1
 * @param i2 iterator2
 * @return vrati true alebo false, podla toho ci sa iterator zhoduju
 */
static inline bool htable_iter_eq(Thtable_iterator i1, Thtable_iterator i2)
{
	return (i1.htptr == i2.htptr) && (i1.index == i2.index) && (i1.ptr == i2.ptr) ? true : false;
}

/**
 * funkcia vrati ukazatel na zaznam, ktory si je ulozeny v iteratore
 * @param i iterator
 * @return ukazatel na zaznam, ktory obsahoval iterator 
 */
static inline Thtable_listitem *htable_iter_deref(Thtable_iterator i)
{
	return i.ptr;
}
