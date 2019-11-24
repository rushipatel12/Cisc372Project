/* Program to compute Pi using Monte Carlo methods */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <omp.h>

int main(int argc, char** argv)
{
    double start = omp_get_wtime();
    int threads = 4;
    int niter = 1000000000;
    double x,y;
    int i; 
    double z;

	int seed[threads];
	for(int j=0; j<threads; j++){
	    seed[j]=rand();
	}

   omp_set_num_threads(threads);

   int s;
   int count = 0;
   #pragma omp parallel private(s,x,y,z)shared(count,niter)
   {
       s=seed[omp_get_thread_num()];
        #pragma omp for reduction(+:count)
        for ( i=0; i<niter; i++) {
            x = (double)rand_r(&s)/RAND_MAX;
            y = (double)rand_r(&s)/RAND_MAX;
            z = x*x+y*y;
            if (z<=1) {
                count++;
            }
        }
    }
    double pi;
    pi=(double)count/niter*4;
    double total = omp_get_wtime() - start;
    printf(" Number of Trials = %d , Estimate of Pi is %f , Time Taken = %f , Number of Threads = %d \n",niter,pi,total,threads);
    return 0;
}