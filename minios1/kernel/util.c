#include "util.h"
#include <stdio.h>
#include <stdarg.h>

static log_level_t current_log_level = LOG_INFO;

void set_log_level(log_level_t level) {
    current_log_level = level;
}

void log_message(log_level_t level, const char *format, ...) {
    if (level >= current_log_level) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
        printf("\n");
    }
}

