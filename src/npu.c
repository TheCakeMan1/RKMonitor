#include "npu.h"

int npu_usage[3] = {0, 0, 0}; // Инициализация массива

void get_npu_cors() {
    FILE *file = fopen("/sys/kernel/debug/rknpu/load", "r");
    if (!file) {
        perror("Ошибка открытия файла rknpu/load");
        return;
    }

    char buffer[128];

    if (!fgets(buffer, sizeof(buffer), file)) { 
        perror("Ошибка чтения файла");
        fclose(file);
        return;
    }

    fclose(file); 
    if (sscanf(buffer, "NPU load:  Core0:  %d%%, Core1:  %d%%, Core2:  %d%%,", 
               &npu_usage[0], &npu_usage[1], &npu_usage[2]) == 3) {
    }
}