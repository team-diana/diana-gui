#ifndef QCONTROLLER_H
#define QCONTROLLER_H

#include <QTextEdit>
#include <QTimer>
#include <QObject>

#include "comunication.h"

class QController : public QObject
{
    Q_OBJECT
public:
    QController(QObject* parent = NULL);
    bool Check();
    bool Init();
    bool Conn();
    int disc();

public:
    QTextEdit *log;
    QTimer *refresh;
    QTimer *delay;
    bool wait;
    Comunication *comm;
    int speed,time;

public slots:
    int getData();
    void waiting();

};

#endif // QCONTROLLER_H

