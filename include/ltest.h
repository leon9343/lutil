#ifndef LUTIL_LTEST_H
#define LUTIL_LTEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef bool (*TestFn)(void);

typedef struct {
    const char* name;
    TestFn fn;
    bool passed; 
} Test;

void run_tests(Test* tests, int count);

#ifdef __cplusplus
}
#endif

#endif // !LUTIL_LTEST_H
