#ifndef TEST_ELECTRONIC_DATA_H
#define TEST_ELECTRONIC_DATA_H

#include "abstract_electronic_data_manager.h"

#include <QTimer>

/**
 * @brief The TestElectronicData class
 * Classe per testare il funzionamento della gui
 */

class TestElectronicDataManager : public AbstractElectronicDataManager
{
    Q_OBJECT

public:
    TestElectronicDataManager();
    ~TestElectronicDataManager();

private slots:
    void updateData();

private:
    QTimer updateTimer;
};

#endif // TEST_ELECTRONIC_DATA_H
