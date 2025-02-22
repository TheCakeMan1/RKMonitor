#include "ram.h"

struct MemInfo memInfo = {0, 0, 0, 0, 0, 0};

void update_memory_usage() {
    FILE *file = fopen("/proc/meminfo", "r");
    if (!file) {
        perror("Ошибка при открытии /proc/meminfo");
        return;
    }

    char label[64];
    unsigned long long value; // Переменная для чтения значений

    while (fscanf(file, "%63s %llu kB", label, &value) != EOF) {
        if (strcmp(label, "MemTotal:") == 0) {
            memInfo.MemTotal = value;
        } else if (strcmp(label, "MemAvailable:") == 0) {
            memInfo.MemAvailable = value;
        } else if (strcmp(label, "MemFree:") == 0) {
            memInfo.MemFree = value;
        } else if (strcmp(label, "Buffers:") == 0) {
            memInfo.Buffers = value;
        } else if (strcmp(label, "Cached:") == 0) {
            memInfo.Cached = value;
        }
    }
    fclose(file);

    memInfo.memory_usage = (memInfo.MemTotal > 0) ? 
                   (double)(memInfo.MemTotal - memInfo.MemAvailable) / memInfo.MemTotal * 100.0 
                   : 0.0;
}