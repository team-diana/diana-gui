#ifndef ABSTRACT_ELECTRONIC_DATA_H
#define ABSTRACT_ELECTRONIC_DATA_H

#include <QObject>
#include <QMap>


/**
 * @brief Classe astratta per gestire i sensori del rover.
 *
 * Questa classe e` fatta per essere ereditata da altre classi,
 * che devono implementare i metodi relativi ai diversi sensori
 * (I metodi sono ancora in fase di definizione e verrano presto
 * cambiati.
 *
 * Il segnale newData() deve essere emesso all'arrivo di nuovi dati.
 *
 * Ci saranno due implementazioni di questa classe:
 * SerialElectronicData, per ricevere i dati attraverso la seriale
 * e
 * RosElectronicData, per ricevere i dati attraverso il ROS
 *
 * Per evitare di duplicare codice, la gui dovrebbe gestire i dati
 * soltanto attraverso questa classe,
 * e.g.
 * AbstractElectronicData* electronicData = new RosElectrionicData();
 * electronicData->temp1();
 *
 */
class AbstractElectronicDataManager : public QObject
{
    Q_OBJECT
public:
    explicit AbstractElectronicDataManager(QObject *parent = 0);
    virtual ~AbstractElectronicDataManager() = 0;
    
signals:
    void newData();

public slots:
    virtual const QMap<QString, float>& getElectronicData() {return electronicData;}

protected:
    QMap<QString, float> electronicData;

};

#endif // ABSTRACT_ELECTRONIC_DATA_H
