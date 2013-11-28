#include "d_logger.h"

void XBeeManager::run()
{
    u_int08 counter=0;
    u_int16 timeout=800;
    bool_t flag_print=false;
    char data[20];
    while(1)
    {
        XBeeCOM_MainFsmInfo_t Rovm_XBeeeApiSts;
        Rovm_XBeeeApiSts=XBeeAPI_Manager();
        if(Rovm_XBeeeApiSts.ErrMainFsm==XBeeAPI_NO_ERROR)
        {
            if(Rovm_XBeeeApiSts.NewDataRead==1)
            {
                //qDebug("Incoming data");
                u_int08 RxPayload[XBeeAPI_MAX_BUFFER_SIZE];
                u_int08 Rovm_RxPayloadSize=0;
                XBeeCOM_GetRxPayloadBuffer(RxPayload,&Rovm_RxPayloadSize);
                XBeeCOM_SetRxPayloadBufferToUsed();
                counter++;
                timeout=800;
            }

            if(timeout>0)
            {
                timeout--;
            }
            else if(timeout==0)
           {
                dLog(QString().format("Counter: %d",(int)counter));
           }
        }
        else
           dLog("La libreria sbarella");
        sleep(0.015);
       }
