#ifndef ELECTRONICDATASET_H
#define ELECTRONICDATASET_H

#include <QString>
#include <QMap>


enum Category {
    TEMP,
    POWER,
    ENGINE
};

namespace Type {
enum Type {
    FLOAT,
    ON_OFF,
    PERCENTAGE
};
}

struct ElectronicDataView
{
    bool show;
    float threshold;
    float x;
    float y;
    Category category;
    QString unit;
    Type::Type type;

    ElectronicDataView();
};

class ElectronicDataViewReader {
public:
    QMap<QString, ElectronicDataView> readElectronicDataViewFromCsv(QString fileName);

private:
    QMap<QString, ElectronicDataView> electronicDataViews;
    void processLineFromCsv(QString line, int lineNum);
};

#endif // ELECTRONICDATAVIEW_H
