#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 1

int INCLUDE(char *progname, char *filename);
int INCLUDE(char *progname, char *filename)
{
	FILE *prog;
	FILE *file;
	char **A;
	char c;
	int N, i;
	char *incl = 0;
	int kNUM1, kNUM2;

	//open file progname
	if ((prog = fopen(progname, "r")) == NULL)
	{
		printf("Can't open file' %s\n", progname);
		return -1;
	}

	// create string "#include filename"
	incl = (char*)malloc((strlen("#include ") + strlen(filename) + 1) * sizeof(char));
	strcpy(incl, "#include ");
	strcpy(incl + strlen("#include "), filename);

	// create array of strings
	// A[i] - string in prog or contents of the file
	A = (char**)malloc(NUM * sizeof(char*));
	A[0] = (char*)malloc(NUM * sizeof(char));
	A[0][0] = 0;
	kNUM1 = kNUM2 = NUM;

	N = 0;
	while (fscanf(prog, "%c", &c) == 1)
	{
		printf("\\%c/", c);
		// write char to the string
		if ((strlen(A[N]) + 2) > kNUM2)
		{
			kNUM2 += NUM;
			A[N] = (char*)realloc(A[N], kNUM2 * sizeof(char));
		}
		A[N][strlen(A[N]) + 1] = 0;
		A[N][strlen(A[N])] = c;

		// if c == '\n' check equal to "#include filename" and create new string
		if (c == '\n')
		{
			printf("JuSt HaLlOw\n");
			// check equal to "#include filename"
			if (A[N] == strstr(A[N], incl))
			{
				printf("JuSt HaW aRe YoU?\n");
				// open filename
				if ((file = fopen(filename, "r")) == NULL)
				{
					free(incl);
					fclose(prog);
					i = 0;
					while (i <= N)
					{
						free(A[i]);
						i++;
					}
					free(A);
					printf("Can't open file %s\n", filename);
					return -2;
				}

				// clear A[N] ("#include filename")
				free(A[N]);
				A[N] = (char*)malloc(NUM * sizeof(char));
				A[N][0] = 0;
				kNUM2 = NUM;
				printf("JuSt HaW aRe YoU? - 2\n");
				// write contents of the file to the A[N]
				fscanf(file, "%c", &c);
				printf("<%c>", c);
				if ((strlen(A[N]) + 2) > kNUM2)
				{
					kNUM2 += NUM;
					A[N] = (char*)realloc(A[N], kNUM2 * sizeof(char));
				}
				A[N][strlen(A[N]) + 1] = 0;
				A[N][strlen(A[N])] = c;
				while (fscanf(file, "%c", &c) == 1)
				{
					printf("<%c>", c);
					if ((strlen(A[N]) + 2) > kNUM2)
					{
						kNUM2 += NUM;
						A[N] = (char*)realloc(A[N], kNUM2 * sizeof(char));
					}
					A[N][strlen(A[N]) + 1] = 0;
					A[N][strlen(A[N])] = c;
				}

				// old A[N] ended with '\n' so we must write it
				c = '\n';
				if ((strlen(A[N]) + 2) > kNUM2)
				{
					kNUM2 += NUM;
					A[N] = (char*)realloc(A[N], kNUM2 * sizeof(char));
				}
				A[N][strlen(A[N]) + 1] = 0;
				A[N][strlen(A[N])] = c;

				fclose(file);
			}

			// create new string
			if ((N + 2) > kNUM1)
			{
				kNUM1 += NUM;
				A = (char**)realloc(A, kNUM1 * sizeof(char*));
			}
			N++;
			A[N] = (char*)malloc(NUM * sizeof(char));
			A[N][0] = 0;
		}
	}

	// most probably last A[N] don't ended with '\n' so we must check its equal to "#include filename"
	if (strlen(A[N]) != 0)
		if (A[N] == strstr(A[N], incl) && (A[N][strlen(A[N]) - 1] != '\n'))
		{
			if ((file = fopen(filename, "r")) == NULL)
			{
				free(incl);
				fclose(prog);
				i = 0;
				while (i <= N)
				{
					free(A[i]);
					i++;
				}
				free(A);
				printf("Can't open file %s\n", filename);
				return -2;
			}

			free(A[N]);
			A[N] = (char*)malloc(NUM * sizeof(char));
			A[N][0] = 0;
			kNUM2 = NUM;
			while (fscanf(file, "%c", &c) == 1)
			{
				printf("\\%c/", c);
				if ((strlen(A[N]) + 2) > kNUM2)
				{
					kNUM2 += NUM;
					A[N] = (char*)realloc(A[N], kNUM2 * sizeof(char));
				}
				A[N][strlen(A[N]) + 1] = 0;
				A[N][strlen(A[N])] = c;
			}
			fclose(file);
		}
	fclose(prog);

	//write all
	//prog = fopen(progname, "w");
	i = 0;
	while (i <= N)
	{
		printf("%s", A[i]);
		i++;
	}

	//fclose(prog);
	i = 0;
	while (i <= N)
	{
		free(A[i]);
		i++;
	}
	free(A);
	free(incl);
	return 0;
}

int main(void)
{
	char *filename = "input.txt";
	char *progname = "programm.txt";

	INCLUDE(progname, filename);

	return 0;
}
