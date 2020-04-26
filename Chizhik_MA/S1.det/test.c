#include <stdio.h>
#include <stdlib.h>

#include "../lib/ustrings.h"
#include "determinant.h"

#define in "input.txt"
#define ans "answer.txt"
#define matrix(order, i, j) matrix[(order) * (i) + (j)]

int main(void) {
	FILE *input, *answer;
	int order;
	char **matrix, *result, *correct;

	if ((input = fopen(in, "r")) == NULL) {
		fprintf(stderr, "Can't read %s\n", in);
		return -1;
	}

	if ((answer = fopen(ans, "r")) == NULL) {
		fprintf(stderr, "Can't read %s\n", ans);
		fclose(input);
		return -1;
	}

	if (fscanf(input, "%d\n", &order) != 1) {
		fprintf(stderr, "Can't read the order of the matrix\n");
		fclose(input);
		fclose(answer);
		return -1;
	}

	if ((matrix = (char **)malloc(order * order * sizeof(char *))) == NULL) {
		fprintf(stderr, "Malloc can't allocate enough memory\n");
		fclose(input);
		fclose(answer);
		return -1;
	}

	for (int i = 0; i < order * order; i++) {
		if ((matrix[i] = read_string(input)) == NULL) {
			fprintf(stderr, "Can't read the matrix properly\n");
			fclose(input);
			fclose(answer);

			for (int j = 0; j < i; j++) {
				free(matrix[j]);
			}
			free(matrix);
			return -1;
		}
	}
	fclose(input);

	if ((correct = read_string(answer)) == NULL) {
		fprintf(stderr, "Can't read the correct answer\n");
		fclose(answer);
		free_1d_matrix(matrix, order);
		return -1;
	}
	fclose(answer);

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			fprintf(stdout, "%s\t", matrix(order, i, j));
		}
		fprintf(stdout, "\n");
	}

	free_1d_matrix(matrix, order);
	return 0;
}
