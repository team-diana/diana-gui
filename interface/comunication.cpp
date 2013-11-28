#include "comunication.h"

#include <QtCore>
#include <QHostAddress>


/*/
AUTHOR: Giuseppe Federico Gullo
DATE: 12/04/2012
DESCRIPTION: Classe che gestisce la comunicazione via Socket tra Interfaccia e Rover/Server
*/

//Costruttore della classe


//ATTENZIONE!!!
//NON DARE TROPPA IMPORTANZA A QUESTA PARTE, POICHE' CON L'ARRIVO DELL'INTERFACCIA RADIO QUESTA SARA' DEPRECATA


class XBeeSend: public QThread
{
 public:
    void run();
    u_int08 *data;
    u_int08 size;
};
    void XBeeSend::run()
    {
        qDebug("size: %d",size);
//         int serror=XBeeAPI_ZigBeeTxRequest(Rovm_ADDR_DEST_LSB, Rovm_ADDR_DEST_MSB,data,size,Rovm_FRAME_ID_NO_ACK);
    }

class XBeeManager: public QThread
{
 public:
    void run();
    Comunication *com;
};
    void XBeeManager::run()
    {
        /*_____________________ D I C H I A R A Z I O N I ________________________*/
// #define Rovm_MAX_RX_BUFFER_SIZE      	XBeeAPI_MAX_RX_BUFFER_SIZE
#define Rovm_STOP_XBEE_TO               ((u_int08)(2000/15)) /* 400 ms */
#define Rovm_FRAME_STOP_SIZE            ((u_int08)10)


typedef enum Rovm_FsmState_s
{
  Rovm_IDLE = 0,
  Rovm_STORAGE_RX_PAYLOAD,
  Rovm_RX_PAYLOAD_STOP_XBEE,
}Rovm_FsmState_t;

static XBeeAPI_MainFsmInfo_t Rovm_XBeeSts;
static Rovm_FsmState_t Rovm_FsmState;
// static u_int08 Rovm_RxPayloadBuffer[Rovm_MAX_RX_BUFFER_SIZE];
static u_int16 Rovm_RxPayloadSize;

// static u_int08 Rovm_StopXbeeCnt = Rovm_STOP_XBEE_TO;
static bool_t  Rovm_FlagStopXbee = false;
static bool_t  Rovm_FrameStopRead = false;
const u_int08 Rovm_FrameStop[Rovm_FRAME_STOP_SIZE] =
          {0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA};

        #define Rovm_ClearAllRxPayloadBuffer()                             \
          memset(Rovm_RxPayloadBuffer, 0, Rovm_MAX_RX_BUFFER_SIZE);


        /*_______________________________ I N I T ________________________________*/
        Rovm_XBeeSts.ErrMainFsm  = 0;
        Rovm_XBeeSts.NewDataRead = false;
        Rovm_RxPayloadSize       = 0;
//         memset(Rovm_RxPayloadBuffer, 0, Rovm_MAX_RX_BUFFER_SIZE);
        Rovm_FsmState=Rovm_IDLE;
//         while(1)
//         {
//           int FrameStopRes=0;
// //           u_int08 RxBufferTamp[Rovm_MAX_RX_BUFFER_SIZE];
// 
//           /* No error in init phase */
//           if( Rovm_ErrStsInit == XBeeAPI_NO_ERROR )
//           {
//             if( Rovm_FlagStopXbee == FALSE )
//             {
//                 /* Call the manager for protocol ZigBee */
// //                 Rovm_XBeeSts = XBeeAPI_Manager();
// 
//                 /* Chek on XBee library status */
//                 if( Rovm_XBeeSts.ErrMainFsm == XBeeAPI_NO_ERROR )
//                 {
//                   if( Rovm_XBeeSts.NewDataRead == TRUE )
//                   {
//                     if( Rovm_FrameStopRead == FALSE )
//                     {
//                       /* Set the state for block the XBeeAPI library FSM */
//                        Rovm_FsmState = Rovm_RX_PAYLOAD_STOP_XBEE;
//                     }
//                     else
//                     {
//                       /* Set the state for read and storage the rx payload */
//                       Rovm_FsmState = Rovm_STORAGE_RX_PAYLOAD;
//                     }
//                   }
//                 }
//                 else
//                 {
//                   /* Set error */
//                 }
//               }
// 
//             /* Command FSM */
//             switch(Rovm_FsmState)
//             {
//               case Rovm_IDLE:
//               default:
// 
//                 if( Rovm_FlagStopXbee == TRUE )
//                 {
// //                   if( Rovm_StopXbeeCnt > 0 )
//                   {
// //                     Rovm_StopXbeeCnt--;
//                   }
//                   else
//                   {
//                     Rovm_StopXbeeCnt = Rovm_STOP_XBEE_TO;
//                     Rovm_FlagStopXbee = FALSE;
//                   }
//                 }
//                 break;
// 
//               case Rovm_RX_PAYLOAD_STOP_XBEE:
// 
//                 /* Read the rx payload and its size */
// //                 Rovm_RxPayloadSize = XBeeAPI_GetRxPayloadBuffer(Rovm_RxPayloadBuffer);
//                 u_int08 idx;
// 
//                 for(idx=0; idx < Rovm_FRAME_STOP_SIZE; idx++)
//                 {
//                     FrameStopRes = 0;
//                     if(Rovm_RxPayloadBuffer[idx] != Rovm_FrameStop[idx])
//                     {
//                         FrameStopRes = 1;
//                         break;
//                     }
//                 }
// 
// 
//                 if( FrameStopRes == 0 )
//                 {
//                   Rovm_FlagStopXbee = TRUE;
//                   Rovm_FrameStopRead = TRUE;
//                   memset(Rovm_RxPayloadBuffer, 0, Rovm_MAX_RX_BUFFER_SIZE);
//                   Rovm_RxPayloadSize = 0;
// 
//                 }
//                 /* Return the IDLE state */
//                 Rovm_FsmState = Rovm_IDLE;
//                 break;
// 
//              case Rovm_STORAGE_RX_PAYLOAD:
// 
//                /* Clear flag for stop frame read */
//                Rovm_FrameStopRead = FALSE;
// 
//                /* Read the rx payload and its size */
// //                Rovm_RxPayloadSize = XBeeAPI_GetRxPayloadBuffer(Rovm_RxPayloadBuffer+Rovm_RxPayloadSize);
// 
//                qDebug("Incoming data: %d byte",Rovm_RxPayloadSize);
//                //qDebug("%s",Rovm_RxPayloadBuffer);
//                memset(Rovm_RxPayloadBuffer,0,Rovm_RxPayloadSize);
//                Rovm_RxPayloadSize=0;
//                Rovm_FsmState=Rovm_IDLE;
//                 break;
//             }
//           }
//           sleep(0.015);
//         }
    }



