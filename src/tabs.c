#include "tabs.h"

void draw_bar(int y, int width, double usage, int color_pair, const char* line) {
    int filled = (int)(usage / 100.0 * width);
    int line_length = strlen(line) + 2;

    mvprintw(y, 1, "%s ", line);
    mvprintw(y, line_length, "[");
    attron(COLOR_PAIR(color_pair));

    for (int i = 0; i < width; i++) {
        if (i < filled) {
            addch(' ' | A_REVERSE); 
        } else {
            attroff(COLOR_PAIR(color_pair));
            addch('-'); 
            attron(COLOR_PAIR(color_pair));
        }
    }
    
    attroff(COLOR_PAIR(color_pair));
    printw("] %.1f%%", usage);
}


void show_processor_tab(int max_y, int max_x, int num_cores, int scroll_offset) {
    mvprintw(1, (max_x - 16) / 2, "[ Processor ]");

    attron(A_BOLD | COLOR_PAIR(3));
    mvprintw(2, 2, "Core  | Temp | Pow");
    attroff(A_BOLD | COLOR_PAIR(3));

    char row[64];
    int total_lines = num_cores * 2;
    int max_displayed = max_y - 5; 

    for (int i = 0; i < max_displayed / 2 && (i + scroll_offset) < num_cores; i++) {
        int index = i + scroll_offset;

        snprintf(row, sizeof(row), "CPU %-2d | %-6.1f°C | %-6.1f%%", 
                 index, get_cpu_temperature(3), cpu_usage[index]);
        mvprintw(i * 2 + 3, 2, "%s", row);

        char label[16];
        snprintf(label, sizeof(label), "CPU %-2d", index);
        draw_bar(i * 2 + 4, max_x - 18, cpu_usage[index], 1, label);
    }

    if (scroll_offset > 0) mvprintw(3, max_x - 5, "UP");
    if (scroll_offset + (max_displayed / 2) < num_cores) mvprintw(max_y - 2, max_x - 5, "Down");
}

void show_rk_tab(int max_y, int max_x, int scroll_offset) {
    mvprintw(2, (max_x - 16) / 2, "[ NPU ]");

    if (scroll_offset + 0 < MAX_NPU_CORES) draw_bar(3, max_x - 16, npu_usage[0], 1, "Core0");
    if (scroll_offset + 1 < MAX_NPU_CORES) draw_bar(4, max_x - 16, npu_usage[1], 1, "Core1");
    if (scroll_offset + 2 < MAX_NPU_CORES) draw_bar(5, max_x - 16, npu_usage[2], 1, "Core2");

    mvprintw(6, (max_x - 16) / 2, "[ RGA ]");

    if (scroll_offset + 0 < MAX_RGA_CORES) draw_bar(7, max_x - 11 - strlen(core0_name), rga_usage[0], 1, core0_name);
    if (scroll_offset + 1 < MAX_RGA_CORES) draw_bar(8, max_x - 11 - strlen(core1_name), rga_usage[1], 1, core1_name);
    if (scroll_offset + 2 < MAX_RGA_CORES) draw_bar(9, max_x - 11 - strlen(rga2_name), rga_usage[2], 1, rga2_name);
    
    mvprintw(10, (max_x - 16) / 2, "[ VPU ]");
    mvprintw(11, 2, "Dec0");
    mvprintw(12, 2, "Dec1");
    mvprintw(13, 2, "Enc0");
    mvprintw(14, 2, "Enc1");

    if (strcmp(vpu_usage_dec_0[0], vpu_usage_dec_0[1]) == 0){
        attron(COLOR_PAIR(5)); // Красный
        mvprintw(11, 8, "busy");
        attroff(COLOR_PAIR(5));
    } else {
        attron(COLOR_PAIR(1)); // Зелёный
        mvprintw(11, 8, "load");
        attroff(COLOR_PAIR(1));
    }

    if (strcmp(vpu_usage_dec_1[0], vpu_usage_dec_1[1]) == 0){
        attron(COLOR_PAIR(5)); // Красный
        mvprintw(12, 8, "busy");
        attroff(COLOR_PAIR(5));
    } else {
        attron(COLOR_PAIR(1)); // Зелёный
        mvprintw(12, 8, "load");
        attroff(COLOR_PAIR(1));
    }

    if (strcmp(vpu_usage_enc_0[0], vpu_usage_enc_0[1]) == 0){
        attron(COLOR_PAIR(5)); // Красный
        mvprintw(13, 8, "busy");
        attroff(COLOR_PAIR(5));
    } else {
        attron(COLOR_PAIR(1)); // Зелёный
        mvprintw(13, 8, "load");
        attroff(COLOR_PAIR(1));
    }

    if (strcmp(vpu_usage_enc_1[0], vpu_usage_enc_1[1]) == 0){
        attron(COLOR_PAIR(5)); // Красный
        mvprintw(14, 8, "busy");
        attroff(COLOR_PAIR(5));
    } else {
        attron(COLOR_PAIR(1)); // Зелёный
        mvprintw(14, 8, "load");
        attroff(COLOR_PAIR(1));
    }
    
    int max_displayed = max_y - 10; // Количество доступных строк для прокрутки

    if (scroll_offset > 0) {
        mvprintw(max_y - 3, max_x - 5, "UP");
    }
    if (scroll_offset + max_displayed < 6) {  // 6 — кол-во строк, которые можно прокручивать
        mvprintw(max_y - 2, max_x - 5, "DOWN");
    }
    refresh();
}

void show_memory_tab(int max_x) {
    mvprintw(1, (max_x - 14) / 2, "[ Memory ]");
    double MemTotal = memInfo.MemTotal / 1024 / 1024;
    double MemFree = memInfo.MemFree / 1024 / 1024;
    double Buffers = memInfo.Buffers / 1024 / 1024;
    double Cached = memInfo.Cached / 1024 / 1024;
    char label[16];
    snprintf(label, sizeof(label), "RAM %-.1fgb", MemTotal - MemFree);
    draw_bar(3, max_x - 20, memInfo.memory_usage, 2, label);
    char row[64];
    mvprintw(4, 2, "Total   |   Free   |   Buffer   |   Cached", row);
    snprintf(row, sizeof(row), " %-6.1fgb | %-6.1fgb | %-6.1fgb | %-6.1fgb", 
        MemTotal, MemFree, Buffers, Cached);
        mvprintw(5, 2, "%s", row);
}