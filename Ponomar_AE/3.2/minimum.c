#include <math.h>
#include <stdlib.h>
#include <stdio.h> 
#include "minimum.h"

#define MIN(a,b) ((a)<(b) ? (a) : (b))

double minimum(double xa, double xb, double E, RRFUN func)
{
	double x_minimum, x, minimum, x1, f_x1, x2, f_x2, f_xa, f_xb, f_x;
	double zolotoe_chislo = (1 + sqrt(5))/2;
	while (fabs(xa-xb) >= E)
	{
		x1 = xb - (xb-xa)/zolotoe_chislo;
		x2 = xa + (xb-xa)/zolotoe_chislo;
		f_x1 = (*func)(x1);
		f_x2 = (*func)(x2);
		if (f_x1 >= f_x2)
		{
			xa = x1;
		}
		else
		{
			xb = x2;
		}
	}

	x = (xa+xb)/2;
	f_x = (*func)(x);
	f_xa = (*func)(xa);
	f_xb = (*func)(xb);

	x_minimum = x - 0.5*((x-xa)*(x-xa)*(f_x-f_xb)-(x-xb)*(x-xb)*(f_x-f_xa))/((x-xa)*(f_x-f_xb)-(x-xb)*(f_x-f_xa));

	if ((f_xa > f_x) && (f_xb > f_x))
	{
		minimum = (*func)(x_minimum);
	}
	else
	{
		minimum = MIN(f_xa, f_xb);
	}

	return minimum;
}
	
