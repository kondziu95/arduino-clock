#ifndef SHARED_H
#define SHARED_H

#include <Arduino.h>
#include "clock/modes.h"

// Maximum input string length
#define LINE_BUF_SIZE 64

// Maximum argument string length
#define ARG_BUF_SIZE 16

// Maximum number of arguments
#define MAX_NUM_ARGS 4

extern bool error_flag;
extern char args[MAX_NUM_ARGS][ARG_BUF_SIZE];
extern char line[LINE_BUF_SIZE];
extern CLOCK_MODE clock_mode;
extern uint8_t clock_hours;
extern uint8_t clock_minutes;

#endif
