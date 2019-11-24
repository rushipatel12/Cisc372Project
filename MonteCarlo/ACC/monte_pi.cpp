/* Program to compute Pi using Monte Carlo methods */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <iostream>
#include "openacc.h"
#define a 16807
#define c 0

double randomNum(unsigned long *input){
    *input = ((a*(*input))+c)%RAND_MAX;
    return (double) (*input);
}

int main(int argc, char** argv)
{
    double start = omp_get_wtime();
    int niter = 1000000000;
    double x,y;
    int i; 
    double z;
    int gangs = 64;
	unsigned int seed[gangs];
	for(int j=0; j<gangs; j++){
		seed[j]=rand();
	}

    int *out  = new int[gangs];
    for(int b = 0; b<gangs; b++){
        out[b] = 0;
    }

   unsigned long s;
   int count = 0;
   #pragma acc parallel num_gangs(gangs) copyin(seed[0:gangs]) copyout(out[0:gangs])
   {
       out[__pgi_gangidx()] = __pgi_gangidx();
       #pragma acc loop gang reduction(+:count)
       for ( i=0; i<niter; i++) {
           s = (unsigned long)((seed[out[__pgi_gangidx()]])*i);
           x = (double)randomNum(&s)/RAND_MAX;
           y = (double)randomNum(&s)/RAND_MAX;
           z = x*x+y*y;
           if (z<=1.0) {
               count++;
               }
        }
	}

    double pi;
    pi=(double)count/niter*4;
    double total = omp_get_wtime() - start;
    printf(" Number of Trials = %d , Estimate of Pi is %f , Time Taken = %f , Number of Gangs = %d \n",niter,pi,total,gangs);
    return 0;
}
