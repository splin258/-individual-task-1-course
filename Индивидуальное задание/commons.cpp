#include "commons.h"

//�������������� �������� ���� � ��������� ��� �������� ������ 
void ToUpper(char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		str[i] = toupper(str[i]);
	}
}

