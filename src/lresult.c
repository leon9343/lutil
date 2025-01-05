#include "lresult.h"
#include <stdarg.h>
#include <stdio.h>

Result result_ok() {
  Result r;
  r.status = RESULT_OK;
  r.error_code = 0;
  r.message[0] = '\0';
  return r;
}

Result result_error(int code, const char *message, ...) {
  Result r;
  r.status = RESULT_ERROR;
  r.error_code = code;

  if (message) {
    va_list args;
    va_start(args, message);
    vsnprintf(r.message, sizeof(r.message), message, args);
    va_end(args);
  } else {
    r.message[0] = '\0';
  }

  return r;
}

bool result_is_ok(const Result* r) {
  return (r->status == RESULT_OK);
}

bool result_is_error(const Result* r) {
  return (r->status == RESULT_ERROR);
}

