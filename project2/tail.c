/**
 * Encoding:    utf8
 * File:        tail.c
 * Compiled:    gcc 4.4
 * Name:        Pavol Loffay, xloffa00@stud.fit.vutbr.cz
 * Faculty:     FIT VUTBR
 * Project:     DU2/a for IJC
 * Date:        2.4.2011
*/

//FILE, fopen, fclose , fgets, printf
#include <stdio.h>
//strtol, EXIT_SUCCESS, malloc, calloc, free, exit
#include <stdlib.h>
//isdigit
#include <ctype.h>
//errno
#include <errno.h>
//strcmp, 
#include <string.h>
//LONG_MIN, LONG_MAX
#include <limits.h>


//v zadani je limit na riadok 1024 znakov
//uvazujem do retazca \n + \0, tak 1024 + 2 = 1026
#define LIMIT 1026
//tail bez parametru -n number,,, znamena ze sa ma tlacit 10 riadkov
//pouzitie taktiez pri strtol(,,DEFAULT)
#define DEFAULT 10

//chybove stavy programu
enum tecodes
{
	EOK = 0,
	ECLWRONG,
	EMALLOC,
	ELIMIT,
	EFILE,
	EUNKNOWN,
};

//stavy programu
enum tstates
{
	//tlaci sa n-ty pocet riadkov
	NORMAL = 0,
	//bude sa tlacit od riadku s urcitym cislom
	FROMLINE,
};

//struktura obsahujuca informacia o stave, chybach, programu
//ukladaju sa do nej informacia z prik. riadku
typedef struct params
{
	int state;
	int ecode;
	long lines;
	FILE *fr;
}TParams;

//pole kde su deklarovane chybove hlasenia
const char *ECODEMSG[] =
{
// EOK
	"Vsetko v poriadku\n",
// ECLWRONG
	"Zle parametre prikazoveho riadku!\n",
// EMALLOC
	"Nepodarila sa alokovat pamet!\n",
// ELIMIT
	"Vstupny subor obsahoval riadok dlhsi ako 1024 znakov\n",
// EFILE
	"Nepodarilo sa otvorit subor!\n",
// EUNKNOWN
	"Nastala nevyspitatelna chyba!\n",
};

/**
 * Funkcie
 */
int lines(char argv[], TParams *params);
TParams getParams(int argc, char **argv);
void freeMatrix(char **matrix, long rows);
char **allocMatrix(long rows, long columns);
int tail(TParams *params);
int tailFromLine(TParams *params);
void printError(const char *mesg, FILE *fr);


void printError(const char *mesg, FILE *fr)
{
	if (fr != stdin && fr != NULL)
	{
		fclose(fr);
	}
	fprintf(stderr, "%s", mesg);
	exit(1);
}

/**
 * pomocna funkcia k getParams, zisti ci v argv[] je ulozene
 * +cislo, alebo cislo, pritom cislo prevedie z char[] na long
 * kontroluje pretecenie a medze 
 * @param *argv ukazatel na pole
 * @param *params ukazatel na strukturu s informaciami z prik. riadku 
 */
