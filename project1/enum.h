// Encoding utf-8
//enum.h
//Riesenie IJC-DU1, priklad a) 2.3.2011
//Autor: Pavol Loffay, xloffa00, FIT Brno
//Prelozene: gcc 4.4

enum months{
	ChybnyMesic = 0,
	Leden = 1,
	Unor,
	Brezen,
	Duben,
	Kveten,
	Cerven,
	Srpen,
	Zari,
	Rijen,
	Listopad,
	Prosinec
};

void PrintMonthShort(enum months d);
void PrintMonth(enum months d);
enum months ReadMonth(void);