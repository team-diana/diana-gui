#include <QtNetwork/QTcpSocket>
#include <QTextEdit>
#include <QTableWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QTimer>
#include <stdint.h>

#ifndef COMUNICATION_H
#define COMUNICATION_H

#define Rovm_ADDR_DEST_LSB								((u_int32)0x40665BD0)
#define Rovm_ADDR_DEST_MSB								((u_int32)0x0013A200)
#define Rovm_FRAME_ID_NO_ACK							((u_int08)0)
#define Rovm_MAX_BUFFER_SIZE      				XBeeAPI_MAX_BUFFER_SIZE

/*______________ Codifica comandi principali ______________*/
#define Rovm_IDLE_C							          ((char)NULL)
#define Rovm_EXIT_C												((char)'x')
#define Rovm_SEND_PAYLOAD_C								((char)'s')

#define LOGFILE "log.txt"
#define XBEE 1
#define SERIAL 2

class Comunication : public QObject
{
Q_OBJECT
public:

    typedef enum Rovm_FsmState_s
    {
      Rovm_IDLE = 0,
      Rovm_EXIT,
      Rovm_SEND_PAYLOAD,
      Rovm_STORAGE_RX_PAYLOAD,
      Rovm_PRINT_ERROR,
    }Rovm_FsmState_t;

    Comunication(QObject* parent = NULL);
    ~Comunication();
    void initial(int connection_type);
    int send(QString s);
    int sendControll(int c,int x,int y,int speed,int time);
    int saveLog(QString log);
    void build_table();
       // void stampa_rosso(int i, char *data);
        void insert_data(int ids, int idd, char *data);
        void leggi_dati();
        void ricerca(int i, int n, int idd, char *data);
        void dividi_str(char *stringa);
    QString sendXBee(QByteArray data,int size);
    QString sendSerial(QByteArray data);

    void disc();

public slots:
    void start();
    void startManager();
    void readSerial();



public:
    struct Tabella
      {
          int ids, idd, row, column;
      };
       struct Tabella table[97];
    QTcpSocket *tcpSocket;
    QThread* thread;
    QTextEdit *log;
    QTextEdit *console;
    QTableWidget *tab_data;
    QComboBox *valSpeed;
    QComboBox *valTime;
    QSpinBox *valX;
    QSpinBox *valY;
    QTimer *timer;
    int nspeed,ntime,k,j,i;
    int cmd_sx,cmd_dx;
    int connection_type;
   // QList<QByteArray> tot_data;
    QStringList tot_data;



    int error;
    int extReq,dataReq;
    uint8_t port;
    uint32_t baudrate;


public slots:
    void manager();
    void onSettingsChanged();

private:
    QString tcpAddr;
    int tcpPort;

};

#endif // COMUNICATION_H
