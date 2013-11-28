#include <QtTest/QtTest>

#include "../electronicdataview.h"
#include "unittest.h"

class ElectronicViewCsvReaderTest : public UnitTest
{
    Q_OBJECT

public:
    QString getTestName();

public slots:
    bool testRead();

private slots:
    void run();

};
