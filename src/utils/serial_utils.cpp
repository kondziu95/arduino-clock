
#include "serial_utils.h"

uint32_t read_line()
{
    String line_string = {};

    if (Serial.available())
    {
        line_string = Serial.readStringUntil('\n');
        if (line_string.length() < LINE_BUF_SIZE)
        {
            line_string.toCharArray(line, LINE_BUF_SIZE);
            Serial.println(line_string);
        }
        else
        {
            Serial.println("Input string too long.");
            error_flag = true;
        }
    }

    return line_string.length();
}

void parse_line()
{
    char *argument;
    int counter = 0;

    argument = strtok(line, " ");

    while ((argument != NULL))
    {
        if (counter < MAX_NUM_ARGS)
        {
            if (strlen(argument) < ARG_BUF_SIZE)
            {
                strcpy(args[counter], argument);
                argument = strtok(NULL, " ");
                counter++;
            }
            else
            {
                Serial.println("Input string too long.");
                error_flag = true;
                break;
            }
        }
        else
        {
            break;
        }
    }
}