int lines(char argv[], TParams *params)
{
	int i = 0;
	
	if (argv[0] == '+')
	{
		//znamena ze niekto zadal iba +
		if (strlen(argv) == 1)
			return EXIT_FAILURE;
		params->state = FROMLINE;
		i = 1;
	}
	while (argv[i] != '\0')
	{
		if (!isdigit(argv[i++]))
			return EXIT_FAILURE;
	}
	params->lines = strtol(argv, NULL, DEFAULT);
	if ((errno == ERANGE && (params->lines == LONG_MAX || params->lines == LONG_MIN)) || params->lines < 0) 
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

/**
 * funkcia spracuje parametre prik. riadku a ulozi do struktury typu TParams
 */
TParams getParams(int argc, char **argv)
{
	TParams params = {
		.ecode = EOK,
		.state = NORMAL,
		.lines = DEFAULT,
		.fr = stdin
	};
	if (argc == 1)
		params.ecode = EOK;
	else
		if (argc == 2)
		{
			params.fr = fopen(argv[1], "r");
			if (params.fr == NULL)
				printError(ECODEMSG[EFILE], params.fr);
		}
		else
			if(argc == 3)
			{
				if (strcmp(argv[1], "-n") == 0)
				{
					if(lines(argv[2], &params) != EXIT_SUCCESS)
						params.ecode = ECLWRONG;
				}
				else
					params.ecode = ECLWRONG;
			}
			else
				if(argc == 4)
				{
					if(strcmp(argv[1], "-n") == 0)
					{
						if(lines(argv[2], &params) == EXIT_SUCCESS)
						{
							params.fr = fopen(argv[3], "r");
							if (params.fr == NULL)
								printError(ECODEMSG[EFILE], params.fr);
						}
						else
							params.ecode = ECLWRONG;
					}
					else
						params.ecode = ECLWRONG;
				}
				else
					params.ecode = ECLWRONG;
	return params;
}

/**
 * Funcia dealokuje maticu
 * @param **matrix ukazatel na 2D pole
 * @param rows pocet riadkov matice
 */
void freeMatrix(char **matrix, long rows)
{
    for (long i = 0; i < rows; i++)
	{
      free(matrix[i]);
	}
   free(matrix);
}

/** 
 * funkcia alokuje 2D pole, a vrati ukazatel na neho
 * @param rows pocet riadkov matice
 * @param columns pocet stlpcov matice
 */
char **allocMatrix(long rows, long columns)
{
	char **print;
	print = (char **)malloc(rows * sizeof(char*));  //riadky
	if (print == NULL)
		return NULL;
	
	for (int i = 0; i < rows; i++)
	{
		print[i] = (char *)calloc(columns, sizeof(char));
		if (print[i] == NULL) 
		{
			for (int j = 0; j < i; j++)  //dealokujem pole a koncim
			free(print[j]);
			free(print); //uvolnim celu            
			return NULL;
		}
	}
	return print;
}

/**
 * funckia funguje ako POSIX tail, vypise 0-.. poslednych riadkov subora/stdin
 * @param *params ukazatel na strukturu s informaciami z prikazoveho riadku
 */
int tail(TParams *params)
{
	
	//alokacia 2D pola
	char **print = allocMatrix(params->lines, LIMIT);
	if (print == NULL)
		printError(ECODEMSG[EMALLOC], params->fr);
	//premenna do ktorej sa bude vracat vysledok z *fgets()..
	char *c = print[0];
	
	
	//citanie riadkov, pouzitie kruhoveho buffera
	long line = 0;
	if (params->lines > 0)
		while(c != NULL)
		{
			c = fgets(print[line], LIMIT, params->fr);
			//test ci sa spravne nacital riadok, ak nie tak bolo pretecenie 
			if (strlen(print[line]))
			if (print[line][strlen(print[line]) -1] != '\n' && strlen(print[line]) == LIMIT - 1)
			{
				//preskocim vstup az do konca riadku, aby som
				//zase zacinal na novom riadku
				int z = 0;
				while((z = fgetc(params->fr)) != EOF)
					if (z == '\n')
						break;
				//ulozim na koniec znak \n
				print[line][strlen(print[line]) - 1] = '\n';
				fprintf(stderr, "%s", ECODEMSG[ELIMIT]);
			}
			if (c != NULL)
				line = (line + 1) % params->lines;
		}

	if (params->lines > 0)
	{
		//vypis
		long oldLine = line;
		printf("%s", print[line]);
		line = (line + 1) % params->lines;
		while (line != oldLine)
		{
			printf("%s", print[line]);
			line = (line + 1) % params->lines;
		}
	}
	
	freeMatrix(print, params->lines);	
	return EXIT_SUCCESS;
}

/**
 * funckia funguje ako posix tail -n +number,
 * tlaci od riadku number,
 * @param *params ukazatel na strukturu s informaciami z prik. riadku 
 */
int tailFromLine(TParams *params)
{
	char *print= (char *) malloc(LIMIT * sizeof(char));
	if(print == NULL)
		printError(ECODEMSG[EMALLOC], params->fr);
	
	//nastavenie ukazatela aby neukazoval na NULL
	char *c = print;
	
	//dostane sa na poziciu riadku od ktoreho sa ma tlacit
	for (long i = 1; i < params->lines && c != NULL; i++)
	{
		c = fgets(print, LIMIT, params->fr);
		if (strlen(print) > 0)
			if (print[strlen(print) - 1] != '\n' && strlen(print) == LIMIT - 1)
			{
				//preskocim vstup az do konca riadku, aby som
				//zase zacinal na novom riadku
				int z = 0;
				while((z = fgetc(params->fr)) != EOF)
					if (z == '\n')
						break;
				fprintf(stderr, "%s", ECODEMSG[ELIMIT]);
			}
	}
	
	//nacita riadok a vytlaci ho
	while(c != NULL)
	{
		c = fgets(print, LIMIT, params->fr);
		if (strlen(print) > 0)
			if (print[strlen(print) - 1] != '\n' && strlen(print) == LIMIT - 1)
			{
				//preskocim vstup az do konca riadku, aby som
				//zase zacinal na novom riadku
				int z = 0;
				while((z = fgetc(params->fr)) != EOF)
					if (z == '\n')
						break;
				//ulozim na koniec znak \n
				print[strlen(print) - 1] = '\n';
				fprintf(stderr, "%s", ECODEMSG[ELIMIT]);
		}
		if (c != NULL)
			printf("%s", print);
	}
	
	free(print);
	
	return EXIT_SUCCESS;
}

/**
 * Hlavny program
 */
int main(int argc, char **argv)
{
	TParams params = getParams(argc, argv);
	
	if (params.ecode != EOK)
		printError(ECODEMSG[params.ecode], params.fr);
	
	if (params.state == NORMAL)
	{
		if (tail(&params) != EXIT_SUCCESS)
			printError(ECODEMSG[EUNKNOWN], params.fr);
	}
	else
		if (tailFromLine(&params) != EXIT_SUCCESS)
			printError(ECODEMSG[EUNKNOWN], params.fr);
		
	if (params.fr != stdin && params.fr != NULL)
		fclose(params.fr);
	return EXIT_SUCCESS;
}
