#ifndef SETTINGS_H
#define SETTINGS_H

/**
* Finestra per gestire le impostazioni della gui.
* Questo dialog ospita i singoli widget per ogni categoria,
* permettendo di selezionarli, visualizzandoli uno alla volta.
**/

#include "settings_network.h"
#include "settings_interface.h"

#include <QDialog>

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

namespace Ui {
class settings;
}

class Settings : public QDialog
{
    Q_OBJECT
    
public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private slots:
    void save();
    void cancel();
    void apply();
    void onNewChanges();
    

signals:
    // Quando l'utente applica una modifica avvisa le altre classi.
    void settingsChanged();

private:
    void createIcons();

private:
    Ui::settings *ui;
    Settings_network* settingsNetwork;
    Settings_interface* settingsInterface;
    bool newChanges;
};

#endif // SETTINGS_H
