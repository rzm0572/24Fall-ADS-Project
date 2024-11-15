#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <string>
#include "helper.h"
#include "BSeq.h"

// @param n: Size of input array
// @param id: Batch ID
int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s n id\n", argv[0]);
        return 0;
    }

    // Set IO file names
    std::string input_file_no_ext = "data_" + std::string(argv[1]) + "_" + std::string(argv[2]);
    std::string input_file = "data/" + input_file_no_ext + ".in";
    std::string log_file = "log/[" + get_timestamp() + "]" + std::string(tostr(ALGORITHM_NAME)) + "_" + input_file_no_ext + ".log";
    std::string output_file = "out/" + std::string(tostr(ALGORITHM_NAME)) + "_" + input_file_no_ext + ".out";

    FILE* input_fp = fopen(input_file.c_str(), "r");      // Open input file
    FILE* output_fp = fopen(output_file.c_str(), "w");    // Open output file
    freopen(log_file.c_str(), "w", stderr);               // Open log file

    // Read input parameters
    int n, m;
    fscanf(input_fp, "%d%d", &n, &m);

    // Read input array
    int *a = new int[n];
    for (int i = 0; i < n; i++) {
        fscanf(input_fp, "%d", &a[i]);
    }

    START_TIMER;                     // Start of time zone
    int ans = count_BSeq(n, m, a);   // Call algorithm
    
    double total_time = 0.0;
    STOP_TIMER(total_time);          // End of time zone

    // Output result and log
    fprintf(output_fp, "%d\n", ans);
    logger(stderr, "Algorithm: " tostr(ALGORITHM_NAME) "\n");
    logger(stderr, "Answer: %d\n", ans);
    logger(stderr, "Total time: %.6lf s\n", total_time);
    return 0;
}
