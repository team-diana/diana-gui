/*
 * Copyright (C) 2012 Rajendran Thirupugalsamy
 * See LICENSE for full copyright and license information.
 * See COPYING for distribution information.
 */

#include "qutty_config_window.h"
#include "GuiMainWindow.h"
#include "GuiTerminalWindow.h"
#include "ui_Qutty_config_window.h"
#include<QVariant>
#include <QAbstractButton>
#include<QRadioButton>
#include<QString>
#include "QtCommon.h"
#include "QtConfig.h"
extern "C" {
#include "putty.h"
}

QtConfig qutty_config;

Qutty_config_window::Qutty_config_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Qutty_config_window)
{
    memset(&this->cfg, 0, sizeof(Config));

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->treeWidget->topLevelItem(0)->setData(0, Qt::UserRole, GUI_PAGE_SESSION);
    ui->treeWidget->topLevelItem(0)->child(0)->setData(0, Qt::UserRole, GUI_PAGE_LOGGING);
    ui->treeWidget->topLevelItem(1)->setData(0, Qt::UserRole, GUI_PAGE_TERMINAL);
    ui->treeWidget->topLevelItem(1)->child(0)->setData(0, Qt::UserRole, GUI_PAGE_KEYBOARD);
    ui->treeWidget->topLevelItem(1)->child(1)->setData(0, Qt::UserRole, GUI_PAGE_BELL);
    ui->treeWidget->topLevelItem(1)->child(2)->setData(0, Qt::UserRole, GUI_PAGE_FEATURES);
    ui->treeWidget->topLevelItem(2)->setData(0, Qt::UserRole, GUI_PAGE_WINDOW);
    ui->treeWidget->topLevelItem(2)->child(0)->setData(0, Qt::UserRole, GUI_PAGE_APPEARANCE);
    ui->treeWidget->topLevelItem(2)->child(1)->setData(0, Qt::UserRole, GUI_PAGE_BEHAVIOUR);
    ui->treeWidget->topLevelItem(2)->child(2)->setData(0, Qt::UserRole, GUI_PAGE_TRANSLATION);
    ui->treeWidget->topLevelItem(2)->child(3)->setData(0, Qt::UserRole, GUI_PAGE_SELECTION);
    ui->treeWidget->topLevelItem(2)->child(4)->setData(0, Qt::UserRole, GUI_PAGE_COLOURS);
    ui->treeWidget->topLevelItem(3)->setData(0, Qt::UserRole, GUI_PAGE_CONNECTION);
    ui->treeWidget->topLevelItem(3)->child(0)->setData(0, Qt::UserRole, GUI_PAGE_DATA);
    ui->treeWidget->topLevelItem(3)->child(1)->setData(0, Qt::UserRole, GUI_PAGE_PROXY);
    ui->treeWidget->topLevelItem(3)->child(2)->setData(0, Qt::UserRole, GUI_PAGE_TELNET);
    ui->treeWidget->topLevelItem(3)->child(3)->setData(0, Qt::UserRole, GUI_PAGE_RLOGIN);
    ui->treeWidget->topLevelItem(3)->child(4)->setData(0, Qt::UserRole, GUI_PAGE_SSH);
    ui->treeWidget->topLevelItem(3)->child(4)->child(0)->setData(0, Qt::UserRole, GUI_PAGE_KEX);
    ui->treeWidget->topLevelItem(3)->child(4)->child(1)->setData(0, Qt::UserRole, GUI_PAGE_AUTH);
    ui->treeWidget->topLevelItem(3)->child(4)->child(1)->child(0)->setData(0, Qt::UserRole, GUI_PAGE_GSSAPI);
    ui->treeWidget->topLevelItem(3)->child(4)->child(2)->setData(0, Qt::UserRole, GUI_PAGE_TTY);
    ui->treeWidget->topLevelItem(3)->child(4)->child(3)->setData(0, Qt::UserRole, GUI_PAGE_X11);
    ui->treeWidget->topLevelItem(3)->child(4)->child(4)->setData(0, Qt::UserRole, GUI_PAGE_TUNNELS);
    ui->treeWidget->topLevelItem(3)->child(4)->child(5)->setData(0, Qt::UserRole, GUI_PAGE_BUGS);
    ui->treeWidget->topLevelItem(3)->child(5)->setData(0, Qt::UserRole, GUI_PAGE_SERIAL);

    /* Options controlling session logging */

    ui->gp_seslog->setId(ui->rb_sessionlog_none, LGTYP_NONE);
    ui->gp_seslog->setId(ui->rb_sessionlog_printout, LGTYP_ASCII);
    ui->gp_seslog->setId(ui->rb_sessionlog_alloutput, LGTYP_DEBUG);
    ui->gp_seslog->setId(ui->rb_sessionlog_sshpacket, LGTYP_PACKETS);
    ui->gp_seslog->setId(ui->rb_sessionlog_rawdata, LGTYP_SSHRAW);

    ui->gp_logfile->setId(ui->rb_sessionlog_overwrite, LGXF_OVR);
    ui->gp_logfile->setId(ui->rb_sessionlog_append, LGXF_APN);
    ui->gp_logfile->setId(ui->rb_sessionlog_askuser, LGXF_ASK);

    ui->gp_termopt_echo->setId(ui->rb_termopt_echoauto, AUTO);
    ui->gp_termopt_echo->setId(ui->rb_termopt_echoon, FORCE_ON);
    ui->gp_termopt_echo->setId(ui->rb_termopt_echooff, FORCE_OFF);

    ui->gp_termopt_edit->setId(ui->rb_termopt_editauto,  AUTO);
    ui->gp_termopt_edit->setId(ui->rb_termopt_editon, FORCE_ON);
    ui->gp_termopt_edit->setId(ui->rb_termopt_editoff, FORCE_OFF);

    ui->gp_fnkeys->setId(ui->rb_fnkeys_esc, FUNKY_TILDE);
    ui->gp_fnkeys->setId(ui->rb_fnkeys_linux, FUNKY_LINUX);
    ui->gp_fnkeys->setId(ui->rb_fnkeys_xtermr6, FUNKY_XTERM);
    ui->gp_fnkeys->setId(ui->rb_fnkeys_vt400, FUNKY_VT400);
    ui->gp_fnkeys->setId(ui->rb_fnkeys_vt100, FUNKY_VT100P);
    ui->gp_fnkeys->setId(ui->rb_fnkeys_sco, FUNKY_SCO);

    ui->gp_remote_qtitle_action->setId(ui->rb_featqtitle_none, TITLE_NONE);
    ui->gp_remote_qtitle_action->setId(ui->rb_featqtitle_empstring, TITLE_EMPTY);
    ui->gp_remote_qtitle_action->setId(ui->rb_featqtitle_wndtitle, TITLE_REAL);

    ui->gp_resize_action->setId(ui->rb_wndresz_rowcolno, RESIZE_TERM);
    ui->gp_resize_action->setId(ui->rb_wndresz_fontsize, RESIZE_FONT);
    ui->gp_resize_action->setId(ui->rb_wndresz_onlywhenmax, RESIZE_EITHER);
    ui->gp_resize_action->setId(ui->rb_wndresz_forbid, RESIZE_DISABLED);

    ui->gp_addressfamily->setId(ui->rb_connectprotocol_auto, ADDRTYPE_UNSPEC);
    ui->gp_addressfamily->setId(ui->rb_connectprotocol_ipv4, ADDRTYPE_IPV4);
    ui->gp_addressfamily->setId(ui->rb_connectprotocol_ipv6, ADDRTYPE_IPV6);


    this->getConfig();

    this->loadSessionNames();

    qutty_config.restoreConfig();
}