//divido la stringa str="ids;idd;dato;" in arrivo
void Comunication::dividi_str(char *stringa)
{

     char *data;
         int ids,idd;
         qDebug("TEST 1");
     ids = atoi(strtok(stringa, ";"));
     idd = atoi((strtok(NULL, ";")));
     data= strtok(NULL, ";");
     qDebug("TEST 2");
     //funziona se faccio if(sscanf(stringa,"%d;%d;%s;",&ids,&idd,data)==3) insert_data...???
     insert_data(ids,idd,data);
     qDebug("TEST 3");
 }

Comunication::Comunication(QObject* parent) 
: QObject(parent)
{
    qDebug("Initialization...");
    cmds = new Commands();              //inizializza la classe Commands
    ntime=nspeed=-1;
    extReq=dataReq=k=0;
    onSettingsChanged();
    ///SERIAL///
}

int r;
void Comunication::initial(int connection_type)
{
    log->append("Connessione in corso...");
    this->connection_type=connection_type;
    if(connection_type==SERIAL)
    {
        log->append(QString("Connesione a %0:%1 ...").arg(tcpAddr).arg(tcpPort));
        tcpSocket = new QTcpSocket(this);   //Crea un nuovo socket TCP (Wikipedia docet)
        connect(tcpSocket, SIGNAL(connected()),this, SLOT(start()));//chiama la funzione start() quando la connessione è pronta
        connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readSerial()));
        QHostAddress addr(tcpAddr);
        tcpSocket->connectToHost(addr, tcpPort); //Avvia, o almeno ci prova, la connessione sulla porta 80
    }
    else if(connection_type==XBEE)
    {
        QLibrary library("libXBeeAPI_V5.dll");
        library.load();
       XBeeManager *xbm=new XBeeManager();
//       error = XBeeAPI_Init(6,115200);

       switch(error)
       {
           case(XBeeAPI_NO_ERROR):
               log->append("Connessione stabilita");
               xbm->start();
               break;
          case(XBeeAPI_NO_OPEN_SERIAL_COMM):
               log->append("Impossibile aprire la porta seriale N");
               break;
          case(XBeeAPI_NO_SET_BAUD_RATE):
               log->append("Impossibile settare il baudrate selezionato");
               break;
          default:
            log->append("Impossibile stabilire la connessione: errore sconosciuto");
        }
    }
    else
        log->append("Impossibile stabilire la connessione: protocollo sconosciuto");
}

