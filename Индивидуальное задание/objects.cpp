#include "objects.h"

ObjectsTable objectsArray[1000];//������ ��� ���������� ������� ������� ObjectsTable
int objectCount = 0;// ���������� ������� � �������

					//----- ������ ����� ������� ������� �� ��������� �����
void ReadObjects(FILE *fin)
{
	int NumberObjects = 0;
	scanf("%d", &NumberObjects);
	for (int i = 0; i < NumberObjects; i++)
	{
		ObjectsTable newObject;
		scanf("%s %s %d", newObject.CountryObjects, newObject.NameObject, &newObject.Square);
		ToUpper(newObject.CountryObjects);
		objectsArray[i] = newObject;
		objectCount++;
	}
	sort_objects(NumberObjects);

	fclose(fin);
}

//-------------------------------------------------------------------------------

//----- ���������� �������� ObjectsTable
//----- ��������� ���������� �� ����� CountryObjects � NameObject
void sort_objects(int NumberObjects)
{
	if (NumberObjects > 1)// ����������� ���� ����� ������� ������ 1
	{
		for (int j = 0; j< NumberObjects; j++)
		{
			for (int i = 0; i < NumberObjects - 1; i++)
			{
				// ��������� � ��������� ������� �� ������� � ��������
				if (strcmp(objectsArray[i].CountryObjects, objectsArray[i + 1].CountryObjects) > 0 || (strcmp(objectsArray[i].CountryObjects, objectsArray[i + 1].CountryObjects) == 0 && strcmp(objectsArray[i].NameObject, objectsArray[i + 1].NameObject) > 0))
				{
					ObjectsTable tmp = objectsArray[i];
					objectsArray[i] = objectsArray[i + 1];
					objectsArray[i + 1] = tmp;
				}
			}
		}
	}
}

//������� �� ���������� ��������� ����� ������� � ������
//���������� � ������ �������� resultCount �������� ���������� ��� ����������� ����������
int Parser(char *NamePattern, char *country, ObjectsTable *resultCount)
{
	int res = 0;
	for (int i = 0; i < objectCount; i++)
	{
		bool res_country = true;
		bool res_pattern = true;
		if (strcmp(country, objectsArray[i].CountryObjects) != 0)
		{
			res_country = false;
		}

		if (res_country)
		{
			for (int j = 0; NamePattern[j] != '\0' && res_pattern; j++)
			{
				if (NamePattern[j] != objectsArray[i].NameObject[j])
				{
					res_pattern = false;
					break;
				}
			}
			//������ ��������� ������� � ������
			if (res_pattern)
			{
				resultCount[res] = objectsArray[i];
				res++;
			}
		}
	}
	return res;
}