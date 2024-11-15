# Project 4: Beautiful Subsequence

## File structure

```
project4
├── CMakeLists.txt
├── data
├── include
│   ├── BSeq.h
│   └── helper.h
├── init.sh
├── log
├── out
├── README.md
├── result
├── run.sh
├── src
│   ├── Baseline.cpp
│   ├── BItree.cpp
│   ├── main.cpp
│   └── Merge.cpp
└── utils
    ├── autobench.py
    └── dataGen.py
```

## Preparation & Data generation

1. Run `./init.sh` to prepara the environment.

2. Modify and run `python3 utils/dataGen.py` to generate the input data.

    ```python
    # utils/dataGen.py, line 18-22
    path = './data'  # directory to store the input data
    num_samples = 1  # number of input data sets to generate
    N = 10000
    M = random.randint(1, 1000)
    T = 10000
    ```

## Run the test

You can test one of the algorithms by running the following command:

```bash
./run.sh <algorithm> <input_N> <sample_id>
```

- algorithm: `Baseline`, `BItree`, or `Merge`
- input_N: the size of the input sequence
- sample_id: the id of the input data set to use (from 0 to num_samples-1)

You can also run the performance test by running the following command:

```bash
python3 utils/autobench.py
```

That will automatically generate the input data and run all the algorithms for each input size serveral times and plot the results. The plot will be saved in `result` directory.
