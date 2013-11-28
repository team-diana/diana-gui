#ifndef UNITTEST_H
#define UNITTEST_H

#include <QObject>

class UnitTest : public QObject
{
    Q_OBJECT

public:
    UnitTest();

    // Metodi virtuali astratto.
    // Tutte le classi che ineritano da UnitTest devono
    // implementarlo.
    virtual QString getTestName() = 0;

};

#endif // UNITTEST_H
