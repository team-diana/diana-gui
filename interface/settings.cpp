#include "settings.h"
#include "ui_settings.h"
#include "settings_network.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings),
    settingsNetwork(new Settings_network()),
    settingsInterface(new Settings_interface()),
    newChanges(false)
{
    ui->setupUi(this);

    // Aggiungi i widget per ogni categoria

    ui->stackedWidget->addWidget(settingsNetwork);
    ui->stackedWidget->addWidget(settingsInterface);

    ui->stackedWidget->setCurrentIndex(0);

    // Controlla che i button siano presenti nella ui e connetti

    QPushButton* button = ui->buttonBox->button(QDialogButtonBox::Save);
    Q_ASSERT(button); // Controlla valore NULL.
    connect(button, SIGNAL(clicked()), this, SLOT(save()));
    button = ui->buttonBox->button(QDialogButtonBox::Cancel);
    Q_ASSERT(button);
    connect(button, SIGNAL(clicked()), this, SLOT(cancel()));
    button = ui->buttonBox->button(QDialogButtonBox::Apply);
    Q_ASSERT(button);
    connect(button, SIGNAL(clicked()), this, SLOT(apply()));
    
    connect(settingsNetwork, SIGNAL(newChanges()), this, SLOT(onNewChanges()));

    ui->stackedWidget->addWidget(settingsNetwork);

    createIcons();

    ui->pageWidgetList->setCurrentRow(0);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::createIcons()
{
    // Aggiungi le icone per ogni categoria.
    QListWidgetItem *interfaceButton = new QListWidgetItem(ui->pageWidgetList);
//    networkButton->setIcon(QIcon(":/images/config.png"));
    interfaceButton->setText(tr("Interface"));
    interfaceButton->setTextAlignment(Qt::AlignHCenter);
    interfaceButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *networkButton = new QListWidgetItem(ui->pageWidgetList);
//    networkButton->setIcon(QIcon(":/images/config.png"));
    networkButton->setText(tr("Network"));
    networkButton->setTextAlignment(Qt::AlignHCenter);
    networkButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);



    connect(ui->pageWidgetList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

// Cambia categoria quando un'icona viene selezionata.
void Settings::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    ui->stackedWidget->setCurrentIndex(ui->pageWidgetList->row(current));
}

void Settings::save() {
    apply();
    close();
}

void Settings::apply() {
   settingsNetwork->apply();
   emit settingsChanged();
}
void Settings::cancel() {
    if(newChanges) {
        QMessageBox msgBox;
        msgBox.setText("Modifiche non ancora salvate");
        msgBox.setInformativeText("Sono state apportate nuove modifiche, vuoi salvarle?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec(); 
        switch(ret) {
            case QMessageBox::Save:
                apply();
                break;
            case QMessageBox::Cancel:
                return;
            case QMessageBox::Discard:
            default:
                ;
        }
    }
    close();
}

void Settings::onNewChanges()
{
    newChanges = true;
}
