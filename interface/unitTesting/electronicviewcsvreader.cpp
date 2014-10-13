#include <QtTest/QtTest>

#include "electronicdataview.h"
#include "electronicviewcsvreader.h"
#include <QDebug>

bool ElectronicViewCsvReaderTest::testRead()
{
    ElectronicDataViewReader reader;


    QString csvTestFile = "unitTesting/testFiles/electronicDataView.csv";

    if(!QFile::exists(csvTestFile)) {
        qDebug() << "Unable to find test file!";
        qDebug() << "Missing: " << QDir::currentPath() + "/" + csvTestFile;
    }

    QMap<QString, ElectronicDataView> view = reader.
            readElectronicDataViewFromCsv(csvTestFile);

    if(view.count() <= 0) {
        return false;
    } else {
        qDebug() << "FILE READ. TEST OK";
    }

    for(QMap<QString, ElectronicDataView>::Iterator it = view.begin(); it != view.end(); it++) {
        // TODO: verificare che i dati siano stati letti correttamente.
    }

    return true;
}

void ElectronicViewCsvReaderTest::run() {
    testRead();
}

QString ElectronicViewCsvReaderTest::getTestName() {
    return "ElectronicViewCsvReader";
}

//#include "electronicviewcsvreader.moc"
