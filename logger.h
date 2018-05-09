#ifndef LOGGER_H
#define LOGGER_H

#define _GNU_SOURCE

#include <stdio.h>
#include <syslog.h>

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_WARNING
#endif

#ifndef _DISABLE_LOGGER
#define _DISABLE_LOGGER 0
#endif

#define TO_S(M) #M
#define STR(M) TO_S(M)

#ifdef _LOG_SYSLOG
#undef _LOG_SYSLOG
#define _LOG_SYSLOG 1
#else
#define _LOG_SYSLOG 0
#endif // _LOG_SYSLOG

#ifdef _LOG_STDOUT
#undef _LOG_STDOUT
#define _LOG_STDOUT 1
#else
#define _LOG_STDOUT 0
#endif // _LOG_STDOUT

#ifdef _LOG_NO_STD
#undef _LOG_NO_STD
#define _LOG_NO_STD 1
#else
#define _LOG_NO_STD 0
#endif // _LOG_NO_STD

#ifdef _LOG_RUNTIME_ENVIRONMENT
#undef _LOG_RUNTIME_ENVIRONMENT
#define _LOG_RUNTIME_ENVIRONMENT 1
extern FILE* user_file;
#define LOG_UMSG(LEVEL, f_str, ...) fprintf(user_file, "[" STR(LEVEL) "]["  __FILE__  ":" STR(__LINE__)
int logger_read_configuration(struct logger_conf *config, const char *file_name);
int logger_init(struct logger_conf *configuraiton);
int logger_close(void);
int logger_write_configuration(struct logger_conf *config, const char *file_name);
#else
#define LOG_UMSG(LEVEL, f_str, ...)
#define _LOG_RUNTIME_ENVIRONMENT 0
#endif // _LOG_RUNTIME_ENVIRONMENT

#define LOG_MSG(LEVEL, f_str, ...)                                                   \
    do { \
        if (!_LOG_NO_STD) {\
            if (_LOG_STDOUT)                                                      \
                fprintf(stdout, "[" STR(LEVEL) "]["  __FILE__  ":" STR(__LINE__) "] " f_str, ##__VA_ARGS__); \
            else \
                fprintf(stderr, "[" STR(LEVEL) "]["  __FILE__  ":" STR(__LINE__) "] " f_str, ##__VA_ARGS__); \
        } \
        if (_LOG_SYSLOG) \
            syslog(3, "[" STR(LEVEL) "]["  __FILE__  ":" STR(__LINE__) "] " f_str, ##__VA_ARGS__); \
        LOG_UMSG(LEVEL, f_str, ...) \
    } while(0)


#if LOG_LEVEL >= LOG_EMERG && !_DISABLE_LOGGER
#define LOGF_EMERG(f_str, ...) LOG_MSG("emerg", f_str, ##__VA_ARGS__)
#else
#define LOGF_EMERG(f_str, ...)
#endif

#if LOG_LEVEL >= LOG_ALERT && !_DISABLE_LOGGER
#define LOGF_ALERT(f_str, ...) LOG_MSG("alert", f_str, ##__VA_ARGS__)
#else
#define LOGF_ALERT(f_str, ...)
#endif

#if LOG_LEVEL >= LOG_CRIT && !_DISABLE_LOGGER
#define LOGF_CRIT(f_str, ...) LOG_MSG("crit", f_str, ##__VA_ARGS__)
#else
#define LOGF_CRIT(f_str, ...)
#endif

#if LOG_LEVEL >= LOG_ERR && !_DISABLE_LOGGER
#define LOGF_ERR(f_str, ...) LOG_MSG("err", f_str, ##__VA_ARGS__)
#else
#define LOGF_ERR(f_str, ...)
#endif

#if LOG_LEVEL >= LOG_WARNING && !_DISABLE_LOGGER
#define LOGF_WARINING(f_str, ...) LOG_MSG("warning", f_str, ##__VA_ARGS__)
#else
#define LOGF_WARINING(f_str, ...)
#endif

#if LOG_LEVEL >= LOG_NOTICE && !_DISABLE_LOGGER
#define LOGF_NOTICE(f_str, ...) LOG_MSG("notice", f_str, ##__VA_ARGS__)
#else
#define LOGF_NOTICE(f_str, ...)
#endif

#if LOG_LEVEL >= LOG_INFO && !_DISABLE_LOGGER
#define LOGF_INFO(f_str, ...) LOG_MSG("info", f_str, ##__VA_ARGS__)
#else
#define LOGF_INFO(f_str, ...)
#endif



#endif // LOGGER_H