Qutty_config_window::~Qutty_config_window()
{
    delete ui;
}

void Qutty_config_window::on_rb_contype_telnet_clicked()
{
    ui->le_port->setText("23");
}

void Qutty_config_window::on_rb_contype_ssh_clicked()
{
   ui->le_port->setText("22");
}

void Qutty_config_window::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->stackedWidget->setCurrentIndex(item->data(column,  Qt::UserRole).toInt());
}

void qstring_to_char(char *dst, QString src, int dstlen)
{
    QByteArray name = src.toUtf8();
    strncpy(dst, name.constData(), dstlen);
}

void Qutty_config_window::on_buttonBox_accepted()
{
    emit onAccepted();
}

void Qutty_config_window::on_buttonBox_rejected()
{
    this->close();
}


void Qutty_config_window::setConfig(Config *_cfg)
{
    this->cfg = *_cfg;

    // update the ui with the given settings
    ui->le_hostname->setText(cfg.host);
    ui->le_port->setText(QString::number(cfg.port));
    (cfg.protocol==PROT_SSH ? ui->rb_contype_ssh : ui->rb_contype_telnet)->click();
    ui->le_saved_sess->setText(cfg.config_name);
    QList<QListWidgetItem*> sel_saved_sess = ui->l_saved_sess->findItems(cfg.config_name, Qt::MatchExactly);
    if (sel_saved_sess.size() > 0)
        ui->l_saved_sess->setCurrentItem(sel_saved_sess[0]);

    /* Options controlling session logging */
    ui->gp_seslog->button(cfg.logtype)->click();
    ui->le_sessionlog_filename->setText(cfg.logfilename.path);
    ui->gp_logfile->button(cfg.logxfovr)->click();
    ui->chb_sessionlog_flush->setChecked(cfg.logflush);
    ui->chb_sessionlog_omitpasswd->setChecked(cfg.logomitpass);
    ui->chb_sessionlog_omitdata->setChecked(cfg.logomitdata);

    /* Options controlling the terminal emulation */
    ui->chb_terminaloption_autowrap->setChecked(cfg.wrap_mode);
    ui->chb_terminaloption_decorigin->setChecked(cfg.dec_om);
    ui->chb_terminaloption_lf->setChecked(cfg.lfhascr);
    ui->chb_terminaloption_bgcolor->setChecked(cfg.bce);
    ui->chb_terminaloption_blinktext->setChecked(cfg.blinktext);
    ui->le_termopt_ansback->setText(cfg.answerback);
    ui->gp_termopt_echo->button(cfg.localecho)->click();
    ui->gp_termopt_edit->button(cfg.localedit)->click();

    /* keyboard options */
    (cfg.bksp_is_delete ? ui->rb_backspacekey_ctrlh : ui->rb_backspace_ctrl127)
            ->setChecked(true);
    (cfg.rxvt_homeend ? ui->rb_homeendkeys_rxvt : ui->rb_homeendkeys_std)
            ->setChecked(true);
    ui->gp_fnkeys->button(cfg.funky_type)->click();
    (cfg.app_cursor ? ui->rb_inicursorkeys_app : ui->rb_inicursorkeys_normal)
            ->setChecked(true);
    (cfg.nethack_keypad ? ui->rb_ininumerickeys_nethack :
        cfg.app_keypad ? ui->rb_ininumkeys_app :
                         ui->rb_ininumkeys_normal)
            ->setChecked(true);
    ui->chb_altgrkey->setChecked(cfg.compose_key);
    ui->chb_ctrl_alt->setChecked(cfg.ctrlaltkeys);

    /* terminal features */
    ui->chb_no_applic_c->setChecked(cfg.no_applic_c);
    ui->chb_no_applic_k->setChecked(cfg.no_applic_k);
    ui->chb_no_mouse_rep->setChecked(cfg.no_mouse_rep);
    ui->chb_no_remote_resize->setChecked(cfg.no_remote_resize);
    ui->chb_no_alt_screen->setChecked(cfg.no_alt_screen);
    ui->chb_no_remote_wintitle->setChecked(cfg.no_remote_wintitle);
    ui->chb_no_dbackspace->setChecked(cfg.no_dbackspace);
    ui->chb_no_remote_charset->setChecked(cfg.no_remote_charset);
    ui->chb_no_arabic->setChecked(cfg.arabicshaping);
    ui->chb_no_bidi->setChecked(cfg.bidi);
    ui->gp_remote_qtitle_action->button(cfg.remote_qtitle_action)->click();

    /* window options */
    ui->le_window_column->setText(QString::number(cfg.width));
    ui->le_window_row->setText(QString::number(cfg.height));
    ui->le_wndscroll_lines->setText(QString::number(cfg.savelines));
    ui->chb_wndscroll_display->setChecked(cfg.scrollbar);
    ui->chb_wndscroll_fullscreen->setChecked(cfg.scrollbar_in_fullscreen);
    ui->chb_wndscroll_resetdisply->setChecked(cfg.scroll_on_disp);
    ui->chb_wndscroll_resetkeypress->setChecked(cfg.scroll_on_key);
    ui->chb_wndscroll_pusherasedtext->setChecked(cfg.erase_to_scrollback);
    ui->gp_resize_action->button(cfg.resize_action)->click();

    /* connection options */
    ui->le_ping_interval->setText(QString::number(cfg.ping_interval));
    ui->chb_tcp_keepalive->setChecked(cfg.tcp_keepalives);
    ui->chb_tcp_nodelay->setChecked(cfg.tcp_nodelay);
    ui->gp_addressfamily->button(cfg.addressfamily)->click();
    ui->le_loghost->setText(cfg.loghost);

    /* connection data options */
    ui->le_datausername->setText(cfg.username);
    (cfg.username_from_env ? ui->rb_datausername_systemsuse : ui->rb_datausername_prompt)
            ->setChecked(true);
    ui->le_termtype->setText(cfg.termtype);
    ui->le_termspeed->setText(cfg.termspeed);

    /* ssh auth options */
    ui->chb_ssh_no_userauth->setChecked(cfg.ssh_no_userauth);
    ui->chb_ssh_show_banner->setChecked(cfg.ssh_show_banner);
    ui->chb_ssh_tryagent->setChecked(cfg.tryagent);
    ui->chb_ssh_try_tis_auth->setChecked(cfg.try_tis_auth);
    ui->chb_ssh_try_ki_auth->setChecked(cfg.try_ki_auth);
    ui->chb_ssh_agentfwd->setChecked(cfg.agentfwd);
    ui->chb_ssh_change_username->setChecked(cfg.change_username);
    ui->le_ssh_auth_keyfile->setText(cfg.keyfile.path);
}

