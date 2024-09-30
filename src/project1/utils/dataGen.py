import random

# 生成题目所需的三类数据，并且保存到 data 目录下
# 对于不同的数据规模 N，生成的数据文件为以下三个：
# 1. data/data_same_N.in: Insert N integers in increasing order and delete them in the same order
# 2. data/data_reverse_N.in: Insert N integers in increasing order and delete them in the reverse order
# 3. data/data_random_N.in: Insert N integers in random order and delete them in random order

# 数据文件格式：
# line 1: N(integer)
# line 2 to N+1: optype(0: insert, 1: delete) key(integer) value(integer, optional)

def generate_data(N, datatype):
    with open(f"data/data_{datatype}_{N}.in", "w+") as f:
        lines = [str(N)]
        if datatype == "same":
            for i in range(1, N+1):
                lines.append(f"0 {i} {random.randint(0, 100)}")
            for i in range(1, N+1):
                lines.append(f"1 {i}")
        if datatype == "reverse":
            for i in range(1, N+1):
                lines.append(f"0 {i} {random.randint(0, 100)}")
            for i in range(N, 0, -1):
                lines.append(f"1 {i}")
        if datatype == "random":
            seq = [i for i in range(1, N+1)]
            random.shuffle(seq)
            for i in seq:
                lines.append(f"0 {i} {random.randint(0, 100)}")
            random.shuffle(seq)
            for i in seq:
                lines.append(f"1 {i}")
        f.write("\n".join(lines))
        print(f"data_{datatype}_{N}.in generated.")

if __name__ == '__main__':
    Ns = [1000, 2000, 5000, 10000]
    datatype = ["same", "reverse", "random"]
    for N in Ns:
        for dt in datatype:
            generate_data(N, dt)
