/*
AUTHOR: Giuseppe Federico Gullo
DATE: 08/02/2012
DESCRIPTION: Ciclo Principale del software, viene eseguito all'avvio e richiama la classe Command_interface
*/

#include <QApplication>
#include "command_interface.h"
#include <QTimer>
#include "unitTesting/electronicviewcsvreader.h"
#include "unitTesting/unittestmanager.h"
#include <strings.h>

bool runTests();

int main(int argc, char *argv[])
{
    /////////////////////////
    // TODO: Questo sarebbe meglio spostarlo. I test dovrebbero partire per conto proprio.
    bool runTest = false;
    QString testToRunName;
    if(argc > 1 && (strcmp(argv[1], "-t") || strcmp(argv[1], "--tests"))) {
        runTest = true;
        if(argc == 3) {
            testToRunName = QString(argv[2]);
        }
    }
//    /////////////////////////

    if(runTest) {
        UnitTestManager unitTestManager;
        if(testToRunName.isEmpty()) {
            return unitTestManager.runTests();
        } else {
            return unitTestManager.runTest(testToRunName);
        }
    } else {
        QApplication a(argc, argv);
        Command_interface cmd_int;    //Crea un'istanza di Command_interface chiamata cmd_int;
        cmd_int.connectAction();
        cmd_int.setVisible(true);
    //    cmd_int.showFullScreen();
        return a.exec();
    }
    return 0;
}


