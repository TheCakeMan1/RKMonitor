#include "proc.h"

unsigned long long prev_total[MAX_CORES + 1] = {0};
unsigned long long prev_idle[MAX_CORES + 1] = {0};
double cpu_usage[MAX_CORES] = {0}; // Хранение загрузки CPU

int get_cpu_cores() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

double get_cpu_temperature(int zone) {
    char path[64];
    snprintf(path, sizeof(path), "/sys/class/thermal/thermal_zone%d/temp", zone);

    FILE *file = fopen(path, "r");
    if (!file) return -1;

    int temp_millidegrees;
    if (fscanf(file, "%d", &temp_millidegrees) != 1) {
        fclose(file);
        return -1;
    }
    fclose(file);
    return temp_millidegrees / 1000.0;
}

void update_cpu_usage(int num_cores) {
    FILE *file = fopen("/proc/stat", "r");
    if (!file) {
        perror("Ошибка при открытии /proc/stat");
        return;
    }

    char line[256], label[16];
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    int core = 0;

    while (fgets(line, sizeof(line), file) && core <= num_cores) {
        if (sscanf(line, "%s %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                   label, &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice) >= 5) {

            unsigned long long total = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
            unsigned long long total_diff = total - prev_total[core];
            unsigned long long idle_diff = idle - prev_idle[core];

            cpu_usage[core] = (total_diff > 0) ? (100.0 * (total_diff - idle_diff) / total_diff) : 0.0;

            prev_total[core] = total;
            prev_idle[core] = idle;
        }
        core++;
    }
    fclose(file);
}