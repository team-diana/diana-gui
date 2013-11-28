#ifndef SETTINGS_INTERFACE_H
#define SETTINGS_INTERFACE_H

#include <QWidget>
#include "settings_page.h"

#include <QAbstractItemModel>

/**
* Widget per la configurazione dell'interfaccia
*/

namespace Ui {
class Settings_interface;
}

class Settings_interface : public Settings_page
{
    Q_OBJECT

public:
    explicit Settings_interface(QWidget *parent = 0);
    ~Settings_interface();

public slots:
    virtual void apply();

private slots:
    void readFromSavedCsv();
    void saveToCsv();

private:
    Ui::Settings_interface *ui;
    QAbstractItemModel* itemModel;
    static QString ELECTRONIC_VIEW_CSV_FILENAME;
};

#endif // SETTINGS_INTERFACE_H
