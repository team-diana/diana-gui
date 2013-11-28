#ifndef QUTTYCONFIGWINDOW_H
#define QUTTYCONFIGWINDOW_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QButtonGroup>
#include "QtConfig.h"
#include <QFileDialog>
#include "settings_network.h"
#include <QDialog>

namespace Ui {
class Qutty_config_window;
}

class Qutty_config_window : public QDialog
{
    Q_OBJECT
    enum
    {
        GUI_PAGE_SESSION, GUI_PAGE_LOGGING, GUI_PAGE_TERMINAL, GUI_PAGE_KEYBOARD, GUI_PAGE_BELL, GUI_PAGE_FEATURES,
        GUI_PAGE_WINDOW, GUI_PAGE_APPEARANCE, GUI_PAGE_BEHAVIOUR, GUI_PAGE_TRANSLATION, GUI_PAGE_SELECTION,
        GUI_PAGE_COLOURS, GUI_PAGE_CONNECTION, GUI_PAGE_DATA, GUI_PAGE_PROXY, GUI_PAGE_TELNET, GUI_PAGE_RLOGIN,
        GUI_PAGE_SSH, GUI_PAGE_KEX, GUI_PAGE_AUTH, GUI_PAGE_GSSAPI, GUI_PAGE_TTY, GUI_PAGE_X11, GUI_PAGE_TUNNELS,
        GUI_PAGE_BUGS, GUI_PAGE_SERIAL
    } gui_page_names_t;
    enum
    {
        GUI_LOGLVL_NONE, GUI_LOGLVL_PRINT_OUT, GUI_LOGLVL_ALL_SES_OUT, GUI_LOGLVL_SSH_PACKET, GUI_LOGLVL_SSH_RAWDATA
    } gui_loglevel_t;

    // config that is loaded onto the settings window
    Config cfg;

    signals:
    void onAccepted();

public:
    explicit Qutty_config_window(QWidget *parent = 0);
    ~Qutty_config_window();

    // getter/setter to config in the settings window
    void setConfig(Config *cfg);
    Config *getConfig();

    void loadSessionNames();
    void loadDefaultSettings();

private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_rb_contype_telnet_clicked();

    void on_rb_contype_ssh_clicked();

    void on_b_load_sess_clicked();

    void on_b_save_sess_clicked();

    void on_b_delete_sess_clicked();

    void on_l_saved_sess_doubleClicked(const QModelIndex &index);

    void on_btn_ssh_auth_browse_keyfile_clicked();

private:
    Ui::Qutty_config_window* ui;
};

#endif // Qutty_config_window_H
