#include "d_logger.h"

#include <QDebug>

// Funzione globale, e` uno shortcut per fare i log,
// puo` essere usato al posto di qLog() << "log";
void dLog(QString msg, LogLevel lvl) {
    DLogger::getInstance().dLog(msg, lvl);
}

// Vedi http://it.wikipedia.org/wiki/Singleton
DLogger* DLogger::singleton = NULL;

/**
 * @brief DLogger::DLogger
 * @param output
 *Classe usata per gestire tutti i log.
 *Invece di usare QLog possiamo usare questa classe, che visualizza i log
 *nella console della gui.
 */
DLogger::DLogger(QTextEdit* output) :
output(output)
{}

DLogger& DLogger::getInstance() {
    if(!singleton) {
        qDebug() << "DLogger wasn't initialized";
        singleton = new DLogger(NULL);
    }

    return *singleton;
}

DLogger::~DLogger() {}

/**
 * @brief DLogger::initialize
 * @param output widget dove viene mostrato l'output del logger.
 * Inizializza il logger. Questa funzione deve essere chiamata
 * una sola volta all'inizio del programma.
 */
void DLogger::initialize(QTextEdit* output) {
    singleton = new DLogger(output);
}

void DLogger::dLog(QString msg, LogLevel lvl) {
    // TODO: stampare il log su un file!
    if(output != NULL) {
        output->append(msg);
    }
    qDebug() << msg;
}
