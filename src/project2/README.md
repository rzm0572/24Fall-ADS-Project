# Project 2: Shortest Path Algorithm with Heaps

## File structure

```
├── CMakeLists.txt
├── data
│   ├── processed
│   ├── queries
│   ├── raw
│   └── results
├── include
│   └── MinHeap.h
├── README.md
├── run.sh
├── src
│   ├── BinaryHeap.cpp
│   ├── BinomialHeap.cpp
│   ├── FibonacciHeap.cpp
│   ├── LeftistHeap.cpp
│   └── main.cpp
└── utils
    ├── autobench.py
    └── dataGen.py
```

## Preparation

1. Download the dataset from [Benchmarks for 9th DIMACS Implementation Challenge - Shortest Paths](http://www.dis.uniroma1.it/challenge9/download.shtml) and put them in `data/raw` directory.

2. Run `python3 utils/dataGen.py` to preprocess the data and generate the queries.

## Build and Run

Before the build, make sure you have installed `cmake` and `make`. Then, run the following commands:

```
./run.sh <HEAPTYPE> <DATASET> [NUM_EPOCHS]
```

- `<HEAPTYPE>`: `Binary`, `Binomial`, `Fibonacci`, or `Leftist`

- `<DATASET>`: `BAY`, `NY`, etc. **(You need to download the dataset first)**

- `[NUM_EPOCHS]`: Optional. The number of epochs to run the algorithm. Default is 3.

If you want to build and run the code manually, you can follow these steps:

1. Generate the build files: `cmake -B build`

2. Build the code:

    ```
    cd build
    make <HEAPTYPE>
    ```

3. Run the code in the `project2` directory:

    ```
    ./build/<HEAPTYPE> <DATASET> <NUM_EPOCHS>
    ```

For example, to build and run the `Binary` heap on the `BAY` dataset with 5 epochs, you can run:

```
cmake -B build
cd build
make Binary
cd ..
./build/Binary BAY 5
```

The output will be saved in `data/results/<HEAPTYPE>_<DATASET>_<EPOCH>.res`.
