#ifndef ELECTRONIC_VIEW_H
#define ELECTRONIC_VIEW_H

#include <QObject>
#include <QLabel>
#include <QMap>
#include <QTime>
#include <electronicdataview.h>
#include <abstract_electronic_data_manager.h>

class ElectronicView : public QWidget
{
    Q_OBJECT
public:
    explicit ElectronicView(QWidget* canvas, QWidget* radioButtonContainer);
    virtual ~ElectronicView();
    
public:
    void setElectronicDataManager(AbstractElectronicDataManager* electronicDataManager);
    void setElectronicDataViews(const QMap<QString, ElectronicDataView> electronicDataViews) {
        this->electronicDataViews = electronicDataViews;
    }
    void cleanCanvas();
    void setupCanvas();
    void resizeCanvas();
    static QStringList electronicDataNames;

public slots:
    void updateData();
    void setShowCategory(int cat);

private:
    void setPositionInProportion(QWidget* widget, int x, int y, QSize imageSize, QSize canvasSize);
    void readElectronicDataViewsFromFile();
    void setupRadioButtons(QWidget *radioButtonContainer);

protected slots:
    void resizeEvent(QResizeEvent *);

private:
    QWidget* canvas;
    AbstractElectronicDataManager* electronicDataManager;
    QLabel* imageLabel;
    bool canvasReady;
    float imageHeightFactor;
    QMap<QString, ElectronicDataView> electronicDataViews;
    QMap<QString, QLabel*> electronicDataLabels;
    Category shownCategory;
    QSize centerOffset;

};

#endif // ELECTRONIC_VIEW_H
