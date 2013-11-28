#include "console.h"
#include "d_logger.h"

/*
AUTHOR: Giuseppe Federico Gullo
DATE: 12/04/2012
DESCRIPTION: Classe che gestisce la console
*/

//Costruttore della classe (Non c'è niente da costruire, ma è obbligatorio definirlo)


// I QObject hanno una struttura ad albero dove ogni QObject gestisce una lista di child.
// http://qt-project.org/doc/qt-4.8/objecttrees.html
// Per facilitare la gestione della memoria e` utile continuare ad usare questo modello:
Console::Console(QObject* parent) : 
QObject(parent) //< Aggiungi questo oggetto alla lista di child di parent.
{

}

//Filtra i tasti, e se viene premuto invio, manda il comando
bool Console::eventFilter(QObject *obj, QEvent *event)
     {
         if (event->type() == QEvent::KeyPress)
         {
             QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

             if (keyEvent->key()==Qt::Key_Return)   //E' stato premuto invio
             {
                 QString cmd=wnd->toPlainText().split("\n").last().split("Team@Diana: ").last(); //Estrae il comando

                 dLog(QString().sprintf("%s",cmd.toStdString().c_str())); //Questo serve solo per debug

                 if(!isLocal(cmd)) //Se non è un comando locale, lo invia al server
                 {
                     int c=com->send(cmd); //Torna FALSE se non è un comando valido
                     if(!c)
                        wnd->append("Comando sconosciuto, usare 'help' per maggiori informazioni"); //non è un comando valido
                 }
             wnd->append("Team@Diana: ");

             }
             else
             {
                 return QObject::eventFilter(obj, event);
             }
             return true;
         }
         else
         {
             return QObject::eventFilter(obj, event);
         }
     }

//Decifra i comandi locali, ovvero quelli, che interessa solo l'interfaccia e non il server
int Console::isLocal(QString cmd)
{
    if(cmd=="clear")    //pulisce la console
    {
        wnd->clear();
        return 1;
    }
    if(cmd=="help")     //stampa tutti i comandi disponibili
    {
        wnd->append("Sintassi estesa: Nome: valore");
        wnd->append("Sintassi abbreviata: Sigla valore\nComandi disponibili:\n");

        wnd->append("Identificativo\t Nome\t Sigla\t Range\t Descrizione");

        wnd->append("ON\t accendi scheda\t o\t 0-6\t Accendi una scheda");
        wnd->append("OFF\t spegni scheda\t f\t 0-6\t Spegni una scheda");
        wnd->append("CAR\t carica scheda\t e\t 0-5\t Carica una scheda");
        wnd->append("SCA\t scarica scheda\t q\t 0-5\t Scarica una scheda");

        wnd->append("MON\t accendi motore\t h\t \1-4\t Accendi un motore");
        wnd->append("MOF\t spegni motore\t g\t 1-4\t Spegni un motore");
        wnd->append("VE\t velocità \t\t v\t 0-5\t Velocità massima");
        wnd->append("TE\t tempo \t\t t\t 0-5\t Tempo di esecuzione");
        wnd->append("STOP\t blocca motori\t s\t n\t Blocca i motori");

        wnd->append("CA0\t camp master\t a\t 0-5\t Tempo di campionamento Master");
        wnd->append("CA1\t camp potenza\t b\t 0-5\t Tempo di campionamento Potenza");
        wnd->append("CA2\t camp motori\t c\t 0-5\t Tempo di campionamento Motori");
        wnd->append("CA5\t camp sensori\t d\t 0-5\t Tempo di campionamento Sensori");

        wnd->append("POI\t polling \t\t n\t 0,1\t Abita o disabilita polling");

        wnd->append("FAN\t ventola \t\t v\t 0,1\t Abilita o disabilita ventola");


    }

    if(cmd=="clear log") {};

    return 0;
}
