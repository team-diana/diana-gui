#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include <QWidget>

/**
* Classe base per pagine di configurazione.
*/

class Settings_page : public QWidget
{
    Q_OBJECT
    
public:
    Settings_page(QWidget *parent = 0);
    virtual ~Settings_page() = 0;

public slots:
    virtual void apply();
    
signals:
    // Avvisa classe Settings quando sono state fatte delle modifiche.
    void newChanges();

};

#endif // SETTINGS_PAGE_H