Config *Qutty_config_window::getConfig()
{
    Config *cfg = &this->cfg;

    // update the config with current ui selection and return it
    qstring_to_char(cfg->host, ui->le_hostname->text(), sizeof(cfg->host));
    cfg->port = ui->le_port->text().toInt();
    cfg->protocol = ui->gp_contype->checkedButton()==ui->rb_contype_ssh ? PROT_SSH :
                                                                        PROT_TELNET ;
    if(ui->le_saved_sess->text() != "")
        qstring_to_char(cfg->config_name, ui->le_saved_sess->text(), sizeof(cfg->config_name));
    else if (ui->l_saved_sess->currentItem())
        qstring_to_char(cfg->config_name, ui->l_saved_sess->currentItem()->text(), sizeof(cfg->config_name));

    /* Options controlling session logging */
    cfg->logtype = ui->gp_seslog->checkedId();
    qstring_to_char(cfg->logfilename.path, ui->le_sessionlog_filename->text(), sizeof(cfg->logfilename.path));
    cfg->logxfovr = ui->gp_logfile->checkedId();
    cfg->logflush = ui->chb_sessionlog_flush->isChecked() ? 1 : 0 ;
    cfg->logomitpass = ui->chb_sessionlog_omitpasswd->isChecked() ? 1 : 0 ;
    cfg->logomitdata = ui->chb_sessionlog_omitdata->isChecked() ? 1 : 0 ;

    /* Options controlling the terminal emulation */
    cfg->wrap_mode = ui->chb_terminaloption_autowrap->isChecked() ? 1 : 0;
    cfg->dec_om = ui->chb_terminaloption_decorigin->isChecked() ? 1 : 0;
    cfg->lfhascr = ui->chb_terminaloption_lf->isChecked() ? 1 : 0;
    cfg->bce = ui->chb_terminaloption_bgcolor->isChecked() ? 1 : 0;
    cfg->blinktext = ui->chb_terminaloption_blinktext->isChecked() ? 1 : 0;
    qstring_to_char(cfg->answerback, ui->le_termopt_ansback->text(), sizeof(cfg->answerback));
    cfg->localecho = ui->gp_termopt_echo->checkedId();
    cfg->localedit = ui->gp_termopt_edit->checkedId();

    /* keyboard options */
    cfg->bksp_is_delete = ui->rb_backspacekey_ctrlh->isChecked() ? 1 : 0;
    cfg->rxvt_homeend = ui->rb_homeendkeys_rxvt->isChecked() ? 1 : 0;
    cfg->funky_type = ui->gp_fnkeys->checkedId();
    cfg->app_cursor = ui->rb_inicursorkeys_app->isChecked();
    cfg->nethack_keypad = ui->rb_ininumerickeys_nethack->isChecked();
    cfg->app_keypad = ui->rb_ininumkeys_app->isChecked();
    cfg->compose_key = ui->chb_altgrkey->isChecked();
    cfg->ctrlaltkeys = ui->chb_ctrl_alt->isChecked();

    /* terminal features */
    cfg->no_applic_c = ui->chb_no_applic_c->isChecked();
    cfg->no_applic_k = ui->chb_no_applic_k->isChecked();
    cfg->no_mouse_rep = ui->chb_no_mouse_rep->isChecked();
    cfg->no_remote_resize = ui->chb_no_remote_resize->isChecked();
    cfg->no_alt_screen = ui->chb_no_alt_screen->isChecked();
    cfg->no_remote_wintitle = ui->chb_no_remote_wintitle->isChecked();
    cfg->no_dbackspace = ui->chb_no_dbackspace->isChecked();
    cfg->no_remote_charset = ui->chb_no_remote_charset->isChecked();
    cfg->arabicshaping = ui->chb_no_arabic->isChecked();
    cfg->bidi = ui->chb_no_bidi->isChecked();
    cfg->remote_qtitle_action = ui->gp_remote_qtitle_action->checkedId();

    /* window options */
    cfg->width = ui->le_window_column->text().toInt();
    cfg->height = ui->le_window_row->text().toInt();
    cfg->savelines = ui->le_wndscroll_lines->text().toInt();
    cfg->scrollbar = ui->chb_wndscroll_display->isChecked();
    cfg->scrollbar_in_fullscreen = ui->chb_wndscroll_fullscreen->isChecked();
    cfg->scroll_on_disp = ui->chb_wndscroll_resetdisply->isChecked();
    cfg->scroll_on_key = ui->chb_wndscroll_resetkeypress->isChecked();
    cfg->erase_to_scrollback = ui->chb_wndscroll_pusherasedtext->isChecked();
    cfg->resize_action = ui->gp_resize_action->checkedId();

    /* connection options */
    cfg->ping_interval = ui->le_ping_interval->text().toInt();
    cfg->tcp_keepalives = ui->chb_tcp_keepalive->isChecked();
    cfg->tcp_nodelay = ui->chb_tcp_nodelay->isChecked();
    cfg->addressfamily = ui->gp_addressfamily->checkedId();
    qstring_to_char(cfg->loghost, ui->le_loghost->text(), sizeof(cfg->loghost));

    /* connection data options */
    qstring_to_char(cfg->username, ui->le_datausername->text(), sizeof(cfg->username));
    cfg->username_from_env = ui->rb_datausername_systemsuse->isChecked();
    qstring_to_char(cfg->termtype, ui->le_termtype->text(), sizeof(cfg->termtype));
    qstring_to_char(cfg->termspeed, ui->le_termspeed->text(), sizeof(cfg->termspeed));

    /* ssh auth options */
    cfg->ssh_no_userauth = ui->chb_ssh_no_userauth->isChecked();
    cfg->ssh_show_banner = ui->chb_ssh_show_banner->isChecked();
    cfg->tryagent = ui->chb_ssh_tryagent->isChecked();
    cfg->try_tis_auth = ui->chb_ssh_try_tis_auth->isChecked();
    cfg->try_ki_auth = ui->chb_ssh_try_ki_auth->isChecked();
    cfg->agentfwd = ui->chb_ssh_agentfwd->isChecked();
    cfg->change_username = ui->chb_ssh_change_username->isChecked();
    qstring_to_char(cfg->keyfile.path, ui->le_ssh_auth_keyfile->text(),
                    sizeof(cfg->keyfile.path));

    return cfg;
}

