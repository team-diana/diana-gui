#include "test_electronic_data_manager.h"
#include "electronic_view.h"
#include <QTime>

TestElectronicDataManager::TestElectronicDataManager()
{
  connect(&updateTimer, SIGNAL(timeout()), this, SLOT(updateData()));
    updateTimer.setInterval(300);
    updateTimer.start();
}

TestElectronicDataManager::~TestElectronicDataManager() {}


// if the data come all in one, don't emit all stuff, but emit a struct.
void TestElectronicDataManager::updateData() {
    // Random data
    float random = QTime::currentTime().second() % 5 / 0.33f;

    QStringListIterator it(ElectronicView::electronicDataNames);
    while(it.hasNext()) {
        random = (random / 2) + random*2 - 0.12f;
        random /= 3.43;
        electronicData.insert(it.next(), random);
    }

    emit newData();
}
