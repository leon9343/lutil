#ifndef LUTIL_LLOG_H
#define LUTIL_LLOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

typedef enum {
  LOG_DEBUG,
  LOG_TRACE,
  LOG_INFO,
  LOG_WARNING,
  LOG_ERROR
} LogLevel;

void _log(LogLevel level, const char* message, ...);

#define LOG_DEBUG(...)   _log(LOG_DEBUG, __VA_ARGS__)
#define LOG_TRACE(...)   _log(LOG_TRACE, __VA_ARGS__)
#define LOG_INFO(...)    _log(LOG_INFO, __VA_ARGS__)
#define LOG_WARNING(...) _log(LOG_WARNING, __VA_ARGS__)
#define LOG_ERROR(...)   _log(LOG_ERROR, __VA_ARGS__)


#ifdef __cplusplus
}
#endif

#endif // !LUTIL_LLOG_H
