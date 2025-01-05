#include "ltest.h"

#include <stdio.h>

#define RESET_COLOR   "\x1b[0m"
#define OK_COLOR      "\x1b[32m"
#define FAIL_COLOR    "\x1b[31m"

void run_tests(Test* tests, int count) {
    if (!tests || count <= 0) {
        return;
    }

    int passed_count = 0;

    for (int i = 0; i < count; i++) {
        bool result = tests[i].fn();
        tests[i].passed = result;
        if (result) {
            printf("%s[OK]   %s%s\n", OK_COLOR, tests[i].name, RESET_COLOR);
            passed_count++;
        } else {
            printf("%s[FAIL] %s%s\n", FAIL_COLOR, tests[i].name, RESET_COLOR);
        }
    }

    printf("\n%d/%d tests passed\n", passed_count, count);
}
