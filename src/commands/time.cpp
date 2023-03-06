#include "time.h"
#include "rtc/rtc.h"
#include "utils/array_utils.h"
#include "utils/number_utils.h"
#include "shared.h"

// List of LED sub command names
const char *led_args[] = {"set", "mode", "save"};

void change_mode(const char *mode_arg);
void set_time(const char *time_arg);
bool is_time_valid(uint8_t hours, uint8_t minutes);
void save_time();

int cmd_time()
{
    if (strcmp(args[1], led_args[0]) == 0)
    {
        if (clock_mode == EDIT)
        {
            char *time_arg = args[2];
            set_time(time_arg);
        }
        else
        {
            Serial.println("Cannot set temporary time when edit mode is disabled. Use \"time mode e\".");
        }
    }
    else if (strcmp(args[1], led_args[1]) == 0)
    {
        char *mode = args[2];
        change_mode(mode);
    }
    else if (strcmp(args[1], led_args[2]) == 0)
    {
        if (clock_mode == EDIT)
            save_time();
        else
            Serial.println("Cannot save time when edit mode is disabled. Use \"time mode e\".");
    }
    else
    {
        Serial.println("Invalid command.");
    }

    return 0;
}

void change_mode(const char *mode_arg) // n = normal mode, e = edit mode
{
    switch (mode_arg[0])
    {
    case 'n':
        clock_mode = NORMAL;
        Serial.println("Switched to normal mode.");
        break;
    case 'e':
        clock_mode = EDIT;
        Serial.println("Switched to edit mode.");
        break;
    default:
        Serial.println("This mode is not supported");
    }
}

void set_time(const char *time_arg)
{
    uint8_t time_length = strlen(time_arg);
    char time[time_length];
    memcpy(time, time_arg, time_length);

    if (time_length == 4)
    {
        uint8_t middleIndex = time_length / 2;

        char hours_part[middleIndex + 1];
        char minutes_part[middleIndex + 1];
        splitArray(time, time_length, hours_part, minutes_part, middleIndex);

        uint8_t hours = atol(hours_part);
        uint8_t minutes = atol(minutes_part);

        if (is_time_valid(hours, minutes))
        {
            clock_hours = hours;
            clock_minutes = minutes;
        }
        else
        {
            Serial.println("Command excecution error. Invalid date...");
        }
    }
    else
    {
        Serial.println("Invalid value in 3 argument.");
    }
}

void save_time()
{
    adjust_time(DateTime(1970, 1, 1, clock_hours, clock_minutes, 0));
    Serial.println("Time saved in RTC memory.");
    change_mode("n");
}

bool is_time_valid(uint8_t hours, uint8_t minutes)
{
    bool is_hour_valid = hours >= 0 && hours < 24;
    bool is_minute_valid = minutes >= 0 && minutes < 60;
    return is_hour_valid && is_minute_valid;
}
