#include <stdio.h>
#include <math.h>
#include "chord.h"

double f1(double x);
double f2(double x);
double f3(double x);

double f1(double x) {
	return 2 * x + 4;
}
double f2(double x) {
	return x * x * x + 27;
}
double f3(double x) {
	return sin(x / 10 + 0.3);
}

int main(void) {
    ErrorCode perr;
	double result, eps = 0.0001, a = -4, b = 4;
	double ideal[] = {-2, -3, -3};
	RRfun fun[] = {f1, f2, f3};
	for(int i = 0; i < 3; i++) {
		result = chord(a, b, fun[i], eps, &perr);
        if(perr == I_OK) 
		    printf("ideal:\n%f\nresult:\n%f\n", ideal[i], result);
        else if(perr == I_NOSIGM){
            printf("Sorry, non-exisment segment\n");
            return -1;
	    }
        else if(perr == I_SMALL){
            printf("Sorry, segment is too small\n");
            return -1;
	    }
``      else if(perr == I_MUCH){
            printf("Sorry, too much iterations\n");
            return -1;
	    }
    }
    return 0;
}

