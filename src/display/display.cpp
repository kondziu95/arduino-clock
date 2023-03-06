#include "display.h"

SHIFT_REGISTER_PINOUT shift_register_pinout;
const uint8_t dot_mask = 0b01111111;
const uint8_t numbers[10] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000  // 9
};

uint8_t mask_with_display_dot(uint8_t number);

void initialize_display(SHIFT_REGISTER_PINOUT pinout)
{
    pinMode(pinout.latch, OUTPUT);
    pinMode(pinout.clock, OUTPUT);
    pinMode(pinout.data, OUTPUT);
    shift_register_pinout = pinout;
    show_number(1234, false);
}

void show_number(uint16_t number, bool show_dot)
{
    uint32_t temp_number = number;
    if (temp_number > 9999)
        temp_number = 9999;

    digitalWrite(shift_register_pinout.latch, LOW);

    uint16_t divider = 1000;
    while (divider >= 1)
    {
        uint8_t part = floor(temp_number / divider);
        temp_number = temp_number - (part * divider);
        uint8_t number_to_show = numbers[part];
        if (show_dot)
            number_to_show = mask_with_display_dot(number_to_show);
        shiftOut(shift_register_pinout.data, shift_register_pinout.clock, MSBFIRST, number_to_show);
        divider = floor(divider * 0.1);
    }
    digitalWrite(shift_register_pinout.latch, HIGH);
}

uint8_t mask_with_display_dot(uint8_t number)
{
    return ~(~number | ~dot_mask);
}
