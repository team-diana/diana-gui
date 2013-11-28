#include "unittestmanager.h"

#include "electronicviewcsvreader.h"

/**
  Classe per gestire tutti i test.

 * @brief UnitTestManager::UnitTestManager
 */
UnitTestManager::UnitTestManager()
{
    loadAllTests();
}

UnitTestManager::~UnitTestManager() {
    for(std::vector<UnitTest*>::iterator it = tests.begin(); it != tests.end(); it++) {
        delete *it;
    }
}

bool UnitTestManager::runTests() {
    // TODO: usare valore di ritorno per vedere risultato del test.
    for(std::vector<UnitTest*>::iterator it = tests.begin(); it != tests.end(); it++) {
        UnitTest* test = *it;
        startTest(test);
    }

    return true;
}

bool UnitTestManager::runTest(QString testName) {
    UnitTest* testToRun = NULL;


    for(std::vector<UnitTest*>::iterator it = tests.begin(); it != tests.end(); it++) {
        UnitTest* test = *it;
        if(test->getTestName().toLower() == testName.toLower()) {
            testToRun = test;
        }
    }

    if(!testToRun) {
        qDebug() << "ERROR! Test \"" + testName + "\" was not found" ;
    } else {
        return startTest(testToRun);
    }

    return false;
}

void UnitTestManager::loadAllTests() {
    tests.push_back(new ElectronicViewCsvReaderTest());
}

bool UnitTestManager::startTest(UnitTest *test) {
    qDebug() << "Starting Test: " + test->getTestName();
    bool result = QTest::qExec(test);
    qDebug() << "Ending Test: " + test->getTestName();
    return result;
}
