/*
AUTHOR: Davide Pala
DATE: 11/04/2012
DESCRIPTION: Classe che gestisce la camera
*/

#include "cam.h"

#include "d_logger.h"

#include <QProcess>
#include <QSettings>
#include <QDir>
#include <QBitmap>

#include <stdio.h>

using namespace std;

DownloadThread::DownloadThread() {
    onSettingsChanged();
}

void DownloadThread::run(QString nomefile)
{
    QString command = "tftp -i %1 GET %2 %3/%2";
    command = command.arg(ipAddr, nomefile, imageDir);
    QProcess prc;
    prc.start(command);
    prc.waitForFinished(5000);
    if(prc.exitCode() != 0) {
        QString msg = "Unable to download image \"%1\" at %2";
        msg = msg.arg(nomefile, ipAddr);
        dLog(prc.readAll());
    } else if(prc.error() == QProcess::FailedToStart) {
        QString msg = "Unable to start tftp. Maybe the executable is not present in the working directory?";
        dLog(msg);
        emit processError();
    } else {
        emit downloadFinished();
    }
}

void DownloadThread::onSettingsChanged()
{
    // Carica i parametri (indirizzo ip, cartella) da QSettings
    QSettings settings;
    ipAddr = settings.value("tftpAddr", "192.168.50.1").toString();
    imageDir = settings.value("tftpImagesDir", "c:\\immaginirover\\").toString();
}


//costruttore
Cam::Cam(QGraphicsView* view, QObject* parent) :
QObject(parent)

{
    camWidget = new QVideoWidget();
    player = new QMediaPlayer;
    playlist=new QMediaPlaylist(player);
    //playlist->addMedia(QUrl::fromLocalFile("/home/alessandro/Video/Campeggio2013.mp4"));    //Cam1, Playlist Index 1
    //playlist->addMedia(QUrl::fromLocalFile("/home/alessandro/Video/prova.mp4"));    //Cam2, Playlist Index 2
    playlist->addMedia(QUrl("http://rover.teamdiana.org:8182/stream?topic=/camera/image_raw"));    //Cam1, Playlist Index 1
    //playlist->addMedia(QUrl("http://"));    //Cam3, Playlist Index 3
    //playlist->addMedia(QUrl("http://"));    //Cam3D, Playlist Index 4

    selectedImageIndex=0;
    player->setPlaylist(playlist);
    playlist->setCurrentIndex(selectedImageIndex);

    item = new QGraphicsVideoItem;
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);

    player->setVideoOutput(item);
    view->scene()->addItem(item);
    view->show();
    player->play();     //libqt5




}



QPixmap Cam::getImage()
{
    return image;
}

void Cam::setImage(QString nome)
{
    QSettings settings;
    QString imageDir = settings.value("tftpImagesDir", "").toString();
    QString path = imageDir + "/" + nome;

    if (!image.load( path )) {
        dLog("Failed loading images", SERIOUS_ERROR);
    }
}

void Cam::changeCam(int index)
{
    selectedImageIndex = index;
    updateView();
}

void Cam::updateView() {
    /*QString name;
    switch(selectedImageIndex+1)
    {
    case 1:
        name = "right.png";
        break;
    case 2:
        name = "left.png";
        break;
    case 3:
        name = "center.png";
        break;
    case 4:
        name = "3d.png";
        break;
    default:
        name = "right.png";
    }

    setImage(name);
    QPixmap image = getImage();

    camLabel->setPixmap(image);
    camLabel->setMask(image.mask());
    camLabel->show();*/

    player->stop();
    playlist->setCurrentIndex(selectedImageIndex);
    player->play();
}
