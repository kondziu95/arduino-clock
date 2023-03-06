#include "cli.h"
#include "utils/serial_utils.h"

#include "commands/time.h"

// List of functions pointers corresponding to each command
int (*commands_func[])(){&cmd_time};
// List of command names
const char *commands_str[] = {"time"};
int num_commands = sizeof(commands_str) / sizeof(char *);

bool is_line_initialized = false;

void initalize_cli()
{
    Serial.println("Welcome to this simple Arduino command line interface (CLI).");
}

void check_cli()
{
    if (!is_line_initialized)
    {
        Serial.print("> ");
        is_line_initialized = true;
    }

    uint32_t line_legth = read_line();
    if (line_legth)
    {
        if (!error_flag)
        {
            parse_line();
        }
        if (!error_flag)
        {
            execute_command();
        }

        memset(line, 0, LINE_BUF_SIZE);
        memset(args, 0, sizeof(args[0][0]) * MAX_NUM_ARGS * ARG_BUF_SIZE);

        error_flag = false;
        is_line_initialized = false;
    }
}

int execute_command()
{
    for (int i = 0; i < num_commands; i++)
    {
        if (strcmp(args[0], commands_str[i]) == 0)
        {
            return (*commands_func[i])();
        }
    }

    Serial.println("Invalid command. Type \"help\" for more.");
    return 0;
}