void Comunication::startManager()
{
    log->append("Avvio thread esterno");
    timer->start();
}

void Comunication::start()
{
    qDebug("CONNECTED!");
    send("");
}

void Comunication::manager()
{
    //qDebug("Manager called");
//     XBeeAPI_Manager();
}

int Comunication::saveLog(QString log)
{
    FILE *logfile=fopen(LOGFILE,"a");
    if(!logfile)
        return 1;
    fprintf(logfile,"%s\n",log.toStdString().c_str());
    fclose(logfile);
}

///////////////////////PARTE DI INVIO/////////////////////////////////////////

QString Comunication::sendSerial(QByteArray data)
{
    tcpSocket->write(data);
    return "niente";
}

void Comunication::readSerial()
{
    QString data;
    int i,data_size;
    char tmp[120];
    data=tcpSocket->readAll();
    console->setText(data);
    qDebug("Sizeof payload: %d",data.length());
    QStringList data_list=data.split("\n");
    data_size=data_list.length();
    for(i=1;i<data_size;i++)
    {
        if(data_list.at(i).count(";")==3)
        {
        strcpy(tmp,data_list.at(i).toStdString().c_str());
        qDebug("data: %s",tmp);
        dividi_str(tmp);
        }
    }
}


QString Comunication::sendXBee(QByteArray data,int size)
{
    const u_int08 test[]={1,2,3,4,5};
    qDebug("Invio tramite XBEE");
    saveLog(QString(data));
    QString response="ERRORE: errore sconosciuto";
    qDebug("Test 4");
    XBeeSend  *xsnd=new XBeeSend();
    xsnd->data=(u_int08*)malloc(size);
    memcpy(xsnd->data,data.constData(),size);
    qDebug("Test 4.1");
    xsnd->size=size;
    qDebug("Test 4.2");
    xsnd->start();
    qDebug("Test 4.5");
    int serror=XBeeAPI_NO_ERROR;
    switch(serror)
    {
        case(XBeeAPI_NO_ERROR):
        qDebug("Test 5");
        //log->append("Comando: "+data);
        response="Comando inviato con successo";
        break;
        case(XBeeAPI_TX_BUFFER_IS_FULL):
            response="ERRORE: il buffer di trasmissione è pieno";
            break;
        case(XBeeAPI_FSM_IN_ERROR):
            response="ERRORE: la macchina a stati sbarella";
            break;
        case(XBeeAPI_MODEM_BUSY):
            response="ERRORE: il modem è impegnato";
            break;
    }
    qDebug("Test 5");
    return response;
}

//Invia un comando dal joystick
int Comunication::sendControll(int c,int ydx,int ysx,int speed,int time)
{

    if(1)    //Controlla che la connessione sia attiva
    {
        log->append("Nessuna connessione attiva");
        return 0;
    }

    QByteArray cmd;
    QString num;
    if(c)
    {
        ydx=cmds->getControllY(ydx);
        valX->setValue(ydx);
        ysx=cmds->getControllY(ysx);
        valY->setValue(ysx);
    }

   cmd.append('p');
   cmd.append(';');
   cmd.append(num.number(ysx));
   cmd.append(';');
   cmd.append(num.number(ydx));
   cmd.append(';');
   if(connection_type==XBEE)
        sendXBee(cmd,cmd.size());
   else if(connection_type==SERIAL)
       sendSerial(cmd);
}

