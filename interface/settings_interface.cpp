#include "settings_interface.h"

#include "ui_settings_interface.h"

#include <QSettings>
#include <QFileDialog>
#include <electronicdataview.h>

QString Settings_interface::ELECTRONIC_VIEW_CSV_FILENAME = "config/electronicViews.csv";


Settings_interface::Settings_interface(QWidget *parent) :
    Settings_page(parent),
    ui(new Ui::Settings_interface)
{
    ui->setupUi(this);
    ui->expertView->setHidden(true);

}

// Salva le modifiche in QSettings
void Settings_interface::apply() {
    // do nothing.
}

Settings_interface::~Settings_interface()
{
    delete ui;
}

void Settings_interface::readFromSavedCsv() {
    ElectronicDataViewReader reader;
    QMap<QString, ElectronicDataView> views = reader.readElectronicDataViewFromCsv(ELECTRONIC_VIEW_CSV_FILENAME);

//    ui->electronicViewTableWidget->setColumnCount(6);
//    ui->electronicViewTableWidget->setEntryCount(views.count());

    int r,c;
    r = c = 0;
    for(QMap<QString, ElectronicDataView>::Iterator it = views.begin(); it != views.end(); it++) {
//        ui->electronicViewTableWidget->setItem(r, c++, it.key());
//        ElectronicDataView view = it.value();
//        ui->electronicViewTableWidget->setItem(r, c++, view.show);
//        ui->electronicViewTableWidget->setItem(r, c++, view.threshold);
//        ui->electronicViewTableWidget->setItem(r, c++, view.x);
//        ui->electronicViewTableWidget->setItem(r, c++, view.y);
//        r++;
    }
}

void Settings_interface::saveToCsv() {
}

