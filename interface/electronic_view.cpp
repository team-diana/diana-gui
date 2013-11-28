#include "electronic_view.h"

#include <QDebug>
#include <QLayout>
#include <QHBoxLayout>
#include <QTime>
#include <d_logger.h>
#include <QStyle>
#include <QRadioButton>
#include <QButtonGroup>
#include "costants.h"

// Elenco di tutti i dati che devono essere visualizzati.
QStringList ElectronicView::electronicDataNames = QStringList();

/**
   Questa classe permette di visualizzare le temperature, velocita`, volts etc.
   sul disegno del rover. I dati da visualizzare sono elencati in un file.
   I valori invece sono forniti da un AbstractElectronicDataManager, che emette
   un segnale quando ci sono nuovi valori.

 * @brief ElectronicView::ElectronicView
 * @param canvas il widget dove verra` aggiunta l'immagine del rover e le labels
 * @param radioButtonContainer il widget che conterra` i radiobuttons che permettono di
 *          selezionare la categoria di dati da visualizzare.
 */
ElectronicView::ElectronicView(QWidget* canvas, QWidget* radioButtonContainer) :
    QWidget(canvas),
    canvas(canvas),
    canvasReady(false),
    imageLabel(NULL)
{
    // Aggiungi un layout
    canvas->setLayout(new QHBoxLayout());
    canvas->layout()->addWidget(this);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    // Aggiungi i radiobuttons.
    setupRadioButtons(radioButtonContainer);


    // Gli elementi da visualizzare sono scritti su un file.
    // Leggi da questo file gli elementi da visualizzare e le loro caratteristiche.
    readElectronicDataViewsFromFile();
}

ElectronicView::~ElectronicView() {
    cleanCanvas();
}

// Setta il manager che fornira` i valori.
void ElectronicView::setElectronicDataManager(AbstractElectronicDataManager *electronicDataManager) {
    this->electronicDataManager = electronicDataManager;
    electronicDataManager->setParent(this);
    // Quando i valori cambiano, aggiorna i dati!
    connect(electronicDataManager, SIGNAL(newData()), this, SLOT(updateData()));
}

void ElectronicView::updateData() {
    // electronicDataValues e` una mappa che contiene tutti i valori da visualizzare.
    const QMap<QString, float> electronicDataValues = electronicDataManager->getElectronicData();

    if(canvasReady) {
        QFont font;
        font.setPointSize(13);
        // Stile per sfondo nero trasparente e colore verde o rosso se il valore supera la soglia.
        QString underThreshold("QLabel {color:green; background-color: rgba(0, 0, 0, 200);}");
        QString overThreshold("QLabel {color:red; background-color: rgba(0, 0, 0, 200);}");

        // Itera per ogni elemento da visualizzare
        QListIterator<QString> it(electronicDataViews.keys());
        while(it.hasNext()) {
            QString index = it.next();
            ElectronicDataView view = electronicDataViews[index];
            float value = electronicDataValues[index];
            if(!electronicDataLabels.contains(index)) {
                dLog("There is no view for " + index + " data. Unexpected input");
                continue;
            }
            // Formatta il contenuto della label da visualizzare.
            QString content = QString().sprintf("%.2f%s", value, view.unit.toStdString().c_str());

            // Prendi la label relativa, assegna lo stile e il font, riduci le dimensioni
            // per ottenere uno sfondo della label non troppo grande.
            QLabel* label = electronicDataLabels[index];
            label->setStyleSheet( value < view.threshold ? underThreshold : overThreshold);
            label->setFont(font);
            label->setMaximumSize(content.length() * 10 + 5, 18);

            // Imposta infine il testo.
            label->setText(content);
        }
    }

}


// Inizializza il widget che visuallizza il disegno del rover,
// con le labels in sovrimpressione.
void ElectronicView::setupCanvas() {
    // Se il canvas e` uguale a NULL fallisci con errore.
    Q_ASSERT(canvas != NULL);

    // Itera per ogni elemento
    QListIterator<QString> it(electronicDataViews.keys());
    while(it.hasNext()) {
        // Crea una label, aggiungila nella map, assicurati che venga visualizzata
        // in sovrimpressione.
        QLabel* newLabel = new QLabel(canvas);
        electronicDataLabels.insert(it.next(), newLabel);
        newLabel->raise();
    }


    // Carica e imposta il disegno del rover.
    if(imageLabel == NULL) {
        QImage roverImage(":/icons/images/elettronica.jpeg");
        imageHeightFactor = (double)roverImage.height() / roverImage.width();
        if(roverImage.isNull()) {
            qDebug() << "Missing elettronica.jpeg";
        }
        imageLabel = new QLabel(this);
        imageLabel->setPixmap(QPixmap::fromImage(roverImage));
        imageLabel->setScaledContents(true);
        imageLabel->setAlignment(Qt::AlignCenter);

    }
    imageLabel->lower();

    canvasReady = true;
}

