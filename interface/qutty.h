#ifndef QUTTY_H
#define QUTTY_H

#include "GuiTerminalWindow.h"

#include <QObject>
#include <QTabWidget>

class Qutty : public QObject
{
    Q_OBJECT
public:
    explicit Qutty(QObject* parent, QTabWidget* tabWidget);
    
signals:
    

public slots:
    bool createNewTab();
private slots:
    bool initTab();
    void closeTab(int tabN);

private:
    QTabWidget* tabWidget;

};

#endif // QUTTY_H
