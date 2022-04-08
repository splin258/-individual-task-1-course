#ifndef _objects_
#define _objects_

#define _CRT_SECURE_NO_WARNINGS

#include "commons.h"

//--- ��������� ObjectsTable ��� �������� ������ � ������� �� �������
typedef struct
{
	char CountryObjects[4];             //������ � ������� ��������� ������
	char NameObject[31];                //��� �������  
	int Square;                         //������� �������

} ObjectsTable;

//----- ������ ����� ������� ������� �� ��������� �����
void ReadObjects(FILE *fin);

//������� �� ���������� ��������� ����� ������� � ������
int Parser(char *NamePattern, char *country, ObjectsTable *resultCount);

//----- ���������� �������� ObjectsTable
void sort_objects(int NumberObjects);
#endif _objects_