//Invia un comando
int Comunication::send(QString s)
{
    int c;
    char data1[2];
    QByteArray data;
    if(s!="")
    {
        if(s[0]=='x')
        {
            char data2[20];
            cmds->ext(s,data2);
            for(i=0;i<20;i++)
                data.append(data2[i]);
            //sendXBee(data,data.size());
            //sendSerial(data);
            if(connection_type==XBEE)
                log->append(sendXBee(data,data.size()));
            else
                sendSerial(data);
            extReq=1;
        }
        else
        {
        c=cmds->getCommand_from_shell(s,data1);
        if(!c)
            return 0;
        data.append(data1[0]);
        data.append(';');
        if(data[0]!='s' && data[0]!='z')
            data.append(data1[1]);
        data.append(';');
        data.append(';');
        qDebug("Test 1");
        if(connection_type==SERIAL)
            sendSerial(data);
        else if(connection_type==XBEE)
            log->append(sendXBee(data,data.size()));
      }

    }
    else
         log->append("Connesso al dispositivo remoto");
    return 1;
}

///////////////////////PARTE DI RICEZIONE/////////////////////////////////////////



///////////////////////////////////CORRADO////////////////77

//cerco ids (e idd tramite la funzione "ricerca") lette da "dividi_str" e faccio verifiche
void Comunication::insert_data(int ids, int idd, char *data)
{
    int i,n;
    qDebug("TEST 1.1");

    if(strlen(data)<=32 && strlen(data)>0)
    {
        if(ids==0)
            if(idd>=1 && idd<=17)
            {
                qDebug("TEST 1.2");
                i=0;
                n=17;
                qDebug("TEST 1.3");
                ricerca(i,n,idd,data);
                qDebug("TEST 1.4");
                return;
            }

        if(ids==1)
        {
            if(idd>=1 && idd<=32)
            {
                i=17;
                n=49;
                ricerca(i,n,idd,data); return;
            }

            if(idd>=33 && idd<=44)
            {
                i=49;
                n=61;
                ricerca(i,n,idd,data); return;
            }
        }

        if(ids==2)
            if(idd>=1 && idd<=28)
            {
                i=61;
                n=89;
                ricerca(i,n,idd,data); return;
            }

        if(ids==3)
            if(idd>=1 && idd <=8)
            {
                i=89;
                n=97;
                ricerca(i,n,idd,data); return;
            }
    }

}

//cerco idd, faccio verifiche di allarmi e stampo sulla Qtable (evidenziando se ci sono allarmi)
void Comunication::ricerca(int i, int n, int idd, char *data)
{
    qDebug("Ricerca...");
    int z;
    for(z=i; z<n; z++)
        if(table[z].idd==idd)
        {
            qDebug("Stampa normalmente (se sempre stampa)");
            QTableWidgetItem *value=new QTableWidgetItem(data);
            tab_data->setItem(table[z].row, table[z].column, value);
            break;
        }
}

//Riempio la struttura dati di tipo struct Tabella con i valori di idd, x e y noti (dal file exel di Mattia)!
void Comunication::build_table()
{
    int i,k;
    for(i=0, k=1; i<17; i++, k++)
    {
        table[i].ids=0;
        table[i].idd=k;
        table[i].column=7;
        table[i].row=k+10;
    }

    for(i=17, k=1; i<49; i++, k++)
    {
        table[i].ids=1;
        table[i].idd=k;
        table[i].column=1;
        table[i].row=k-1;
    }
    for(i=49, k=33; i<61; i++, k++)
    {
        table[i].ids=1;
        table[i].idd=k;
        table[i].column=3;
        table[i].row=k-33;
    }

    for(i=61, k=1; i<89; i++, k++)
    {
        table[i].ids=2;
        table[i].idd=k;
        table[i].column=5;
        table[i].row=k-1;
    }

    for(i=89, k=1; i<97; i++, k++)
    {
        table[i].ids=3;
        table[i].idd=k;
        table[i].column=7;
        table[i].row=k-1;
    }
}

///////////////////////////////////////////

//Disconnettiti dal server
void Comunication::disc()
{
    log->append("Disconnessione in corso...");
    tcpSocket->abort();
    log->append("Disconnesso dal server");
}

void Comunication::onSettingsChanged()
{
    QSettings settings;
    tcpAddr = settings.value("tcpAddr", "192.168.50.1").toString();
    tcpPort = settings.value("tcpPort", 8080).toInt();
}

//Decostruttore della classe
Comunication::~Comunication()
{
    delete cmds;
}