// Rimuovi tutto dal Canvas.
// Attenzione! Non funziona bene. Non usare questa funzione per ora...
void ElectronicView::cleanCanvas() {
    canvasReady = false;

    // Elimina le label precedenti
    for(QMap<QString, QLabel*>::Iterator it = electronicDataLabels.begin();
        it != electronicDataLabels.end(); it++) {
        delete it.value();
    }
    electronicDataLabels.clear();

    // Elimina l'immagine del rover
    if(imageLabel != NULL) {
        delete imageLabel;
        imageLabel = NULL;
    }
}

// Ridimensione l'immagine del rover e le labels
void ElectronicView::resizeCanvas() {
    if(!canvasReady) {
        return;
    }

    // Ottieni la dimensione piu` grande possibile,
    // senza cambiare le proporzioni del disegno.
    QRect canvasContent = contentsRect();
    int canvasWidth = canvasContent.width();
    int canvasHeight = canvasContent.height();
    int imageWidth = canvasWidth;
    int imageHeight = canvasWidth * imageHeightFactor;
    if(imageHeight > canvasHeight) {
        imageHeight = canvasHeight;
        imageWidth = imageHeight / imageHeightFactor;
    }
    // Ridimensiona il disegno e mettilo al centro
    imageLabel->setMinimumSize(imageWidth, imageHeight);
    imageLabel->setMaximumSize(imageWidth, imageHeight);
    imageLabel->move(canvasWidth/2.0 - imageWidth/2.0,
                     canvasHeight/2.0 - imageHeight/2.0);

    // Itera per ogni elemento da visualizzare
    QListIterator<QString> it(electronicDataViews.keys());
    while(it.hasNext()) {
        QString index = it.next();
        QLabel* label = electronicDataLabels[index];
        ElectronicDataView view = electronicDataViews[index];
        // Nascondi le altre categorie (e.g. Power e Engine).
        if(view.category != shownCategory) {
            label->setHidden(true);
            continue;
        } else {
            label->setHidden(false);
        }

        // Imposta un offset per correggere leggermente la posizione di tutte le label.
        centerOffset = QSize(-20,0);
        // Metti la label al posto giusto.
        setPositionInProportion(label, view.x, view.y, imageLabel->size(), canvas->size());
    }
}

// Quando la finestra viene ridimensionata, ridimensiona immagine e
// riposiziona le labels
void ElectronicView::resizeEvent(QResizeEvent *) {
    resizeCanvas();
}

// Metti ogni label in una determinata posisione proporzionale
// alla grandezza dell'immagine.
void ElectronicView::setPositionInProportion(QWidget* widget, int x, int y, QSize imageSize, QSize canvasSize) {
    QPoint pos(canvasSize.width()/2.0 + imageSize.width()/1000.0*x + centerOffset.width(),
               canvasSize.height()/2.0 + imageSize.height()/1000.0*y + centerOffset.height());
    widget->move(pos);
}

// Leggi tutti gli elementi da visualizzare da un file.
// Il file contiene nomi, valori soglia, categorie, unita` di misura.
void ElectronicView::readElectronicDataViewsFromFile() {
    ElectronicDataViewReader reader;
    // Il lettore restituisce una map che contiene i dettagli per ciascun elemento.
    // I dettagli sono descritti nella classe ElectronicDataView
    electronicDataViews = reader.readElectronicDataViewFromCsv(ELECTRONIC_VIEW_DEFAULT_CSV_FILENAME);
    electronicDataNames = electronicDataViews.keys();

    // Aggiorna immagine e labels
    cleanCanvas();
    setupCanvas();
}

// Aggiungi i radio buttons sotto l'immagine. Permettono di selezionare
// la categoria da visualizzare
void ElectronicView::setupRadioButtons(QWidget* radioButtonContainer) {
     QLayout *layout = radioButtonContainer->layout();

     QRadioButton *r1 = new QRadioButton("Temp", radioButtonContainer);
     QRadioButton *r2 = new QRadioButton("Power", radioButtonContainer);
     QRadioButton *r3 = new QRadioButton("Engine", radioButtonContainer);
     r1->setMinimumSize(50,0);
     r2->setMinimumSize(50,0);
     r3->setMinimumSize(50,0);
     QString styleSheet("QRadioButton {color:white;}");
     r1->setStyleSheet(styleSheet);
     r2->setStyleSheet(styleSheet);
     r3->setStyleSheet(styleSheet);

     layout->addWidget(r1);
     layout->addWidget(r2);
     layout->addWidget(r3);

     // Il ButtonGroup permette di attivare un solo radiobutton alla volta,
     // inoltre emette un segnale quando si seleziona un radiobutton.
     QButtonGroup *group = new QButtonGroup(radioButtonContainer);
     group->addButton(r1,0);
     group->addButton(r2, 1);
     group->addButton(r3, 2);

     // L'utente ha cambiato categoria, aggiorna!
     connect(group, SIGNAL(buttonClicked(int)), this, SLOT(setShowCategory(int)));

     // Imposta la prima categoria per default.
     r1->setChecked(true);
     shownCategory = (Category)0;
}

// Seleziona la categoria da visualizzare
void ElectronicView::setShowCategory(int cat) {
    shownCategory = (Category) cat;
    resizeCanvas();
}
