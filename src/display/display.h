#ifndef DISPLAY_H
#define DISPLAY_H

#include "shared.h"

struct SHIFT_REGISTER_PINOUT
{
    uint8_t latch;
    uint8_t clock;
    uint8_t data;
};

void initialize_display(SHIFT_REGISTER_PINOUT shift_register_pinout);

void show_number(uint16_t number, bool show_dot);

#endif
