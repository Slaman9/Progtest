#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void tuPlusTuIsFor(Usek *dalnice, int zacatek, int konec, int i)
{
	int pocetKm; 
	int j, k;
	int tmpLen = 0;
	double poplatky[26];
	int meziKilometry = 0;
	int kilometry = 0;

	for (j = 0; j < 26; j++)
	{
		poplatky[j] = 0;
	}
	for(j = 0; j <= i; j++)
	{
		tmpLen = tmpLen + &dalnice[j].len;
		if (zacatek < tmpLen && konec < tmpLen) 
		{
			kilometry = tmpLen - zacatek ;
			meziKilometry = tmpLen - konec;
			kilometry = kilometry - meziKilometry;
			for (k = 0; k < 26; k++)
			{
				poplatky[k] = dalnice[j].tax[k] * kilometry;
			}
			break;
		}
		if (zacatek < tmpLen && konec > tmpLen)
		{
			kilometry = tmpLen - zacatek;
			for (k = 0; k < 26; k++)
			{
				poplatky[k] = dalnice[j].tax[k] * kilometry;
			}
			while (konec > tmpLen)
			{
				for (k = 0; k < 26; k++)
				{
					poplatky[k] = poplatky[k] + (dalnice[j].tax[k] * dalnice[j].len);
				}
			}
		
		}
		if (konec > tmpLen)
		{
			kilometry = tmpLen - konec;
			for (k = 0; k < 26; k++)
			{
				poplatky[k] = poplatky[k] + (dalnice[j].tax[k] * kilometry);
			}
			break;
		}


	}
		/*test pro vstupy*/
	for (k = 0; k < i; k++)
	{
		for (j = 0; j < 26; j++)
		{
			if (j == 0) { printf("zacatek\n"); }
			printf("%lf\n", poplatky[j]);
		}
	}
}

typedef struct usekDalnice {
	int len;
	double tax[26];
} Usek;

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
	int k;
	int tmpI = 0;
	int soucetDelek = 0;
	int zacatek = 0;
	int konec = 0;
	char tmp = '.';
	char tmpChar2 = '.';
	Usek * dalnice = (Usek*)malloc(sizeof(Usek)*lenField); /* alokuje pole*/
	if (scanf("%c", &tmp) != 1 || tmp != '{') { printf("Nespravny vstup.\n"); free(dalnice); return 1; }
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
	//for (k = 0; k < i; k++)
	//{
	//	for (j = 0; j < 26; j++)
	//	{
	//		if (j == 0) { printf("zacatek"); }
	//		printf("%lf\n", dalnice[k].tax[j]);
	//	}
	//}

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
	tuPlusTuIsFor(zacatek, konec, dalnice, i);
	free(dalnice);
	return 0;
}