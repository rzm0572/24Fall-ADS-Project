import numpy as np
import subprocess
import os
import re
import time
import datetime
import matplotlib.pyplot as plt

now = datetime.datetime.now()
timestamp = now.strftime("%Y%m%d_%H%M%S")

_n = np.linspace(1000, 15000, 29).astype(int)

programs = ['./build/Binary', './build/Fibonacci', './build/Leftist']

configures = ['custom' + str(n) for n in _n]

times = 1

results = {}

for program in programs:
    results[program] = []
    for configure in configures:
        command = [program, configure, str(times)]
        # print(command)
        result = subprocess.run(command, capture_output=True, text=True)
        output = result.stdout.strip().split('\n')[-1]
        runtime = float(re.findall(r"[\d.]+", output)[0])
        
        results[program].append(runtime)

        print(datetime.datetime.now(), f"{program} {configure} {output} -> {runtime:.6f}")
        time.sleep(0.25)

plt.figure(figsize=(15, 10))

for program in programs:
    plt.plot(_n, results[program], label=program, marker='D')

plt.legend()
plt.xlabel('VerticeNum')
plt.ylabel('Time / s')
plt.title(f'Dijkstra Optimized by Heaps')
plt.show()
plt.savefig(f'./result/autobench_{timestamp}.png', dpi=300)
