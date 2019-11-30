from __future__ import print_function, absolute_import
import math
import random
import sys
import time

def simulate_pi(count):
    print("Approximating Pi!")
    circleCt = 0;
    TOTAL_NUMS = count
    
    t0 = time.clock()
    for i in range(TOTAL_NUMS):
        x = random.random()
        y = random.random()   

        if x**2 + y**2 <= 1.0:
            circleCt = circleCt + 1
        
    t1 = time.clock() - t0
    pi_approx = 4 * (circleCt / float(TOTAL_NUMS))
    print("TIME ELAPSED: %.9f s" % t1)
    print("this is our approximation of pi based on %5d randomly generated points: %1.20f" % (TOTAL_NUMS,pi_approx))
        



simulate_pi(int(sys.argv[1]))