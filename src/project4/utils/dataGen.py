# -*- coding: utf-8 -*-

import numpy as np
import random
import os

def dataGen(path, num_samples, N, M, T):
    for i in range(num_samples):
        lines = []
        with open(os.path.join(path, f'data_{N}_{i}.in'), 'w') as f:
            lines.append(f'{N} {M}')
            x = np.random.randint(1, T, size=(N))
            lines.append(' '.join(map(str, x)))
            f.write('\n'.join(lines))
            f.close()

if __name__ == '__main__':
    path = './data'
    num_samples = 1
    N = 10000
    M = random.randint(1, 1000)
    T = 10000
    dataGen(path, num_samples, N, M, T)
