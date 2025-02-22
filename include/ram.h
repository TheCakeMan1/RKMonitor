#ifndef RAM_H
#define RAM_H

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

struct MemInfo {
    unsigned long long memory_usage;
    unsigned long long MemTotal;
    unsigned long long MemFree;
    unsigned long long MemAvailable;
    unsigned long long Buffers;
    unsigned long long Cached;
};

extern struct MemInfo memInfo;

void update_memory_usage();

#endif