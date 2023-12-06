import matplotlib.pyplot as plt
import numpy as np
import os


print(os.path.dirname(__file__))

path = os.path.join(os.path.dirname(__file__), "..", "sigmaAndAsymptoticsResults3.txt")
with open(path, 'r') as file:
    lines = file.readlines()
    x_values = []
    y_values = []

    for line in lines:
        data = line.strip("\n").split(" ")
        x_values.append(int(data[0]))
        y_values.append(int(data[1]))
    

plt.plot(x_values, y_values, 'o')
# plt.xticks(range(int(min(x_values)) - 1, int(max(x_values)) + 1, 10))
# plt.yticks(range(int(min(y_values)), int(max(y_values)) + 1, 10))
plt.xlabel('n')
plt.ylabel('sigma(n) - nLog[sqrt(n) - 1]')
plt.title('Results of sigma(n) - nLog[sqrt(n) - 1]')


plt.show()