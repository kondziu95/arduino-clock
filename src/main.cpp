#include <Arduino.h>
#include "shared.h"
#include "rtc/rtc.h"
#include "display/display.h"
#include "utils/number_utils.h"
#include "cli/cli.h"
#include "clock/modes.h"

uint8_t latch_pin = 8;
uint8_t clock_pin = 12;
uint8_t data_pin = 11;

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 5000;
uint16_t previous_time = 0;
CLOCK_MODE previous_clock_mode = NORMAL;

void setup()
{
  SHIFT_REGISTER_PINOUT shift_register_pinout = {latch_pin, clock_pin, data_pin};
  initialize_display(shift_register_pinout);
  initialize_rtc();

  Serial.begin(9600);
  initalize_cli();

  startMillis = millis();
}

void loop()
{
  currentMillis = millis();

  bool is_clock_enabled = clock_mode == NORMAL;
  if (is_clock_enabled && (currentMillis - startMillis >= period))
  {
    DateTime now = get_rtc_current_date_time();
    clock_hours = now.hour();
    clock_minutes = now.minute();
    startMillis = currentMillis;
  }

  uint16_t display_numbers = concat_time_numbers(clock_hours, clock_minutes);
  if (previous_clock_mode != clock_mode || previous_time != display_numbers)
  {
    boolean show_dot = clock_mode == EDIT;
    show_number(display_numbers, show_dot);

    previous_time = display_numbers;
    previous_clock_mode = clock_mode;
  }

  check_cli();
}
