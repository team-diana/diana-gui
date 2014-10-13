#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include <QMainWindow>
#include <QBitmap>
#include "comunication.h"
#include "cam.h"
#include "electronic_view.h"

namespace Ui
{
class Command_interface;
}

class Command_interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Command_interface(QWidget *parent = NULL);
    ~Command_interface();

    Ui::Command_interface *ui;

public slots:

    void startImageRq();
    void connectSerial();
    void connectXBee();
    void connectJoystick();
    void disconnection();

    void sendSpeed();
    void offMotors();
    void powerOnMotor();
    void powerOffMotor();
    void stopMotors();
    void powerOnBoard();
    void powerOffBoard();
    void caBoard();
    void chargeBoard();
    void dischargeBoard();
    void reqData();
    void sendPov();
    void convertspeed();
    void onImageDownloadError();

    void setImageRefreshPeriod(int periodInSecond);
    void refreshImages();
    void showSettings();
    void switchFullScreenMode();

    void connectAction();

private:
    void connectCamButtons();

    void saveInterfaceSettings();
    void loadInterfaceSettings();

private:

    Comunication* com;
    Cam *Camera;
    QTimer *timer;
    DownloadThread *downloadT;
    ElectronicView* electronicView;
    short int camindex;
    short int imageindex;
    short int cam1index;
    short int cam2index;
    bool disabled;

    int isP;
    QString toN;
    QStringList camNames;

};

#endif // COMMAND_INTERFACE_H

