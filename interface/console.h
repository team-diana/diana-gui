#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QEvent>
#include <QtEvents>
#include <QTextEdit>
#include <comunication.h>
#include <commands.h>

class Console : public QObject
{
    Q_OBJECT

public:
    Console(QObject* parent = NULL);
    int isLocal(QString cmd);
    virtual bool eventFilter(QObject *obj, QEvent *event);

public:
    Comunication *com;
    Commands *cmds;
    QTextEdit *wnd;

};

#endif // CONSOLE_H
