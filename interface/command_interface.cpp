/*
AUTHOR: Giuseppe Federico Gullo
DATE: 10/02/2012
DESCRIPTION: Classe Principale del software, questa classe viene richiamata dal ciclo principale
*/
#include "command_interface.h"
#include "ui_command_interface.h"
#include "settings.h"
#include "d_logger.h"

#include "qutty.h"

#include <sstream>
#include <QThread>
#include <QSignalMapper>
#include <QPushButton>
#include <QDebug>
#include <QSettings>

#include <test_electronic_data_manager.h>

using namespace std;

//Costruttore della classe
Command_interface::Command_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Command_interface)
{
    // Imposta parametri dell'applicazione (necessario per utilizzare QSetting)
    QCoreApplication::setOrganizationName("TeamDiana");
    QCoreApplication::setOrganizationDomain("teamdiana.org");
    QCoreApplication::setApplicationName("gui");
    QSettings settings;

    disabled = true;
    ui->setupUi(this);                              //Collega la classe alla  user inteface (UI)
    ui->actionDisconnetti->setDisabled(disabled);   //ActionDisconnetti � un tasto definito nella UI
    ui->et_console->setText("Team@Diana: ");        //et_console � la TextBox che rappresenta la console
    com=new Comunication(this);                           //Inizializza l'istanza della classe comunication(*1)
    com->tab_data=ui->tab_data;
    com->console=ui->et_data;
    com->log=ui->tv_log;
    com->valSpeed=ui->cbox_valSpeed;
    com->valTime=ui->cbox_valTime;
    com->valX=ui->sbox_povs;
    com->valY=ui->sbox_povd;
    com->build_table();
    qutty = new Qutty(this, ui->quttyTab);
    console=new Console(this);                      //Inizializza l'istanza della classe console(*1)
    cmds=new Commands;                              //Inizializza l'istanza della classe controller(*1)
    Camera = new Cam(this->ui->graphicsView , this);                         //Inizializza l'istanza della classe cam
    downloadT = new DownloadThread();
    controller=new QController(this);
    console->wnd=ui->et_console;
    console->com=com;
    console->cmds=cmds;
    controller->log=ui->tv_log;
    electronicView = new ElectronicView(ui->dianaCanvas, ui->dianaRadioButtonContainer);
    electronicView->setElectronicDataManager(new TestElectronicDataManager());
    electronicView->setupCanvas();
    DLogger::initialize(ui->tv_log);
    ui->et_console->installEventFilter(console);
    camindex = 1;
    imageindex = -1;
    timer=new QTimer(this);   //Costruisce un Timer per inserire un delay dopo la pressione di un tasto
    int timerPeriod = settings.value("imageRefreshPeriodSecond", 3).toInt();
    timer->setInterval(timerPeriod * 1000);
    ui->imageDownloadPeriodBox->setValue(timerPeriod);

    loadInterfaceSettings();
}

void Command_interface::setImageRefreshPeriod(int periodInSecond) {
    timer->setInterval(periodInSecond * 1000);
    QSettings settings;
    settings.setValue("imageRefreshPeriodSecond", periodInSecond);
}

