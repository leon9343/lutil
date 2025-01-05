#ifndef LUTIL_LRESULT_H
#define LUTIL_LRESULT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef enum {
  RESULT_OK = 0,
  RESULT_ERROR
} ResultStatus;

typedef struct {
  ResultStatus status;
  int error_code;
  char message[128];
} Result;

Result result_ok();
Result result_error(int code, const char* message, ...);

bool result_is_ok(const Result* r);
bool result_is_error(const Result* r);

#define DEFINE_RESULT_TYPE(TYPE, SUFFIX)              \
  typedef struct {                                    \
    ResultStatus status;                              \
    int error_code;                                   \
    char message[128];                                \
    TYPE data;                                        \
  } Result##SUFFIX;                                   \
                                                      \
  static inline Result##SUFFIX result_ok_##SUFFIX(TYPE val) { \
    Result##SUFFIX r;                                         \
    r.status = RESULT_OK;                                     \
    r.error_code = 0;                                         \
    r.message[0] = '\0';                                      \
    r.data = val;                                             \
    return r;                                                 \
  }                                                           \
  \
  static inline Result##SUFFIX result_err_##SUFFIX(int code,           \
                                                   const char* fmt,    \
                                                   ...) {              \
    Result##SUFFIX r;                                                \
    r.status = RESULT_ERROR;                                         \
    r.error_code = code;                                             \
    r.message[0] = '\0';                                             \
    if (fmt) {                                                       \
        va_list args;                                                \
        va_start(args, fmt);                                         \
        vsnprintf(r.message, sizeof(r.message), fmt, args);          \
        va_end(args);                                                \
    }                                                                \
    return r;                                                        \
  }                                                                  \
  \
  static inline bool result_##SUFFIX##_is_ok(const Result##SUFFIX* r) { \
    return (r->status == RESULT_OK);                                  \
  }                                                                   \
  \
  static inline bool result_##SUFFIX##_is_err(const Result##SUFFIX* r) { \
    return (r->status == RESULT_ERROR);                                \
  }                                                                    \
  \
  static inline TYPE result_##SUFFIX##_get_data(const Result##SUFFIX* r) { \
    return r->data;                                                      \
  }                                                                      \


#ifdef __cplusplus
}
#endif

#endif // !LUTIL_LRESULT_H
