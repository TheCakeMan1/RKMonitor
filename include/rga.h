#ifndef RGA_H
#define RGA_H

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

extern int rga_usage[3];
extern char core0_name[16], core1_name[16], rga2_name[16];

void get_rga_usage();

#endif