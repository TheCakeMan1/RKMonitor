#ifndef VPU_H
#define VPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

extern char vpu_usage_dec_0[2][32];
extern char vpu_usage_dec_1[2][32];
extern char vpu_usage_enc_0[2][32];
extern char vpu_usage_enc_1[2][32];

void get_vpu_usage_dec1();
void get_vpu_usage_dec0();

void get_vpu_usage_enc1();
void get_vpu_usage_enc0();

#endif