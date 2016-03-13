// Encoding utf-8
//Riesenie IJC-DU1, priklad b) 2.3.2011
//Autor: Pavol Loffay, xloffa00, FIT Brno
//Prelozene: gcc 4.4

//printf
#include <stdio.h>
//sqrt
#include <math.h>
//memset
#include <string.h>
//CHAR_BIT
#include <limits.h>
//Error
#include "error.h"

typedef unsigned long ArrayType;
#define SIZE 90000000
#define PRINT 20

//pomocne makro vrati, ake velke pove sa ma deklarovat 
#define ArrayIndex(index)								\
	(long) (index / (sizeof(ArrayType) * CHAR_BIT) + 1)
	
//vrati na ktorom bite sa presne nachadza tento index v poli
#define BitArrayIndex(index)							\
	(ArrayType) (index % (sizeof(ArrayType) * CHAR_BIT))

//makro definuje a nuluje pole
#define BitArray(jmeno_pole, velikost)							\
	ArrayType jmeno_pole[(( velikost % (sizeof(ArrayType) * CHAR_BIT) ) == 0) ?  ArrayIndex(velikost) : ArrayIndex(velikost) +1 ] = {velikost, 0}

#ifdef USE_INLINE
	static inline void SetBit(ArrayType *jmeno_pole, long index, int vyraz)
	{
		if (index >= jmeno_pole[0] || index <= 0)
			Error("Index %ld mimo rozsah 0..%ld", (long)index, (long)jmeno_pole[0]),0;
		else
			if (vyraz) 
				(jmeno_pole[ArrayIndex(index)] |= (1 << BitArrayIndex(index)));
			else
				(jmeno_pole[ArrayIndex(index)] &= 1 << BitArrayIndex(index));
	}

	static inline int GetBit(ArrayType *jmeno_pole, long index)
	{
		if (index >= jmeno_pole[0] || index <= 0)
			Error("Index %ld mimo rozsah 0..%ld", (long)index, (long)jmeno_pole[0]);
		else
		 return (((jmeno_pole[ArrayIndex(index)] >> BitArrayIndex(index)) & 1) == 0) ? 0 : 1;
		return 0;
	}
	
#else
	//makro nastavi 0 alebo 1 v bite s indexom index podla vyhodnotenia vyrazu
	#define SetBit(jmeno_pole, index, vyraz)					\
		if (index >= jmeno_pole[0] || index <= 0)				\
			Error("Index %ld mimo rozsah 0..%ld", (long)index, (long)jmeno_pole[0]),0;	\
		else													\
			vyraz ? (jmeno_pole[ArrayIndex(index)] |= (1 << BitArrayIndex(index)) ) : \
			(jmeno_pole[ArrayIndex(index)] &= (1 << BitArrayIndex(index)) ) 

	//makro vrati hodnotu bitu s indexom index
	#define GetBit(jmeno_pole, index)						\
		(index >= jmeno_pole[0] ? Error("Index %ld mimo rozsah 0..%ld", (long)index, (long)jmeno_pole[0]), 0 :		\
		(((jmeno_pole[ArrayIndex(index)] >> BitArrayIndex(index)) & 1) == 0  ? 0 : 1))
#endif

int main()
{	
	BitArray(bitArr, SIZE);	
	double stop = sqrt(SIZE);	
	for (int i = 2; i <= stop; i++)
	{	
		if (!GetBit(bitArr, i))
		{
			int k = i;
			while (k*i < SIZE)
			{
				SetBit(bitArr, k*i, 1);
				k++;
			}
		}
	}
	
	int arrPrint[20];
	int j = 0;
	for (int i = SIZE-1; j < PRINT; i--)
	{
		if (!GetBit(bitArr, i))
		{
			arrPrint[j] = i;
			j++;
		}
	}	
	
	//vypis poslednych 20 prvocisel vzostupne
	for( int i = PRINT - 1; i >= 0; i--)
		printf("%d\n", arrPrint[i] );
	
	return 0;
}