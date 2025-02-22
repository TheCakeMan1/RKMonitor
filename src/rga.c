#include "rga.h"

int rga_usage[3] = {0};
char core0_name[16], core1_name[16], rga2_name[16];

void get_rga_usage(){
    FILE *file = fopen("/sys/kernel/debug/rkrga/load", "r");
    if (!file) {
        mvprintw(4, 2, "Ошибка чтения RGA!");
        return;
    }

    char buffer[256];
    int core0 = 0, core1 = 0, rga2 = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "scheduler[0]: %s", core0_name) == 1) {
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, " load = %d%%", &rga_usage[0]);
        }
        if (sscanf(buffer, "scheduler[1]: %s", core1_name) == 1) {
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, " load = %d%%", &rga_usage[1]);
        }
        if (sscanf(buffer, "scheduler[2]: %s", rga2_name) == 1) {
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, " load = %d%%", &rga_usage[2]);
        }
    }
    fclose(file);
}