//Questa funzione associa ad ogni tasto un'azione (funzione) che verr� eseguita alla sua pressione
void Command_interface::connectAction()
{
    ui->tv_log->append("Inizializzazione interfaccia...");
    connect(ui->actionEsci, SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(ui->actionConnetti_via_XBee, SIGNAL(triggered()),this,SLOT(connectXBee()));
    connect(ui->actionConnetti_via_seriale, SIGNAL(triggered()),this,SLOT(connectSerial()));
    connect(ui->actionDisconnetti, SIGNAL(triggered()),this,SLOT(disconnection()));
    connect(ui->actionOpzioni, SIGNAL(triggered()),this,SLOT(showSettings()));
    connect(ui->actionFull_Screen, SIGNAL(triggered()), this, SLOT(switchFullScreenMode()));
    connect(ui->bt_joystick_2, SIGNAL(clicked()),this,SLOT(connectJoystick()));
    connect(ui->bt_motor, SIGNAL(clicked()),this,SLOT(sendSpeed()));
    connect(ui->powerOnMotor, SIGNAL(clicked()),this,SLOT(powerOnMotor()));
    connect(ui->powerOffMotor, SIGNAL(clicked()),this,SLOT(powerOffMotor()));
    connect(ui->bt_offMotors, SIGNAL(clicked()),this,SLOT(offMotors()));
    connect(ui->activateBrake,SIGNAL(clicked()),this,SLOT(stopMotors()));
    connect(ui->powerOnBoard, SIGNAL(clicked()),this,SLOT(powerOnBoard()));
    connect(ui->powerOffBoard, SIGNAL(clicked()),this,SLOT(powerOffBoard()));
    connect(ui->bt_board,SIGNAL(clicked()),this,SLOT(caBoard()));
    connect(ui->chargeBoard,SIGNAL(clicked()),this,SLOT(chargeBoard()));
    connect(ui->dischargeBoard,SIGNAL(clicked()),this,SLOT(dischargeBoard()));
    //connect(ui->bt_reqData, SIGNAL(clicked()),this,SLOT(reqData()));
    connect(ui->bt_pov,SIGNAL(clicked()),this,SLOT(sendPov()));
    connect(timer, SIGNAL(timeout()),this,SLOT(refreshImages()));
    connect(ui->refreshImage, SIGNAL(clicked()), this, SLOT(startImageRq()));
    connect(ui->sbox_povs, SIGNAL(valueChanged(QString)), this, SLOT(convertspeed()));
    connect(ui->sbox_povd, SIGNAL(valueChanged(QString)), this, SLOT(convertspeed()));
    connect(ui->cbox_valSpeed, SIGNAL(currentIndexChanged(QString)), this, SLOT(convertspeed()));
    connect(ui->cbox_valTime, SIGNAL(currentIndexChanged(QString)), this, SLOT(convertspeed()));
    connect(downloadT, SIGNAL(processError()), this, SLOT(onImageDownloadError()));
    connect(ui->imageDownloadPeriodBox, SIGNAL(valueChanged(int)), this, SLOT(setImageRefreshPeriod(int)));
    connect(ui->newQuttyTabButton, SIGNAL(clicked()), qutty, SLOT(createNewTab()));
    connectCamButtons();

    ui->tv_log->append("Eseguito");
}

void Command_interface::connectCamButtons()
{
    // Crea un array temporaneo per salvare i puntatori ad ogni camera.
    QPushButton* camPushButtons[] = {ui->cam_1, ui->cam_2, ui->cam_3};
    // Aggiungi nella lista di stringhe i nomi dei file relativi ad ogni camera.
    camNames << "right.png"  << "left.png";
    
    // Crea un QSignalMapper che indica alla funzione changeCam() quale camera attivare
    // in base al numero del QPushButton premuto.
    QSignalMapper* signalMapper = new QSignalMapper(this);

    // Per ogni puntatore nell'array camPushButtons mappa un QPushButton ad un segnale.
    for (unsigned int i = 0; i < sizeof(camPushButtons)/sizeof(QPushButton*); ++i) {
        signalMapper->setMapping(camPushButtons[i], i);
        connect(camPushButtons[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
    }
    
    connect(signalMapper, SIGNAL(mapped(int)), Camera, SLOT(changeCam(int)));

}

void Command_interface::caBoard()
{
    QString cmd=ui->cbox_selectBoard->currentIndex()+97+toN.number(ui->cbox_valBoard->currentIndex());
    com->send(cmd);
}

void Command_interface::stopMotors()
{
    com->send("s");
}

void Command_interface::chargeBoard() {
    com->send("e"+toN.number(ui->cbox_selectBoard->currentIndex()));
}
void Command_interface::dischargeBoard() {
    com->send("q"+toN.number(ui->cbox_selectBoard->currentIndex()));
}

void Command_interface::sendPov()
{
    int x=ui->sbox_povs->value();
    int y=ui->sbox_povd->value();
    com->sendControll(0,x,y,-1,-1);
}


void Command_interface::convertspeed()
{
    float converted_speed1 = 1;
    float converted_speed2 = 1;
    int speed = ui->cbox_valSpeed->currentIndex();
    switch (speed)
    {
    case 0:
        speed = 17;
        break;
    case 1:
        speed = 34;
        break;
    case 2:
        speed = 68;
        break;
    case 3:
        speed = 170;
        break;
    case 4:
        speed = 679;
        break;
    case 5:
        speed = 1696;
        break;
    default:
        speed = 17;
    }

    double conversion = 255.0/(2.0*speed);
    converted_speed1 = (ui->sbox_povs->value() - 127.5)/conversion;
    converted_speed2 = (ui->sbox_povd->value() - 127.5)/conversion;

    int time = ui->cbox_valTime->currentIndex();
    switch (time)
    {
    case 0:
        time = 1;
        break;
    case 1:
        time = 10;
        break;
    case 2:
        time = 20;
        break;
    case 3:
        time = 30;
        break;
    case 4:
        time = 40;
        break;
    case 5:
        time = 50;
        break;
    default:
        time = 1;
    }

    if(ui->sbox_povs->value() == 0)
    {
        ui->lineEdit->setText("- - -");
        ui->metripercorsi1->setText("- - -");
    }
    else
    {
        ui->lineEdit->setText(QString::number(converted_speed1));
        float metri = (converted_speed1/3600.0)*(time);
        ui->metripercorsi1->setText(QString::number(metri));
    }
    if(ui->sbox_povd->value() == 0)
    {
        ui->lineEdit_2->setText("- - -");
        ui->metripercorsi2->setText("- - -");
    }
    else
    {
        ui->lineEdit_2->setText(QString::number(converted_speed2));
        float metri2 = (converted_speed2/3600.0)*(time);
        ui->metripercorsi2->setText(QString::number(metri2));
    }
}



void Command_interface::reqData()
{
    ui->et_data->setText("");
    com->dataReq=1;
    com->send("z");
}

void Command_interface::offMotors()
{
    com->send("g1");
    com->send("g2");
    com->send("g3");
    com->send("g4");
 }

void Command_interface::powerOnMotor() {
   com->send("h"+toN.number(ui->cbox_joystick->currentIndex()+1));
}


void Command_interface::powerOffMotor()
{
   com->send("g"+toN.number(ui->cbox_joystick->currentIndex()+1));
}

void Command_interface::powerOnBoard() {
   com->send("o"+toN.number(ui->cbox_selectBoard->currentIndex()));
}

void Command_interface::powerOffBoard()
{
   com->send("f"+toN.number(ui->cbox_selectBoard->currentIndex()));
}

void Command_interface::sendSpeed()
{
    if(ui->cbox_valSpeed->currentIndex()!=com->nspeed)
    {
        com->send("v"+toN.number(ui->cbox_valSpeed->currentIndex()));
        com->nspeed=ui->cbox_valSpeed->currentIndex();
    }
    if(ui->cbox_valTime->currentIndex()!=com->ntime)
    {
        com->send("t"+toN.number(ui->cbox_valTime->currentIndex()));
        com->ntime=ui->cbox_valTime->currentIndex();
    }
}

//Inizia la connessione con il server, utilizzando la classe Comunication
void Command_interface::connectSerial()
{
    com->initial(SERIAL);                             //Inizializza la comunicazione
    ui->actionConnetti_via_seriale->setDisabled(true);      //Disabilit� il tasto actionConnetti (Dato che � gi� connesso)
    ui->actionConnetti_via_XBee->setDisabled(true);      //Disabilit� il tasto actionConnetti (Dato che � gi� connesso)
    disabled = false;
    ui->actionDisconnetti->setDisabled(disabled);  //Abilita il tasto actionDisconnetti
}

void Command_interface::connectXBee()
{
    com->initial(XBEE);                             //Inizializza la comunicazione
    ui->actionConnetti_via_XBee->setDisabled(true);      //Disabilit� il tasto actionConnetti (Dato che � gi� connesso)
    ui->actionConnetti_via_seriale->setDisabled(true);      //Disabilit� il tasto actionConnetti (Dato che � gi� connesso)
    disabled = false;
    ui->actionDisconnetti->setDisabled(disabled);  //Abilita il tasto actionDisconnetti
}

//Connetti il Joystick (o almeno ci prova)
void Command_interface::connectJoystick()
{
    controller->comm=com;
    controller->Init();
    controller->Check();
    controller->Conn();
}

//Disconnette dal Server
void Command_interface::disconnection()
{
    com->disc();
    controller->disc();
    disabled = true;
    ui->actionConnetti_via_seriale->setDisabled(false);
    ui->actionConnetti_via_XBee->setDisabled(false);
    ui->actionDisconnetti->setDisabled(disabled);
}

void Command_interface::startImageRq()
{
    timer->start();
}

void Command_interface::refreshImages()
{
    downloadT->run("right.png");
    downloadT->run("left.png");
    Camera->setImage("right.png");
    QPixmap image1 = Camera->getImage();
    QIcon buttonIcon1 = image1;
    ui->cam_1->setIcon(buttonIcon1);
    ui->cam_1->setIconSize(image1.rect().size());
    Camera->setImage("left.png");
    QPixmap image2 = Camera->getImage();
    QIcon buttonIcon2 = image2;
    ui->cam_2->setIcon(buttonIcon2);
    ui->cam_2->setIconSize(image2.rect().size());
    Camera->updateView();
}

void Command_interface::showSettings() {
    Settings settings;
    connect(&settings, SIGNAL(settingsChanged()), downloadT, SLOT(onSettingsChanged()));
    settings.exec();
}

void Command_interface::switchFullScreenMode() {
    QString actionText;
    if(isFullScreen()) {
        showNormal();
        actionText = "Fullscreen";
    } else {
        showFullScreen();
        actionText = "Esci da Fullscreen";
    }
    ui->actionFull_Screen->setText(actionText);
}

void Command_interface::onImageDownloadError() {
    downloadT->exit();
    timer->stop();
}

//Decostruttore della classe
Command_interface::~Command_interface()
{
    saveInterfaceSettings();
    delete ui;
}

void Command_interface::saveInterfaceSettings() {
    QSettings settings;

    settings.beginGroup("Interface");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("state", saveState());
    dLog("Saving state");
    settings.endGroup();
}

void Command_interface::loadInterfaceSettings() {
    QSettings settings;

    settings.beginGroup("Interface");
    resize(settings.value("size", QSize(1024, 768)).toSize());
    move(settings.value("pos", QPoint(0, 0)).toPoint());
    if(settings.contains("state")) {
        QByteArray state = settings.value("state", QByteArray()).toByteArray();
        restoreState(state);
    } else {
        // Default docks?
    }

    if(ui->logDockWidget->isVisible()) {
        ui->actionLog->setChecked(true);
        ui->logDockWidget->setVisible(true);
    }
    if(ui->dataDockWidget->isVisible()) {
        ui->actionData->setChecked(true);
        ui->dataDockWidget->setVisible(true);
    }

    settings.endGroup();
}
