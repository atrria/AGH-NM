#include <stdio.h>
#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>
void print_matrix(gsl_matrix *M, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%14f ", gsl_matrix_get(M, i, j));
		}
		printf("\n");
	}
	printf("\n");
}
void init_matrix(gsl_matrix *M, int n, int delta)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			gsl_matrix_set(M, i, j, 1.0/(i+j+delta));
		}
	}
}

int main()
{
	int signum, n=4, delta=2;
	float detA=1, maxA=0.000001, max_invA=0, wsk_uwar=0;
	gsl_matrix *A = gsl_matrix_calloc(n, n);
	gsl_matrix *invA = gsl_matrix_calloc(n, n);
	gsl_matrix *AA = gsl_matrix_calloc(n, n);
	gsl_permutation *p = gsl_permutation_calloc(n);
	
	init_matrix(A,n,delta);
	printf("Macierz A:\n");
	print_matrix(A,n);
	
	gsl_linalg_LU_decomp(A, p, &signum);
	printf("Macierz A po uruchomieniu procedury:\n");
	print_matrix(A,n);
	
	printf("Elementy diagonalne:\n");
	for(int i=0; i<n; i++)
	{
		printf("%f ", gsl_matrix_get(A, i, i));
		detA *= gsl_matrix_get(A, i, i);
	}
	printf("\n");
	
	printf("\nWyznacznik:\n%e\n", detA*signum);
	
	gsl_vector *b = gsl_vector_calloc(n);
	gsl_vector *x1 = gsl_vector_calloc(n);
	gsl_vector *x2 = gsl_vector_calloc(n);
	gsl_vector *x3 = gsl_vector_calloc(n);
	gsl_vector *x4 = gsl_vector_calloc(n);
	
	gsl_vector_set_zero(b);
	gsl_vector_set(b, 0, 1);
	gsl_linalg_LU_solve(A, p, b, x1);
	
	gsl_vector_set_zero(b);
	gsl_vector_set(b, 1, 1);
	gsl_linalg_LU_solve(A, p, b, x2);
	
	gsl_vector_set_zero(b);
	gsl_vector_set(b, 2, 1);
	gsl_linalg_LU_solve(A, p, b, x3);
	
	gsl_vector_set_zero(b);
	gsl_vector_set(b, 3, 1);
	gsl_linalg_LU_solve(A, p, b, x4);
	
	for(int i = 0; i < n; i++)
	{
		gsl_matrix_set(invA, 0, i, gsl_vector_get(x1, i));
		gsl_matrix_set(invA, 1, i, gsl_vector_get(x2, i));
		gsl_matrix_set(invA, 2, i, gsl_vector_get(x3, i));
		gsl_matrix_set(invA, 3, i, gsl_vector_get(x4, i));
	}
	
	printf("\nMacierz odwrotna:\n");
	print_matrix(invA, n);
	
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			float temp=0;
			for(int k=0; k<n; k++)
			{
				temp+=gsl_matrix_get(A, i, k)*gsl_matrix_get(invA, k, j);
			}
			gsl_matrix_set(AA, i, j, temp);	
		}
	}
	
	printf("Macierz A*A^-1:\n");
	print_matrix(AA, n);
	
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			gsl_matrix_get(A, i, j)>0?:gsl_matrix_set(A, i, j, (-1)*gsl_matrix_get(A, i, j));
			gsl_matrix_get(invA, i, j)>0?:gsl_matrix_set(invA, i, j, (-1)*gsl_matrix_get(invA, i, j));
			if(gsl_matrix_get(A, i, j)>maxA)
			{
				maxA=abs(gsl_matrix_get(A, i, j));
			}
			if(gsl_matrix_get(invA, i, j)>max_invA)
			{
				max_invA=abs(gsl_matrix_get(invA, i, j));
			}
		}
	}
	printf("Max A:\n%f", maxA);
	printf("\nMax invA:\n%f", max_invA);
	wsk_uwar=maxA*max_invA;
	printf("\nWskaznik uwarunkowania:\n %f\n", wsk_uwar);
	
	gsl_matrix_free(A);
	gsl_matrix_free(invA);
	gsl_permutation_free(p);
	gsl_vector_free(b);
	gsl_vector_free(x1);
	gsl_vector_free(x2);
	gsl_vector_free(x3);
	gsl_vector_free(x4);
	
	return 0;
}
