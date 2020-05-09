#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

char **ar_of_words(FILE* input)
{
	char **A;
	char c;
	char *str;
	int i = 0, j = 0, I, J;
	A = (char**)malloc(1 * sizeof(char*));
	A[0] = (char*)malloc(1 * sizeof(char));
	A[0][0] = 0;
	//i - ����� �������, � ������� �� ����� ����������
	//j - ����� �����, ������� �� ����� ����������, � �������

	while ((fscanf(input, "%c", &c) == 1)) // ��������� ������
	{
		// ���� ��� ���������� ������, �� ��� ���� �������� � �����
		if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')))
		{
			A[i] = (char*)realloc(A[i], (j + 2) * sizeof(char));
			A[i][j] = c;
			j++;
			A[i][j] = 0;
		}
		else
			if (j > 0) // ���� ������ ������������ � �� ��� �� ��������� ������ �����, �� ��� ����� ���������
			{
				A = (char**)realloc(A, (i + 2) * sizeof(char*));
				i++;
				j = 0;
				A[i] = (char*)malloc(1 * sizeof(char));
				A[i][0] = 0;
			}
	}
	// �� ������ ������ � ����� ����� �������� ������ ������
	if (j > 0)
	{
		A = (char**)realloc(A, (i + 2) * sizeof(char*));
		i++;
		j = 0;
		A[i] = (char*)malloc(1 * sizeof(char));
		A[i][0] = 0;
	}

	// ����������
	I = i - 1;
	while (I > 0)
	{
		J = 0;
		while (J < I)
		{
			if (strcmp(A[J], A[J + 1]) > 0)
			{
				str = A[J];
				A[J] = A[J + 1];
				A[J + 1] = str;
			}
			J++;
		}
		I--;
	}

	return A;
}