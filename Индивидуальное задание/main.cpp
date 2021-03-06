#define _CRT_SECURE_NO_WARNINGS

#include"objects.h"
#include"commons.h"


//--- ????????? TaxTable ??? ???????? ?????? ? ??????? ?? ????? ????? ? ??????? 
typedef struct {
	char Country[4];            //?????? ??? ??????? ????? ? ?????? ?????????????
	int Tax;                    //?????
	double rate[18];            //????
	int rateChangesDate[18];    //????????? ?????
}TaxTable;


TaxTable countryArray[50];
int countryCount = 0;



// ????? ?????? ??? ??????? ??????????? ?????? ? ???????????? ?? ??????
int GetIndexCountry(char *name)
{
	for (int i = 0; i < countryCount; i++)
	{
		if (!strcmp(name, countryArray[i].Country))
		{
			return i;
		}
	}
	return -1;
}

//----- ?????? ????? ??????? ??????? ?? ???????? ?????
void ReadTaxTable(FILE *fin)
{
	scanf("%d", &countryCount);
	for (int i = 0; i < countryCount; i++)
	{
		scanf("%s %d", countryArray[i].Country, &countryArray[i].Tax);
		ToUpper(countryArray[i].Country);
	}
	int c = 0;
	scanf("%d", &c);
	for (int i = 0; i < c; i++)
	{
		char name[4];
		int day;
		int month;
		int year;
		double rate;
		scanf("%s %d.%d.%d %lf", name, &day, &month, &year, &rate);
		ToUpper(name);
		if (GetIndexCountry(name) != -1)
		{
			int date = year * 10000 + month * 100 + day;
			for (int j = year - 2000; j < 18; j++)
			{
				if (countryArray[GetIndexCountry(name)].rateChangesDate[j] < date)
				{
					countryArray[GetIndexCountry(name)].rateChangesDate[j] = date;
					countryArray[GetIndexCountry(name)].rate[j] = rate;
				}
			}
		}
	}
}

int main()
{
	// ??????? ??????? ?????
	if (freopen("input02.txt", "rt", stdin) == NULL)
	{
		printf("Error open input.txt file");
		exit(1);
	}
	if (freopen("objects.txt", "rt", stdin) == NULL)
	{
		printf("Error open objects.txt file");
		exit(1);
	}
	if (freopen("output02.txt", "wt", stdout) == NULL)
	{
		printf("Error open output.txt file");
		exit(1);
	}
	freopen("objects.txt", "r", stdin);

	ReadObjects(stdin);

	fclose(stdin);
	freopen("input02.txt", "r", stdin);

	ReadTaxTable(stdin);


	char operation[4];
	char pattern[31];
	char Country[4];
	int beg;
	int end;
	double currency;
	scanf("%s FOR %s IN %s FROM %d TO %d", operation, pattern, Country, &beg, &end);        //?????? ???????
	fclose(stdin);

	freopen("output02.txt", "w", stdout);
	ToUpper(Country);
	ObjectsTable parseResult[1000];
	//?????? ????????? ???????
	int resultCount = Parser(pattern, Country, parseResult);
	//?????????? ?????? ? ??????? ??? ??????? ??????????? ??????
	TaxTable region = countryArray[GetIndexCountry(Country)];
	//????????? ???????? ? ?????? ???????? ? ????
	if (!strcmp("ALL", operation))
	{
		printf("%d", resultCount*(end - beg + 1));
		for (int i = 0; i < resultCount; i++)
		{
			for (int j = beg - 2000; j <= end - 2000; j++)
			{
				if (j<17)
				{
					printf("\n%10d %3s %-30s %15.2lf %4d-%4d", i*(end - beg + 1) + j - beg + 2001, Country, parseResult[i].NameObject, parseResult[i].Square*region.Tax*region.rate[j], 2000 + j, 2000 + j);
				}
				else
				{
					printf("\n%10d %3s %-30s %15.2lf %4d-%4d", i*(end - beg + 1) + j - beg + 2001, Country, parseResult[i].NameObject, parseResult[i].Square*region.Tax*region.rate[17], 2000 + j, 2000 + j);
				}

			}
		}
	}
	else if (!strcmp("MAX", operation))
	{

		printf("%d", resultCount);
		for (int i = 0; i < resultCount; i++)
		{
			double max = -1;
			for (int j = beg - 2000; j <= end - 2000; j++)
			{

				if (j<17)
				{
					currency = parseResult[i].Square*region.Tax*region.rate[j];
				}
				else
				{
					currency = parseResult[i].Square*region.Tax*region.rate[17];
				}
				if (currency > max)
				{
					max = currency;
				}
				if (j > 17)
				{
					break;
				}
			}
			printf("\n%10d %3s %-30s %15.2lf %4d-%4d", i + 1, Country, parseResult[i].NameObject, max, beg, end);
		}
	}
	else if (!strcmp("AVG", operation))
	{
		printf("%d", resultCount);
		for (int i = 0; i < resultCount; i++)
		{
			double sum = 0;
			for (int j = beg - 2000; j <= end - 2000; j++)
			{

				if (j<17)
				{
					sum += parseResult[i].Square*region.Tax*region.rate[j];
				}
				else
				{
					sum += parseResult[i].Square*region.Tax*region.rate[17];
				}
			}
			printf("\n%10d %3s %-30s %15.2lf %4d-%4d", i + 1, Country, parseResult[i].NameObject, sum / (end - beg + 1), beg, end);
		}
	}
	else if (!strcmp("SUM", operation))
	{
		printf("%d", resultCount);
		for (int i = 0; i < resultCount; i++)
		{
			double sum = 0;
			for (int j = beg - 2000; j <= end - 2000; j++)
			{

				if (j<17)
				{
					sum += parseResult[i].Square*region.Tax*region.rate[j];
				}
				else
				{
					sum += parseResult[i].Square*region.Tax*region.rate[17];
				}
			}
			printf("\n%10d %3s %-30s %15.2lf %4d-%4d", i + 1, Country, parseResult[i].NameObject, sum, beg, end);
		}
	}
	else
	{
		printf("%d", resultCount);
		for (int i = 0; i < resultCount; i++)
		{
			double min = -1;
			for (int j = beg - 2000; j <= end - 2000; j++)
			{

				if (j<17)
				{
					currency = parseResult[i].Square*region.Tax*region.rate[j];
				}
				else
				{
					currency = parseResult[i].Square*region.Tax*region.rate[17];
				}
				if (currency < min || min < 0)
				{
					min = currency;
				}
				if (j > 17)
				{
					break;
				}
			}
			printf("\n%10d %3s %-30s %15.2lf %4d-%4d", i + 1, Country, parseResult[i].NameObject, min, beg, end);
		}
	}
	return 0;
}