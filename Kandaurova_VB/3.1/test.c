#include <stdio.h>
#include "geom.h"
#include <math.h>

double f1(double x);
double f2(double x);
double f3(double x);

double f1(double x) {
	return sin(x);
}
double f2(double x) {
	return x * x;
}
double f3(double x) {
	return cos(x);
}

int main(void) {
	double result, a = -4, b = 4, eps = 0.001;
	double ideal[] = {-1, 0, -1};
    ErrorCode perr;
    int i;
	RRfun fun[] = {f1, f2, f3};
	for(i = 0; i < 3; i++) {
		result = minim(a, b, fun[i], eps, &perr);
        if(perr == I_OK)
		    printf("ideal:\n%f\nresult:\n%f\n", ideal[i], result);
        else if(perr == I_SMALL){
            printf("Sorry, segment is too small\n");
            return -1;
        }
        else if(perr == I_MUCH){
            printf("Sorry, too much iterations\n");
            return -1;
        }
	}
    return 0;
}

