#include "ros_electronic_data_manager.h"

#include <QTimer>
#include <QTime>

ROSElectronicDataManager::ROSElectronicDataManager(QObject *parent) :
    AbstractElectronicDataManager(parent)
{
}

ROSElectronicDataManager::~ROSElectronicDataManager() {}

