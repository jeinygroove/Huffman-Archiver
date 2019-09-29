#ifndef HW_3_AUTOTEST_H
#define HW_3_AUTOTEST_H

#include <cstddef>
#include <string>
#include <iostream>

class Test {
protected:
    static int failedNum;
    static int totalNum;

public:
    static void check(bool expr, const char *func, const char *filename, size_t lineNum);

    static void showFinalResult();

    virtual void runAllTests() = 0;
};

#endif //HW_3_AUTOTEST_H