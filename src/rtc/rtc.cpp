#include "rtc.h"

RTC_DS1307 rtc;

void initialize_rtc()
{
  while (!rtc.begin())
    delay(100);
}

DateTime get_rtc_current_date_time()
{
    return rtc.now();
}

void adjust_time(DateTime date_time) 
{
    rtc.adjust(date_time);
}