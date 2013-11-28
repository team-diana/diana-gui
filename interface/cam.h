#ifndef CAM_H
#define CAM_H


#include <QObject>
#include <QLabel>
#include <QEvent>
#include <QtEvents>
#include <QString>
#include <QPixmap>
#include <QProcess>
#include <comunication.h>
#include <QLabel>
#include <QProcess>
#include <QThread>

#include <QtMultimedia/QMediaPlayer>

#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia/QMediaPlaylist>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QGraphicsView>

class DownloadThread: public QThread
{
    Q_OBJECT
public:
    DownloadThread();
    void run(QString nomefile);

public slots:
    // Aggiorna configurazione.
    void onSettingsChanged();

signals:
    void downloadFinished();
    void processError();

private:
    bool downloading;
    // Indirizzo ip del server tftp.
    QString ipAddr;
    // Cartella dove verranno salvate le immagini.
    QString imageDir;

};

class Cam : public QObject
{
    Q_OBJECT

    public:
        Cam( QGraphicsView* view , QObject* parent = NULL);   //Changed
        QPixmap getImage();
        void setImage(QString index);


    public slots:
        void changeCam(int index);
        void updateView();

    private:
        QLabel* camLabel;
        QPixmap image;
        int selectedImageIndex;

        /*New code by Alessandro Quaranta*/
        QVideoWidget* camWidget;
        QMediaPlaylist* playlist;
        QMediaPlayer* player;

        QGraphicsScene* scene;
        QGraphicsVideoItem* item;

};
#endif // CAM_H



