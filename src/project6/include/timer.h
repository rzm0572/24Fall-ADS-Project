#ifndef TIMER_H
#define TIMER_H

#include <cstdlib>
#include <ctime>
#include <sys/time.h>

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

#endif