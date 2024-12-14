import numpy as np
import random
from scipy.optimize import root_scalar
import math

def F(c, x):
    return 1 - np.exp(-c * x) - c * x * np.exp(-c * x)

def F_inv(c, y, maxx):
    if y > F(c, maxx):
        return maxx
    result = root_scalar(lambda x: F(c, x) - y, bracket=[0, maxx])
    root = result.root
    if root == 0:
        root = root + 1e-6
    return root

def generate_data(w, n, max_h):
    packages = []
    input_str = str(w) + " " + str(n) + "\n"
    for i in range(n):
        _w = random.randint(1, w)
        _h = math.ceil(F_inv(10 / max_h, random.random(), max_h))
        packages.append([_w, _h])
        input_str += str(_w) + " " + str(_h) + "\n"
    return packages, input_str

if __name__ == "__main__":
    packages, input_str = generate_data(300, 100, 50)
    print(packages)
    print(input_str)
