import numpy as np
import matplotlib.pyplot as plt

''' Number of Cores vs Speedup'''
x = [8,16,32,64,128]
y = [11.596/1.716, 11.596/.988, 11.596/.650,11.596/.452,11.596/.385]
plt.plot(x, y)
plt.xlabel("Number of Gangs")
plt.ylabel("Speed Up")
plt.title("OpenACC Paralellized Code")
plt.show()