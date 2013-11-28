#ifndef SETTINGS_NETWORK_H
#define SETTINGS_NETWORK_H

#include <QWidget>
#include "settings_page.h"

/**
* Widget per la configurazione della connessione.
*/

namespace Ui {
class Settings_network;
}

class Settings_network : public Settings_page
{
    Q_OBJECT
    
public:
    explicit Settings_network(QWidget *parent = 0);
    ~Settings_network();

public slots:
    virtual void apply();

private slots:
    void setTftpAddrDefault();
    void setTftpAddrLocalhost();
    void getPhotoDir();

private:
    Ui::Settings_network *ui;
};

#endif // SETTINGS_NETWORK_H
