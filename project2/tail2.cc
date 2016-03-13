
/**
 * Encoding:    utf8
 * File:        tail2.cc
 * Compiled:    g++ 4.4
 * Name:        Pavol Loffay, xloffa00@stud.fit.vutbr.cz
 * Faculty:     FIT VUTBR
 * Project:     DU2/a for IJC
 * Date:        2.4.2011
*/

//strtoul, EXIT_SUCCESS, EXIT_FAILURE, exit()
#include <cstdlib>
//errno
#include <cerrno>
//numeric_limits<unsigned int>::min()
#include <limits>
//strcmp()
#include <cstring>
//getline,   cout, cerr
#include <iostream>
//buffer - fronta
#include <deque>
//praca zo suborom
#include <fstream>

//tail bez parametru -n number,,, znamena ze sa ma tlacit 10 riadkov
//pouzitie taktiez pri strtol(,,DEFAULT)
#define DEFAULT 10

using namespace std;

//chybove stavy programu
enum tecodes
{
	EOK = 0,
	ECLWRONG
};

//stavy programu
enum tstates
{
	//tlaci sa n-ty pocet riadkov
	NORMAL = 0,
	//bude sa tlacit od riadku s urcitym cislom
	FROMLINE
};

//struktura obsahujuca informacia o stave, chybach, programu
//ukladaju sa do nej informacia z prik. riadku
typedef struct params
{
	//stav
	int state;
	//chybove hlasenie
	int ecode;
	unsigned long lines;
	//oznacuje ci sa bude citat z stdin
	bool stdinn;
	istream *fr;
}TParams;

/**
 * Funkcie
 */
int lines(char argv[], TParams *params);
TParams getParams(int argc, char **argv);
int tail(TParams *params);
int tailFromLine(TParams *params);
void printError(const char *mesg);

void printError(const char *mesg)
{
	cerr << mesg;
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
	params->lines = strtoul(argv, NULL, DEFAULT);
	
	if ((errno == ERANGE && (params->lines == numeric_limits<unsigned long>::max())) || params->lines < 0) 
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

/**
 * funkcia spracuje parametre prik. riadku a ulozi do struktury typu TParams
 */
TParams getParams(int argc, char **argv)
{
	//inicializacia struktury
	TParams params;
		params.ecode = EOK;
		params.state = NORMAL;
		params.lines = DEFAULT;
		params.stdinn = true;
		params.fr = &cin;
		
	if (argc == 1)
		params.ecode = EOK;
	else
		if (argc == 2)
		{
			fstream *file = new fstream();
			file->open(argv[1], ios::in);
			if(!*file)
			{
				delete file;
				printError("Nepodarilo sa otvorit subor!\n");
			}
			params.fr = file;
			params.stdinn = false;
			
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
						if(lines(argv[2], &params) != EXIT_SUCCESS)
							params.ecode = ECLWRONG;
						else
						{
							//otvorenie suboru
							fstream *file = new fstream();
							file->open(argv[3], ios::in);
							if(!*file)
							{
								delete file;
								printError("Nepodarilo sa otvorit subor!\n");
							}
							params.fr = file;
							params.stdinn = false;
						}
					}
					else
						params.ecode = ECLWRONG;
				}
				else
					params.ecode = ECLWRONG;
	return params;
}


/**
 * funckia funguje ako POSIX tail, vypise 0-.. poslednych riadkov subora/stdin
 * @param *params ukazatel na strukturu s informaciami z prikazoveho riadku
 */
int tail(TParams *params)
{
	//ak sa ma vypisat 0 riadkov tak nevypise nic
	if(params->lines == 0)
		return EXIT_SUCCESS;
	
	deque<string> dq;
	string line;
		
	//cyklus cita zo suboru/stdin riadky a ukada ich do buffera
	//ukladam polozky na koniec buffera a nasledne odoberam zo zaciatku
	//koli tomu aby osm ich mal nasledne spravne zoradene.
	while(getline(*(params->fr),line))
	{
		
		//odstranenie polozky zo zaciatku buffera
		if (dq.size() == params->lines)
			dq.pop_front();
		
		//ulozenie polozky na koniec buffera
		dq.push_back(line);
	}
	
	//vypis buffera
	for(deque<string>::iterator it = dq.begin(); it != dq.end(); it++)
		cout << *it << endl;
	
	return EXIT_SUCCESS;
}

/**
 * funckia funguje ako posix tail -n +number,
 * tlaci od riadku number,
 * @param *params ukazatel na strukturu s informaciami z prik. riadku 
 */
int tailFromLine(TParams *params)
{
	string line;
	
	unsigned long counter = 1;
	
	while(getline(*(params->fr), line))
	{
		//podmienka preskoci +n prvych riadkov 
		if (counter < params->lines)
		{
			counter++;
			continue;
		}
		else
			//vypis riadkov
			cout << line << endl;
	}
	
	return EXIT_SUCCESS;
}

/**
 * Hlavny program
 */
int main(int argc, char **argv)
{
	TParams params = getParams(argc, argv);
	
	if (params.ecode != EOK)
		printError("Zle parametre prikazoveho riadku!\n");
	
	if (params.state == NORMAL)
		tail(&params);
	else
		tailFromLine(&params);
	
	//zavretie subora
	if (params.stdinn == false)
	{	
		//pretypovanie na fstream z istream
		static_cast<fstream*>(params.fr)->close();
		//odstrananie objektu
		delete params.fr;
	}
	return EXIT_SUCCESS;
}
