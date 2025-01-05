#include "llog.h"

#include <stdio.h>
#include <time.h>

#define RESET_COLOR    "\x1b[0m"
#define DEBUG_COLOR    "\x1b[36m"  /* Cyan */
#define TRACE_COLOR    "\x1b[34m"  /* Blue */
#define INFO_COLOR     "\x1b[32m"  /* Green */
#define WARNING_COLOR  "\x1b[33m"  /* Yellow */
#define ERROR_COLOR    "\x1b[31m"  /* Red */

static void get_time_str(char* buffer, size_t size) {
  time_t rawtime;
  struct tm* timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer, size, "%H:%M", timeinfo);
}

static const char* level_to_string(LogLevel level) {
  switch (level) {
    case LOG_DEBUG:   return "DEBUG";
    case LOG_TRACE:   return "TRACE";
    case LOG_INFO:    return "INFO";
    case LOG_WARNING: return "WARNING";
    case LOG_ERROR:   return "ERROR";
    default: return "???";
  }
}

static const char* level_color(LogLevel level) {
  switch (level) {
    case LOG_DEBUG:   return DEBUG_COLOR;
    case LOG_TRACE:   return TRACE_COLOR;
    case LOG_INFO:    return INFO_COLOR;
    case LOG_WARNING: return WARNING_COLOR;
    case LOG_ERROR:   return ERROR_COLOR;
    default: return RESET_COLOR;
  }
}

void _log(LogLevel level, const char *message, ...) {
  char time_buffer[6];
  get_time_str(time_buffer, sizeof(time_buffer));

  char formatted_msg[1024];
  va_list args;
  va_start(args, message);
  vsnprintf(formatted_msg, sizeof(formatted_msg), message, args);
  va_end(args);

  fprintf(stderr,
          "%s[%s][%s]: %s%s\n",
          level_color(level),
          time_buffer,
          level_to_string(level),
          formatted_msg,
          RESET_COLOR
  );
}
