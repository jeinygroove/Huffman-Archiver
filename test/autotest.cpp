#include "autotest.h"
#include <iostream>

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char *filename, size_t lineNum) {
    if (!expr) {
        std::cout << "test failed: " << func << " in " << filename << ":" << lineNum << std::endl;
        failedNum++;
    }
    totalNum++;
}

void Test::showFinalResult() {
    if (!failedNum) {
        std::cout << "All " << totalNum << " tests passed!" << std::endl;
    } else {
        std::cout << "Failed in " << failedNum << " out of " << totalNum << " tests!" << std::endl;
    }
}
