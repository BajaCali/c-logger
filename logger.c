#include "logger.h"

FILE *user_file;

typedef struct logger_conf
{
    char *logger_file;
    short log_level;
    short log_no_std;
    short log_syslog;
    short log_stdout;
};

typedef struct logger_conf logger_conf;

int logger_read_configuration(struct logger_conf *config, const char *file_name)
{

    return 0;
}

int logger_init(struct logger_conf *configuraiton)
{
    user_file = fopen(configuraiton->logger_file, "a");
    #undef LOG_LEVEL
    #define LOG_LEVEL configration->log_level
    #undef _LOG_NO_STD
    #define _LOG_NO_STD = configuraiton->log_no_std;
    #undef _LOG_SYSLOG
    #define _LOG_SYSLOG = configuration->log_syslog;
    #undef _LOG_STDOUT
    #define _LOG_STDOUT = configuration->log_stdout;
    return 0;
}

int logger_close(void)
{
    fclose(user_file);
    return 0;
}

int logger_write_configuration(struct logger_conf *config, const char *file_name)
{

    return 0;
}
