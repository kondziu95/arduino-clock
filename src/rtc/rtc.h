#ifndef RTC_H
#define RTC_H

#include "shared.h"
#include <RTClib.h>

void initialize_rtc();
DateTime get_rtc_current_date_time();
void adjust_time(DateTime date_time);

#endif
