#ifndef TABS_H
#define TABS_H

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include "proc.h"
#include "ram.h"
#include "npu.h"
#include "rga.h"
#include "vpu.h"

#define MAX_NPU_CORES 3
#define MAX_RGA_CORES 3

void show_processor_tab(int max_y, int max_x, int num_cores, int scroll_offset);
void show_rk_tab(int max_y, int max_x, int scroll_offset);
void show_memory_tab(int max_x);

#endif