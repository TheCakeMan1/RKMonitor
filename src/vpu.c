#include "vpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

// Хранение двух последних значений
char vpu_usage_dec_0[2][32] = { "", "" };
char vpu_usage_dec_1[2][32] = { "", "" };
char vpu_usage_enc_0[2][32] = { "", "" };
char vpu_usage_enc_1[2][32] = { "", "" };

void get_vpu_usage_dec0() {
    FILE *file = fopen("/sys/kernel/debug/pm_genpd/rkvdec0/idle_states", "r");
    if (!file) {
        perror("Ошибка открытия rkvdec0");
        return;
    }

    char line[MAX_LINE];

    fgets(line, MAX_LINE, file); // Пропускаем заголовок

    if (fgets(line, MAX_LINE, file)) {
        strcpy(vpu_usage_dec_0[1], vpu_usage_dec_0[0]);
        sscanf(line, "%*s %31s %*s %*s", vpu_usage_dec_0[0]);
        vpu_usage_dec_0[0][31] = '\0';
    }

    fclose(file);
}

void get_vpu_usage_dec1() {
    FILE *file = fopen("/sys/kernel/debug/pm_genpd/rkvdec1/idle_states", "r");
    if (!file) {
        perror("Ошибка открытия rkvdec1");
        return;
    }

    char line[MAX_LINE];

    fgets(line, MAX_LINE, file); // Пропускаем заголовок

    if (fgets(line, MAX_LINE, file)) {
        strcpy(vpu_usage_dec_1[1], vpu_usage_dec_1[0]);
        sscanf(line, "%*s %31s %*s %*s", vpu_usage_dec_1[0]);
        vpu_usage_dec_1[0][31] = '\0';
    }

    fclose(file);
}

void get_vpu_usage_enc0() {
    FILE *file = fopen("/sys/kernel/debug/pm_genpd/venc0/idle_states", "r");
    if (!file) {
        perror("Ошибка открытия venc0");
        return;
    }

    char line[MAX_LINE];

    fgets(line, MAX_LINE, file); // Пропускаем заголовок

    if (fgets(line, MAX_LINE, file)) {
        strcpy(vpu_usage_enc_0[1], vpu_usage_enc_0[0]);
        sscanf(line, "%*s %31s %*s %*s", vpu_usage_enc_0[0]);
        vpu_usage_enc_0[0][31] = '\0';
    }

    fclose(file);
}

void get_vpu_usage_enc1() {
    FILE *file = fopen("/sys/kernel/debug/pm_genpd/venc1/idle_states", "r");
    if (!file) {
        perror("Ошибка открытия venc1");
        return;
    }

    char line[MAX_LINE];

    fgets(line, MAX_LINE, file); // Пропускаем заголовок

    if (fgets(line, MAX_LINE, file)) {
        strcpy(vpu_usage_enc_1[1], vpu_usage_enc_1[0]);
        sscanf(line, "%*s %31s %*s %*s", vpu_usage_enc_1[0]);
        vpu_usage_enc_1[0][31] = '\0';
    }

    fclose(file);
}
