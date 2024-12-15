import matplotlib.pyplot as plt
import numpy as np
serial_time = np.array([209.264,347.82,472.776,580.501,632.119,742.925,801.97,923.116,1023.6]) # Time taken by serial implementation

numbers = np.array([1,2,3,4,5,6,7,8,9])# Number of words

plt.plot(numbers,serial_time, label='Serial')# Plotting the time taken by serial implementation
plt.xlabel('Total Number of words (1e5)')
plt.ylabel('Time (ms)')
plt.show()


