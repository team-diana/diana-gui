#ifndef ROS_ELECTRONIC_DATA_H
#define ROS_ELECTRONIC_DATA_H

#include "abstract_electronic_data_manager.h"

#include <QTimer>

/**
 * @brief The ROSElectronicData class
 * Classe per ricevere i dati dei sensori del rover tramite
 * il ROS
 */
class ROSElectronicDataManager : public AbstractElectronicDataManager
{
    Q_OBJECT
public:
    explicit ROSElectronicDataManager(QObject *parent = 0);
    ~ROSElectronicDataManager();
    
};

#endif // ROS_ELECTRONIC_DATA_H
