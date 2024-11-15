#ifndef MARCOS_H
#define MARCOS_H

#include <cstdio>
#include <sys/time.h>
#include <string>

// Timing marcos
#define START_TIMER       \
    struct timeval begin; \
    gettimeofday(&begin, (struct timezone*)0);

#define STOP_TIMER(t)                        \
    struct timeval end;                      \
    gettimeofday(&end, (struct timezone*)0); \
    t += (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_usec - begin.tv_usec) * 1.e-6;

#define PRINT_TIMER(msg, ...)                                                                           \
    {                                                                                                   \
        struct timeval end;                                                                             \
        gettimeofday(&end, (struct timezone*)0);                                                        \
        double t = (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_usec - begin.tv_usec) * 1.e-6; \
        printf("%.6fs " msg, t, ##__VA_ARGS__);                                                         \
    }

// Logging marcos
#define logger(file, msg, ...)             \
    {                                      \
        printf(msg, ##__VA_ARGS__);        \
        fprintf(file, msg, ##__VA_ARGS__); \
        fflush(file);                      \
    }

// Transform x to string
#define real_tostr(x) #x
#define tostr(x) real_tostr(x)

// Concatenate two marco
#define real_cat(a, b) a##b
#define cat(a, b) real_cat(a, b)

// Add two numbers with modulo
#define ADD_MODULE(a, b, mod) a = ((a) + (b) + (mod)) % (mod)

// Get timestamp
std::string get_timestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return std::to_string(1900 + ltm->tm_year) + "-" + std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(ltm->tm_mday) + " " + std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec);
}

#endif