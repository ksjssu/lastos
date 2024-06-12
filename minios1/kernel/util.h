#ifndef UTIL_H
#define UTIL_H

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} log_level_t;

void set_log_level(log_level_t level);
void log_message(log_level_t level, const char *format, ...);

#endif // UTIL_H

