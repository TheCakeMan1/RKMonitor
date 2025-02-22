#include <stdio.h>
#include <stdlib.h>
#include <rockchip/mpp_task.h>

int main() {
    MppCtx ctx;
    MppApi *api = NULL;
    int task_count = 0;

    if (mpp_create(&ctx, &api) != MPP_OK) {
        printf("Ошибка: не удалось создать MPP-контекст\n");
        return -1;
    }

    if (api->control(ctx, MPP_CMD_QUERY_STATUS, &task_count) == MPP_OK) {
        printf("Текущие задачи в VPU: %d\n", task_count);
    } else {
        printf("Ошибка: не удалось получить статус VPU\n");
    }

    mpp_destroy(ctx);
    return 0;
}
