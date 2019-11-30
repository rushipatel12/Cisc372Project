from __future__ import print_function, absolute_import

from numba import cuda
from numba.cuda.random import create_xoroshiro128p_states, xoroshiro128p_uniform_float32
import numpy as np
import time

@cuda.jit
def simulate_pi(rng_states, iterations, out):
    thread_id = cuda.grid(1)

    inside = 0
    for i in range(iterations):
        x = xoroshiro128p_uniform_float32(rng_states, thread_id)
        y = xoroshiro128p_uniform_float32(rng_states, thread_id)
        if x**2 + y**2 <= 1.0:
            inside += 1

    out[thread_id] = 4.0 * inside / iterations

t0 = time.clock()
threads_per_block = 64
blocks = 24
rng_states = create_xoroshiro128p_states(threads_per_block * blocks, seed=1)
out = np.zeros(threads_per_block * blocks, dtype=np.float32)

simulate_pi[blocks, threads_per_block](rng_states, 10000, out)
t1 = time.clock() - t0
print('pi:', out.mean())
print("TIME ELAPSED: %9.9f s" % t1)