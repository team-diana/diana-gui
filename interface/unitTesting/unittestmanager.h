#ifndef UNITTESTMANAGER_H
#define UNITTESTMANAGER_H

#include "unittest.h"

#include <vector>

class UnitTestManager
{
public:
    UnitTestManager();
    ~UnitTestManager();

    bool runTests();
    bool runTest(QString testName);

private:
    void loadAllTests();
    bool startTest(UnitTest* test);

private:
    std::vector<UnitTest*> tests;
};

#endif // UNITTESTMANAGER_H
