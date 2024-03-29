/* Program to compute Pi using Monte Carlo methods */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <omp.h>
#define SEED 35791246

int main(int argc, char** argv)
{
   double start = omp_get_wtime();
   int niter = 1000000000;
   double x,y;
   int i,count=0; 
   double z;
   double pi;
   srand(SEED);
   count=0;
   for ( i=0; i<niter; i++) {
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      z = x*x+y*y;
      if (z<=1){
         count++;
      }
   }
   pi=(double)count/niter*4;
   double total = omp_get_wtime() - start;
   printf("Number of Trials = %d , Estimate of Pi is %f , Time Taken = %f \n",niter,pi,total);
   return 0;
}