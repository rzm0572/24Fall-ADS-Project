# Project 2: Shortest Path Algorithm with Heaps

## File structure

```
project2
├── CMakeLists.txt
├── data
│   ├── processed
│   ├── queries
│   ├── raw
│   └── results
├── include
│   └── MinHeap.h
├── log
├── README.md
├── result
├── run.sh
├── src
│   ├── BinaryHeap.cpp
│   ├── BinomialHeap.cpp
│   ├── difftest.cpp
│   ├── FibonacciHeap.cpp
│   ├── LeftistHeap.cpp
│   └── main.cpp
└── utils
    ├── autobench.py
    └── dataGen.py
    └── dataGenCustom.py
```

## Preparation

1. Run `./init.sh` to prepare the environment.

2. Download the dataset from [Benchmarks for 9th DIMACS Implementation Challenge - Shortest Paths](http://www.dis.uniroma1.it/challenge9/download.shtml) and put them in `data/raw` directory.

## Data Generation

1. For datasets downloaded from above, Run `python3 utils/dataGen.py` to preprocess the data and generate the queries.

2. For custom datasets, Run `python3 utils/dataGenCustom.py` to generate random graphs and queries (**Warning:** You may need to install python packages `numpy` and `cyaron` to run this script)

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

## Performance Test

1. Modify `autobench.py` to set the heap types and datasets you want to test.

2. Run `python3 autobench.py` to test and plot the performance results, which will be saved in `result` directory.

For example, to test the performance of `Binary`, `Fibonacci`, and `Leftist` heaps on the `BAY` and `NY` datasets, you can modify `autobench.py` as follows:

```python
programs = ['./build/Binary', './build/Fibonacci', './build/Leftist']
datasets = ['BAY', 'NY']
```

## Accuracy Test

To test the accuracy of these heaps, you can use the `src/difftest.cpp` file.

1. Modify the `src/difftest.cpp` file to set the heap type:

    ```cpp
    // src/difftest.cpp, line 11
    // Take BinaryHeap as an example
    #define heaptype1 Binary
    #define heaptype2 Test
    ``

2. Build the `difftest` program:

    ```bash
    make difftest -C build
    ```

3. Run the `difftest` program:

    ```bash
    ./build/difftest
    ```
    And you will see the output of the program in the console.
