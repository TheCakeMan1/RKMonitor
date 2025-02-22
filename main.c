#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include "proc.h"
#include "ram.h"
#include "tabs.h"
#include "vpu.h"

// #define MAX_CORES 128  // Максимальное количество ядер
// #define TAB_COUNT 2    // Количество вкладок

int current_tab = 0; 
// double npu_usage[3] = {0}; // Хранение загрузки CPU
unsigned long last_update_time = 0; // Время последнего обновления
const unsigned long update_interval = 500; // Интервал обновления в миллисекундах

unsigned long get_current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void update_npu_usage(int num_cores) {
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

// int main() {
//     get_npu_cors();
//     printf("VPU Dec0 Usage: Previous=%d, Current=%d\n", npu_usage[1], npu_usage[0]);

//     get_npu_cors();
//     printf("VPU Dec0 Usage: Previous=%d, Current=%d\n", npu_usage[1], npu_usage[0]);
//     sleep(1);
//     get_npu_cors();

//     printf("VPU Dec0 Usage: Previous=%d, Current=%d\n", npu_usage[1], npu_usage[0]);
    
//     return 0;
// }


int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(500);  // Быстрое обновление интерфейса

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK); // CPU бар
        init_pair(2, COLOR_BLUE, COLOR_BLACK);  // RAM бар
        init_pair(3, COLOR_CYAN, COLOR_BLACK);  // Заголовок "Processor"
        init_pair(4, COLOR_MAGENTA, COLOR_BLACK); // Заголовок "Memory"
        init_pair(5, COLOR_RED, COLOR_BLACK); // Заголовок "Memory"
    }

    int max_y, max_x;
    int num_cores = get_cpu_cores();
    int scroll_offset = 0;

    while (1) {
        getmaxyx(stdscr, max_y, max_x); // Теперь каждый цикл обновляет размеры
        int max_displayed = (max_y - 7) / 2;  // Сколько строк вмещается на экран
        int max_scroll = (num_cores > max_displayed) ? num_cores - max_displayed : 0;

        unsigned long current_time = get_current_time_ms();
        if (current_time - last_update_time >= update_interval) {
            update_cpu_usage(num_cores);
            update_memory_usage();
            get_npu_cors();
            get_rga_usage();
            get_vpu_usage_dec0();
            get_vpu_usage_dec1();
            get_vpu_usage_enc1();
            get_vpu_usage_enc0();
            last_update_time = current_time;
        }

        clear();
        box(stdscr, 0, 0);
        mvprintw(0, (max_x - 20) / 2, "[ Usage Monitor ]");

        // Отрисовка вкладок
        mvprintw(0, 2, " [ Processor ] ");
        mvprintw(0, 20, " [ Memory ] ");
        mvprintw(0, 40, " [ RockChip ] ");
        attron(A_BOLD);
        if (current_tab == 0) mvprintw(0, 3, "[ Processor ]");
        else if (current_tab == 1) mvprintw(0, 21, "[ Memory ]");
        else mvprintw(0, 41, "[ RockChip ]");
        attroff(A_BOLD);

        if (current_tab == 0) {
            show_processor_tab(max_y, max_x, num_cores, scroll_offset);
        } else if (current_tab == 1) {
            show_memory_tab(max_x);
        } else {
            show_rk_tab(max_y, max_x, scroll_offset);
        }

        refresh();

        int ch = getch();
        if (ch == KEY_UP && scroll_offset > 0 && current_tab == 0) scroll_offset--;
        if (ch == KEY_DOWN && scroll_offset < max_scroll && current_tab == 0) scroll_offset++;
        if (ch == KEY_LEFT) {
            if(current_tab != 0) {
                current_tab--;
            }   
        }
        if (ch == KEY_RIGHT) {
            if(current_tab != 2) {
                current_tab++;
            }   
        }
        if (ch == 'q') break;
    }

    endwin();
    return 0;
}
