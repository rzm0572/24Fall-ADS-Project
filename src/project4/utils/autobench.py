import numpy as np
import subprocess
import os
import re
import time
import random
import datetime
import matplotlib.pyplot as plt
from dataGen import dataGen

now = datetime.datetime.now()
timestamp = now.strftime("%Y%m%d_%H%M%S")

MAXM = 1000
MAXT = 100000

_n = np.array([100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000])

programs = ['./build/Baseline', './build/Merge', './build/BItree']

times = 5

results = {}

# Generate data
for n in _n:
    N = n
    M = MAXM
    T_lower = min(N * M // 2, MAXT)
    T_upper = min(2 * N * M, MAXT)
    T = random.randint(T_lower, T_upper)
    dataGen("./data", times, N, M, T)

# Run benchmarks
for program in programs:
    results[program] = []
    for n in _n:
        runtime = 0
        for i in range(times):
            command = [program, str(n), str(i)]
            print(command)
            result = subprocess.run(command, capture_output=True, text=True)
            output = result.stdout.strip().split('\n')

            single_runtime = float(re.findall(r"[\d.]+", output[-1])[0])
            runtime += single_runtime
            answer = int(re.findall(r"[\d]+", output[-2])[0])

            print(datetime.datetime.now(), f"{program} {n} {i} -> ans: {answer} runtime: {single_runtime:.6f}")
            time.sleep(0.25)
        
        runtime /= times
        results[program].append(runtime)
        print(f"{program} {n} -> avg runtime: {runtime:.6f}")

print(list(map(lambda x: round(x, 6), results["./build/Baseline"])))
print(list(map(lambda x: round(x, 6), results["./build/Merge"])))
print(list(map(lambda x: round(x, 6), results["./build/BItree"])))

plt.figure(figsize=(15, 10))

for program in programs:
    plt.plot(_n, results[program], label=program, marker='D')

plt.legend()
plt.xlabel('N')
plt.ylabel('Time / s')
plt.title(f'Beautiful Subsequence')
plt.savefig(f'./result/autobench_{timestamp}.png', dpi=300)

plt.figure(figsize=(15, 10))

for program in programs:
    plt.plot(np.log10(_n), np.log10(np.array(results[program])), label=program, marker='D')

plt.legend()
plt.xlabel('lg(N)')
plt.ylabel('lg(Time / s)')
plt.title(f'Beautiful Subsequence')
plt.savefig(f'./result/autobench_lg_{timestamp}.png', dpi=300)
