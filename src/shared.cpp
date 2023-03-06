#include "shared.h"

bool error_flag = false;
char args[MAX_NUM_ARGS][ARG_BUF_SIZE] = {};
char line[LINE_BUF_SIZE] = {};
CLOCK_MODE clock_mode = NORMAL;
uint8_t clock_hours = 0;
uint8_t clock_minutes = 0;
