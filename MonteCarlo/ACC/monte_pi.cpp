/* Program to compute Pi using Monte Carlo methods */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <iostream>
#include "openacc.h"
// #define m 2147483647
#define a 16807
#define c 0

double generate(unsigned long *input){
    *input = ((a*(*input))+c)%RAND_MAX;
    return (double) (*input);
}

int main(int argc, char** argv)
{
    double start = omp_get_wtime();
   int niter=1000000000;
   double x,y;
   int i; /* # of points in the 1st quadrant of unit circle */
   double z;
    int gangs = 16;
	unsigned int seed[gangs];
	for(int j=0; j<gangs; j++){
		seed[j]=rand();
	}
    int *out  = new int[gangs];
    for(int b = 0; b<gangs; b++){
        out[b] = 0;
    }
   /* initialize random numbers */
   //srand(SEED);
   unsigned long s;
   int count = 0;
   #pragma acc parallel num_gangs(gangs) copyin(seed[0:gangs]) copyout(out[0:gangs])
   {
       out[__pgi_gangidx()] = __pgi_gangidx();
   #pragma acc loop gang reduction(+:count)
   for ( i=0; i<niter; i++) {
       s=(unsigned long)((seed[out[__pgi_gangidx()]])*i);
      x = (double)generate(&s)/RAND_MAX;
      y = (double)generate(&s)/RAND_MAX;
      z = x*x+y*y;
      if (z<=1.0) count++;
      }
	}
    
	double pi;
   pi=(double)count/niter*4;
   double total = omp_get_wtime() - start;
   printf("# of trials= %d , estimate of pi is %g , time taken = %f \n",niter,pi,total);
   return 0;
}
