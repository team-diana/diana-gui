#include "settings_network.h"
#include "ui_settings_network.h"

#include <QSettings>
#include <QFileDialog>


Settings_network::Settings_network(QWidget *parent) :
    Settings_page(parent),
    ui(new Ui::Settings_network)
{
    ui->setupUi(this);

    connect(ui->tftpDefaultButton, SIGNAL(clicked()), this, SLOT(setTftpAddrDefault()));
    connect(ui->tftpLocalhostButton, SIGNAL(clicked()), this, SLOT(setTftpAddrLocalhost()));
    connect(ui->tftpAddrLineEdit, SIGNAL(textEdited(QString)), this, SIGNAL(newChanges()));
    connect(ui->tftpAddrLineEdit, SIGNAL(textEdited(QString)), this, SIGNAL(newChanges()));
    connect(ui->tftpExecutableLineEdit, SIGNAL(textEdited(QString)), this, SIGNAL(newChanges()));

    // Carica le impostazioni precedenti
    QSettings settings;
    ui->tftpAddrLineEdit->setText(settings.value("tftpAddr", "192.168.50.1").toString());
    ui->photoDirLineEdit->setText(settings.value("tftpImagesDir", "c:\\immaginirover\\").toString());
    ui->tftpExecutableLineEdit->setText(settings.value("tftpExecutable", "c:\\immaginirover\\").toString());

#ifdef _LINUX
    connect(ui->photoDirButton, SIGNAL(clicked()), this, SLOT(getPhotoDir()));
#endif
#ifdef _WINDOWS
#endif

}

void Settings_network::setTftpAddrDefault()
{
    ui->tftpAddrLineEdit->setText("192.168.50.1");
}

void Settings_network::setTftpAddrLocalhost()
{
    ui->tftpAddrLineEdit->setText("127.0.0.1");
}

// Salva le modifiche in QSettings
void Settings_network::apply() {
   QSettings qsettings;

   // TODO: aggiungere regex per controllare validita` indirizzo.
   qsettings.setValue("tftpAddr", ui->tftpAddrLineEdit->text());
   qsettings.setValue("tftpImagesDir", ui->photoDirLineEdit->text());
   qsettings.setValue("tftpExecutable", ui->tftpExecutableLineEdit->text());
}

// Apri un dialog per selezionare la cartella dove verranno salvate le foto.
void Settings_network::getPhotoDir() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.exec();
    QString dir = dialog.selectedFiles().first();
    ui->photoDirLineEdit->setText(dir);
}

Settings_network::~Settings_network()
{
    delete ui;
}
