typedef enum {OK = 0, ERROR} ErrorCode;
#define eps 0.0000001

class Appr
{
public:
	void approximation(double(*f)(double), double* a, int N, ErrorCode E)
	{
		double S1 = 0, S2 = 0, S3 = 0, S4 = 0;
		for (int i = 0; i < N; i++)
		{
			S1 += a[i] * a[i];
			S2 += a[i];
			S3 += f(a[i]) * a[i];
			S4 += f(a[i]);
		}
		if ((S1 * N - S2 * S2) < eps)
		{
			E = ERROR;
		}
		E = OK;
		k = (S3 * N - S2 * S4) / (S1 * N - S2 * S2);
		b = (S1 * S4 - S2 * S3) / (S1 * N - S2 * S2);
	}
	double return_k()
	{
		return k;
	}
	double return_b()
	{
		return b;
	}
	double value(double x)
	{
		return k * x + b;
	}
private:
	double k;
	double b;
};
