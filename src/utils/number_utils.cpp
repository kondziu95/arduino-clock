#include "number_utils.h"

uint16_t concat_time_numbers(uint8_t first, uint8_t second)
{
  char buf[5];
  snprintf(buf, sizeof(buf), "%d%02d", first, second);
  return atol(buf);
}
