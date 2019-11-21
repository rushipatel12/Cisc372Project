/* Program to compute Pi using Monte Carlo methods */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <omp.h>

int main(int argc, char** argv)
{
   int niter=1000000000;
   double x,y;
   int i; /* # of points in the 1st quadrant of unit circle */
   double z;
	int gangs = 16;
	int vectors = 256;
	int seed[gangs*vectors];
	for(int j=0; j<gangs*vectors; j++){
		seed[j]=rand();
	}
   /* initialize random numbers */
   //srand(SEED);
   
   int s;
   int count = 0;
   #pragma acc parallel num_gangs(gangs) vector_length(vectors)
   {
   s=seed[omp_get_thread_num()];
   #pragma acc loop gang vector reduction(+:count)
   for ( i=0; i<niter; i++) {
      x = (double)rand_r(&s)/RAND_MAX;
      y = (double)rand_r(&s)/RAND_MAX;
      z = x*x+y*y;
      if (z<=1) count++;
      }
	}
	double pi;
   pi=(double)count/niter*4;
   printf("# of trials= %d , estimate of pi is %g \n",niter,pi);
   return 0;
}