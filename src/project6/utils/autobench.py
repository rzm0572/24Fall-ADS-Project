import numpy as np
from draw import draw_texture, parsing_output
from dataGen import generate_data
import random
import subprocess
import os
import datetime
from scipy.optimize import root_scalar
from matplotlib import pyplot as plt

now = datetime.datetime.now()
timestamp = now.strftime("%Y%m%d_%H%M%S")

_w = [100, 1000]
_n = [10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000]
_h = [100, 1000]

GEN = False
MAXW = 200
MAXN = 100
MAXH = 100
START = 0
TIMES = 5
Q = len(_w) * len(_n) * TIMES

programs = ['./build/BFDH', './build/FFDH', './build/NFDH']

results = [{"max_height": 0, "avg_height": 0, "avg_time": 0} for i in range(len(programs) * len(_w) * len(_n))]

if GEN:
    t = Q // len(_w)
    for i in range(Q):
        w = _w[i // t]
        h = _h[i // t]
        n = _n[i // TIMES % len(_n)]
        packages, input_str = generate_data(w, n, h)
        with open(f"./data/input_{i + START}.txt", "w") as f:
            f.write(input_str)
            f.close()

for program in programs:
    for i in range(Q):
        w, n = 0, 0
        input_data = ""
        with open(f"./data/input_{i + START}.txt") as f:
            input_data = f.read()
            input_size = input_data.strip().split('\n')[0].strip().split()
            w, n = int(input_size[0]), int(input_size[1])
            f.close()
        command = [program]
        print(command)
        result = subprocess.run(command, input = input_data, capture_output=True, text=True)
        output = result.stdout
        h, textures, time = parsing_output(output)

        index = (programs.index(program) * len(_w) + _w.index(w)) * len(_n) + _n.index(n)

        if h > results[index]["max_height"]:
            results[index]["max_height"] = h
        
        results[index]["avg_height"] += h
        results[index]["avg_time"] += time

        # if textures != []:
        #     draw_texture(w, h, textures, f"./result/output_{os.path.basename(program)}_{i + START}.png")
        
        print(f"Index: {index}, Program: {program}, Input: {i + START}, Weight: {w}, Height: {h}, Time: {time:.6f}")

print("\n\nResults:")

for i in range(len(results)):
    program = programs[i // (len(_w) * len(_n))]
    w = _w[i // len(_n) % len(_w)]
    n = _n[i % len(_n)]
    results[i]["avg_height"] /= TIMES
    results[i]["avg_time"] /= TIMES
    # print(results[i])
    print(f"Program: {program}, Weight: {w}, Num: {n:<5}\t, Max Height: {results[i]['max_height']}\t, Avg Height: {results[i]['avg_height']}\t, Time: {results[i]['avg_time']:.6f}")

mh = [{'./build/BFDH': [], './build/FFDH': [], './build/NFDH': []} for i in range(len(_w))]
ah = [{'./build/BFDH': [], './build/FFDH': [], './build/NFDH': []} for i in range(len(_w))]
at = [{'./build/BFDH': [], './build/FFDH': [], './build/NFDH': []} for i in range(len(_w))]

for i in range(len(results)):
    program = programs[i // (len(_w) * len(_n))]
    index_w = i % (len(_w) * len(_n)) // len(_n)
    mh[index_w][program].append(results[i]['max_height'])
    ah[index_w][program].append(results[i]['avg_height'])
    at[index_w][program].append(results[i]['avg_time'])

color = ['r', 'g', 'b']

for index_w in range(len(_w)):
    f = plt.figure()
    for program in programs:
        index = programs.index(program)
        plt.plot(_n, mh[index_w][program], label=program + " Max Height", color=color[index], linestyle='--')
        plt.plot(_n, ah[index_w][program], label=program + " Avg Height", color=color[index])

    plt.title(f"Max Height and Avg Height, Weight = {_w[index_w]}")
    plt.xlabel("N")
    plt.ylabel("h")
    plt.legend()
    plt.savefig(f"./result/max_height_avg_height_{_w[index_w]}.png")

    plt.clf()

    for program in programs:
        index = programs.index(program)
        plt.plot(_n, at[index_w][program], label=program + " Time", color=color[index])
    plt.title(f"Time, Weight = {_w[index_w]}")
    plt.xlabel("N")
    plt.ylabel("Time / s")
    plt.legend()
    plt.savefig(f"./result/time_{_w[index_w]}.png")

