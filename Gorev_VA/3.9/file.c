#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int INCLUDE(char *progname, char *filename)
{
	FILE *prog;
	FILE *file;
	char **A;
	char c;
	int N, i;
	char *incl = 0;
	
	//open file progname
	if ((prog = fopen(progname, "r")) == NULL)
	{
		printf("Íå óäàëîñü îòêðûòü ôàéë %s\n", progname);
		return -1;
	}
	
	// create string "#include filename"
	incl = (char*)malloc((strlen("#include ") + strlen(filename) + 1) * sizeof(char));
	strcpy(incl, "#include ");
	strcpy(incl + strlen("#include "), filename);
	
	// create array of strings
	// A[i] - string in prog or contents of the file
	A = (char**)malloc(sizeof(char*));
	A[0] = (char*)malloc(sizeof(char));
	A[0][0] = 0;
	
	N = 0;
	while (fscanf(prog, "%c", &c) == 1)
	{
		// write char to the string
		A[N] = (char*)realloc(A[N], (strlen(A[N]) + 2) * sizeof(char));
		A[N][strlen(A[N]) + 1] = 0;
		A[N][strlen(A[N])] = c;
		
		// if c == '\n' check equal to "#include filename" and create new string
		if (c == '\n')
		{
			// check equal to "#include filename"
			if (A[N] == strstr(A[N], incl))
			{
				// open filename
				if ((file = fopen(filename, "r")) == NULL)
				{
					free(incl);
					fclose(prog);
					i = 0;
					while (i <= N)
					{
						printf("%s", A[i]);
						i++;
					}
					free(A);
					printf("Íå óäàëîñü îòêðûòü ôàéë %s\n", filename);
					return -2;
				}
				
				// clear A[N] ("#include filename")
				free(A[N]);
				A[N] = (char*)malloc(sizeof(char));
				A[N][0] = 0;
				
				// write contents of the file to the A[N]
				while (fscanf(file, "%c", &c) == 1)
				{
					A[N] = (char*)realloc(A[N], (strlen(A[N]) + 2) * sizeof(char));
					A[N][strlen(A[N]) + 1] = 0;
					A[N][strlen(A[N])] = c;
				}
				
				// old A[N] ended with '\n' so we must write it
				c = '\n';
				A[N] = (char*)realloc(A[N], (strlen(A[N]) + 2) * sizeof(char));
				A[N][strlen(A[N]) + 1] = 0;
				A[N][strlen(A[N])] = c;
				
				fclose(file);
			}
			
			// create new string
			A = (char**)realloc(A, (N + 2) * sizeof(char*));
			N++;
			A[N] = (char*)malloc(sizeof(char));
			A[N][0] = 0;
		}
	}
	
	// most probably last A[N] don't ended with '\n' so we must check its equal to "#include filename"
	if (A[N][strlen(A[N]) - 1] != '\n')
		if (A[N] == strstr(A[N], incl))
		{
			if ((file = fopen(filename, "r")) == NULL)
			{
				free(incl);
				fclose(prog);
				i = 0;
				while (i <= N)
				{
					printf("%s", A[i]);
					i++;
				}
				free(A);
				printf("Íå óäàëîñü îòêðûòü ôàéë %s\n", filename);
				return -2;
			}
			
			free(A[N]);
			A[N] = (char*)malloc(sizeof(char));
			A[N][0] = 0;
			while (fscanf(file, "%c", &c) == 1)
			{
				A[N] = (char*)realloc(A[N], (strlen(A[N]) + 2) * sizeof(char));
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
	free(incl);
	i = 0;
	while (i <= N)
	{
		free(A[i]);
		i++;
	}
	free(A);
	return 0;
}

int main(void)
{
	char *filename = "input.txt";
	char *progname = "programm.txt";	
	
	INCLUDE(progname, filename);
	
	return 0;
}
