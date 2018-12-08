#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct usekDalnice {
	int len;
	double tax[26];
} Usek;



void tuPlusTuIsFor(Usek *dalnice, int zacatek, int konec, int i)
{
	int j, k;
	int tmpLen = 0;
	double poplatkyK[26];
	double poplatkyZ[26];
	double poplatky[26];
	int meziKilometry = 0;
	int kilometry = 0;
	char pismena = 'A';

	for (j = 0; j < 26; j++)
	{
		poplatkyZ[j] = 0;
		poplatkyK[j] = 0;
		poplatky[j] = 0;
	}
	if (zacatek < dalnice[1].len && konec < dalnice[1].len)
	{
		kilometry = dalnice[1].len - zacatek;
		meziKilometry = dalnice[1].len - konec;
		kilometry = kilometry - meziKilometry;
		for (k = 0; k < 26; k++)
		{
			poplatky[k] = dalnice[j].tax[k] * kilometry;
		}
	
	}
	for (j = 0; j <= i; j++)	//spocita poplatky od 0 do konce cesty
	{
		tmpLen = tmpLen + dalnice[j].len;
		if (konec > tmpLen)
		{
			for (k = 0; k < 26; k++)
			{
				poplatkyK[k] = poplatkyK[k] + (dalnice[j].tax[k] * dalnice[j].len);
			}
		}
		if (konec < tmpLen)
		{
			for (k = 0; k < 26; k++)
			{
				poplatkyK[k] = poplatkyK[k] + (dalnice[j].tax[k] * (tmpLen - konec));
			}

		}
	}
	tmpLen = 0;
	for (j = 0; j <= i; j++)	//spocita poplatky do zacatku cesty
	{
		tmpLen = tmpLen + dalnice[j].len;
		if (zacatek > tmpLen)
		{
			for (k = 0; k < 26; k++)
			{
				poplatkyZ[k] = poplatkyZ[k] + (dalnice[j].tax[k] * dalnice[j].len);
			}
		}
		if (zacatek < tmpLen)
		{
			for (k = 0; k < 26; k++)
			{
				poplatkyZ[k] = poplatkyZ[k] + (dalnice[j].tax[k] * (tmpLen - zacatek));
			}
		}
	}
	for (k = 0; k < 26; k++) // spocita finalni cenu
	{
		poplatky[k] = poplatkyK[k] - poplatkyZ[k];
	}
		/*test pro vystup*/
	for (j = 0; j < 26; j++)
	{
		if (poplatky[j] > 0)
		{
			printf(" %c=%lf", (pismena + j), poplatky[j]);
		}
	}
}



void realokace(Usek *dalnice, int lenField)
{
	lenField = lenField + 10;
	dalnice = (Usek*)realloc(dalnice, sizeof(Usek)*lenField);
}


int main(void)
{
	int lenField = 10;
	int i;
	int j;

	int tmpI = 0;
	int soucetDelek = 0;
	int zacatek = 0;
	int konec = 0;
	char tmp = '.';
	char tmpChar2 = '.';
	Usek * dalnice = (Usek*)malloc(sizeof(Usek)*lenField); /* alokuje pole*/
	printf("Myto:\n");
	if (scanf("%c", &tmp) != 1 || tmp != '{') { printf("Nespravny vstup.\n"); free(dalnice); return 1; }
	// nacita vstupy
	for (i = 0; i <= lenField; i++)
	{
		if (i == 0)
		{
			for (j = 0; j < 26; j++)
			{
				dalnice[i].tax[j] = 0 ;
			}
		}
		if (i >= 1)
		{
			for (j = 0; j < 26; j++)
			{
				dalnice[i].tax[j] = dalnice[i - 1].tax[j];
			}
		}
		if (scanf(" [ %d : ", &dalnice[i].len) != 1) { printf("Nespravny vstup.\n"); free(dalnice); return 2; }
		soucetDelek = soucetDelek + dalnice[i].len;
		while (scanf(" %c ", &tmp) == 1)
		{
			scanf(" = %lf %c", &dalnice[i].tax[tmp - 'A'], &tmpChar2);
			if (tmpChar2 == ']') { break; }
		}
		if (i == lenField - 1)
		{
			realokace(dalnice, lenField);
		}
		if (scanf(" %c", &tmp) == 1 && tmp == '}') { break; }
		else if (tmp != ',') { printf("Nespravny vstup.\n"); free(dalnice); return 3; }
	}
	/*test pro vstupy*/
	// int k;
	//for (k = 0; k <= i; k++)
	//{
	//	for (j = 0; j < 26; j++)
	//	{
	//		if (j == 0) { printf("zacatek\n"); }
	//		printf("%lf\n", dalnice[k].tax[j]);
	//	}
	//}

	//nacita 2. vstup
	printf("Hledani:\n");
	if (scanf(" %d %d", &zacatek, &konec) != 2) { printf("Nespravny vstup.\n"); free(dalnice); return 4; }
	if (zacatek < 0 || zacatek == konec || konec < 0 || zacatek > soucetDelek || konec > soucetDelek) 
		{ printf("Nespravny vstup.\n"); free(dalnice); return 5; }
	if (konec < zacatek)
	{
		tmpI = konec;
		konec = zacatek;
		zacatek = tmpI;
	}
	//pocita cenu 
	tuPlusTuIsFor(dalnice, zacatek, konec, i);
	free(dalnice);
	return 0;
}