void Qutty_config_window::loadSessionNames()
{
    ui->l_saved_sess->clear();
    for(std::map<string, Config>::iterator it = qutty_config.config_list.begin();
        it != qutty_config.config_list.end(); it++) {
        ui->l_saved_sess->addItem(new QListWidgetItem(it->first.c_str()));
    }
}

void Qutty_config_window::on_b_load_sess_clicked()
{
    char config_name[100];
    if (!ui->l_saved_sess->currentItem())
        return;
    qstring_to_char(config_name, ui->l_saved_sess->currentItem()->text(), sizeof(config_name));
    if (qutty_config.config_list.find(config_name) == qutty_config.config_list.end())
        return;
    setConfig(&qutty_config.config_list[config_name]);
}

void Qutty_config_window::on_b_save_sess_clicked()
{
    Config *cfg = this->getConfig();
    qutty_config.config_list[cfg->config_name] = *cfg;
    qutty_config.saveConfig();
    qutty_config.restoreConfig();
    loadSessionNames();
}

void Qutty_config_window::loadDefaultSettings()
{
    if (qutty_config.config_list.find(QUTTY_DEFAULT_CONFIG_SETTINGS)
            != qutty_config.config_list.end()) {
        setConfig(&qutty_config.config_list[QUTTY_DEFAULT_CONFIG_SETTINGS]);
        ui->le_saved_sess->setText(QUTTY_DEFAULT_CONFIG_SETTINGS);
    }
}

void Qutty_config_window::on_b_delete_sess_clicked()
{
    char config_name[100];
    if (!ui->l_saved_sess->currentItem())
        return;
    qstring_to_char(config_name, ui->l_saved_sess->currentItem()->text(), sizeof(config_name));
    if (ui->l_saved_sess->currentItem()->text() == QUTTY_DEFAULT_CONFIG_SETTINGS)
        return;
    if (qutty_config.config_list.find(config_name) == qutty_config.config_list.end())
        return;
    qutty_config.config_list.erase(config_name);
    qutty_config.saveConfig();
    qutty_config.restoreConfig();
    loadSessionNames();
}

void Qutty_config_window::on_l_saved_sess_doubleClicked(const QModelIndex &index)
{
    on_b_load_sess_clicked();
    on_buttonBox_accepted();
}

void Qutty_config_window::on_btn_ssh_auth_browse_keyfile_clicked()
{
    ui->le_ssh_auth_keyfile->setText(QFileDialog::getOpenFileName(
                                         this, tr("Select private key file"),
                                         ui->le_ssh_auth_keyfile->text(), tr("*.ppk")));
}
