#include "electronicdataview.h"
#include "d_logger.h"

#include <QFile>
#include <QDir>

/**
   Un ElectronicDataView contiene i dettagli del dato da visualizzare

   ad esempio il valore soglia, la posizione della label, la categoria, l'unita di misura.

   esempio file csv:

   /////
   file.csv:

   temp11,1,2,0,350,0,[celsius]
   power1,1,50,-370,-350,1,A

   /////

 * @brief ElectronicDataView::ElectronicDataView
 */
ElectronicDataView::ElectronicDataView() :
    // Valori di defualt
    show(true), threshold(100), x(0), y(0), category(TEMP) {}

// Leggi i dettagli dei dati da visualizzare da un file CSV
QMap<QString, ElectronicDataView> ElectronicDataViewReader::readElectronicDataViewFromCsv(QString fileName) {
    // Apri il file
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int lineNum = 0;
        // Processa una linea per volta
        // Ogni linea corrisponde ad un dato da visualizzare
        while (!file.atEnd())
        {
            QString line = file.readLine();
            processLineFromCsv(line, lineNum++);
        }
        file.close();
    } else {
        dLog("Unable to open " + fileName + "\n Impossible to open electronic data view settings", SERIOUS_ERROR);
        dLog("Current working directory: " + QDir::currentPath());
    }

    // Restituisci i nuovi dati letti.
    return electronicDataViews;
}

void ElectronicDataViewReader::processLineFromCsv(QString line, int lineNum) {
    // Ignora i commenti
    if(line.startsWith('#')) {
        return;
    }

    // E` un file CSV, ogni elemento e` separato da virgole.
    QStringList strings = line.split(",");
    if(strings.count() != 7) {
        dLog("CSV file was malformed at line "+ QString::number(lineNum));
    }

    // Crea una ElectronicDataView per salvare i dettagli.
    ElectronicDataView view;
    // L'index e` una strina univoca che indica quel valore (e.g. temp1, engine2)
    QString index = strings.value(0);
    // Salva i dettagli letti dal file.
    view.show = strings.value(1).toInt();
    view.threshold = strings.value(2).toFloat();
    view.x = strings.value(3).toFloat();
    view.y = strings.value(4).toFloat();
    view.category = (Category)strings.value(5).toInt();

    // Per l'unita di misura ci sono valori speciali che impostiamo noi manualmente.
    // Altri valori speciali verranno aggiunti.
    QString unit = strings.value(6);
    unit = unit.trimmed();
    if(unit == "[celsius]") {
        // Unita celsius
        unit = "°C";
    } else if(unit == "[on/off]") {
        // valore booleano
        view.type = Type::ON_OFF;
        unit = "";
    }
    view.unit = unit;

    // Aggiungi infine i dettagli relativi ad un valore nella map.
    electronicDataViews.insert(index, view);
}
