import numpy as np
import matplotlib.pyplot as plt

''' Number of Cores vs Execution Time'''
x = [1,2,4,8,16]
y = [58.42, 21.81, 10.76, 10.75, 10.59]
plt.plot(x, y)
plt.xlabel("Number of Threads")
plt.ylabel("Execution Time (Seconds)")
plt.title("OpenMP Paralellized Code")
plt.show()

import numpy as np
import matplotlib.pyplot as plt

''' Number of Cores vs Speedup'''
x = [2,4,8,16]
y = [58.42/21.81, 58.42/10.76, 58.42/10.75, 58.42/10.59]
plt.plot(x, y)
plt.xlabel("Number of Threads")
plt.ylabel("Speed Up")
plt.title("OpenMP Paralellized Code")
plt.show()