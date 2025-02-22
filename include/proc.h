#ifndef PROC_H
#define PROC_H

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define MAX_CORES 128 

extern unsigned long long prev_total[MAX_CORES + 1];
extern unsigned long long prev_idle[MAX_CORES + 1];
extern double cpu_usage[MAX_CORES];

int get_cpu_cores();
double get_cpu_temperature(int zone);
void update_cpu_usage(int num_cores);

#endif