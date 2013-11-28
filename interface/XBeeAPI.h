/******************************************************************************/
/*F_NAME:          XbeeAPI.h                                                  */
/*F_PURPOSE:       Public interface for library of the module Xbee with API   */
/*                 firmware. The library must be used with AP = 1 and for     */
/*                 network ZIGBEE. The ZS, ZigBee Stack profile, must         */
/*                 be set to 1. This library will test only for Xstick and    */
/*                 for Xbee PROS2B. The firmware used are: 21A0 and 23A0.     */
/*F_CREATED_BY:    Carmine Celozzi                                            */
/*F_CREATION_DATE: OCT 2012                                                   */
/******************************************************************************/
/******************************************************************************/
/* This firmware is wrote according to the product manual for                 */
/* XBee/XBee-PRO ZB RF modules. This document can be downloaded to address    */
/* http://ftp1.digi.com/support/documentation/90000976_L.pdf                  */
/******************************************************************************/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
|-----------------------------------------------------------------------------
|    CC        Carmine Celozzi					 none
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
|  Date       Ver   Author  Description
|-----------------------------------------------------------------------------
| 14/10/12   1.0.0   CC     Development first version of library for Xbee module
|                           with API firmware.
|-----------------------------------------------------------------------------
*/

/*______ P R O T E C T I O N - H E A D E R ___________________________________*/

#ifndef XBEE_API_H
#define XBEE_API_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "TypeLib_CC.h"

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*_______________ Define for API identifer used with API firmware ____________*/
/* AT Command */
#define XBEE_API_AT_COMMAND															((u_int08)0x08)
/* AT Command - Queue Parameter Value */
#define XBEE_API_AT_COMMAND_QPV  												((u_int08)0x09)
/* ZigBee Transmit Request */
#define XBEE_API_ZBEE_TX_REQ														((u_int08)0x10)
/* Explicit Addressing ZigBee Command Frame */
#define XBEE_API_ZBEE_COMM_FRAME_EXPLICIT_ADDR					((u_int08)0x11)
/* Remote AT Command Request */
#define XBEE_API_REMOTE_AT_COMMAND_REQ									((u_int08)0x17)
/* Create Source Route */
#define XBEE_API_CREATE_SOURCE_ROUTE										((u_int08)0x21)
/* AT Command Response */
#define XBEE_API_AT_COMMAND_RESP										    ((u_int08)0x88)
/* Modem Status */
#define XBEE_API_MODEM_STATUS                           ((u_int08)0x8A)
/* ZigBee Transmit Status */
#define XBEE_API_ZBEE_TX_STATUS													((u_int08)0x8B)
/* ZigBee Receive Packet (AO=0) */
#define XBEE_API_ZBEE_RX_PACKET                         ((u_int08)0x90)
/* ZigBee Explicit Rx Indicator (AO=1) */
#define XBEE_API_ZBEE_EXPLICIT_RX_INDICATOR							((u_int08)0x91)
/* ZigBee IO Data Sample Rx Indicator */
#define XBEE_API_ZBEE_IO_DATA_SAMPLE_RX									((u_int08)0x92)
/* Xbee Sensor Read Indicator (AO=0) */
#define XBEE_API_XBEE_SENSOR_READ												((u_int08)0x94)
/* Node Identification Indicator (AO=0) */
#define XBEE_API_NODE_IDENT_INDICATOR            				((u_int08)0x95)
/* Remote AT Command Response */
#define XBEE_API_REMOTE_AT_COMMAND_RESP									((u_int08)0x97)
/* Over-the-Air Firmware Update Status */
#define XBEE_API_AIR_FIRMWARE_UPDATE_STS								((u_int08)0xA0)
/* Route Record Indicator */
#define XBEE_API_ROUTE_RECORD_INDICATOR									((u_int08)0xA1)
/* Many-to-One Route Request Indicator */
#define XBEE_API_MANY_TO_ONE_ROUTE_REQ									((u_int08)0xA3)

/*____________________ Section for communication protocol ____________________*/
#define XBeeAPI_MAX_TX_BUFFER_SIZE								((u_int08)100)
#define XBeeAPI_MAX_RX_BUFFER_SIZE								((u_int16)1600)

/*___________________________ Section for error code _________________________*/
/* Returned by all routines */
#define XBeeAPI_NO_ERROR									((u_int08)0)
/* Returned by XBeeAPI_Init routine */
#define XBeeAPI_NO_OPEN_SERIAL_COMM				((u_int08)1)
#define XBeeAPI_NO_SET_BAUD_RATE          ((u_int08)2)
/* Returned by XBeeAPI_Manager routine */
#define XBeeAPI_SERIAL_NO_RX							((u_int08)3)
#define XBeeAPI_SERIAL_NO_TX							((u_int08)4)
/* Returned by XBeeAPI_ATCommand and XBeeAPI_ZigBeeTxRequest routines */
#define XBeeAPI_TX_BUFFER_IS_FULL					((u_int08)16)
#define XBeeAPI_MODEM_BUSY  							((u_int08)17)
#define XBeeAPI_FSM_IN_ERROR							((u_int08)18)


/*________________________ SECTION FOR FSM __________________________*/
/* Time scheduling for FSM handler */
#define XbeeAPI_FSM_SCHEDULING_TIME           ((u_int08)15) /* 15 ms */
/* Setting for RX_CHECK timeout */
#define XbeeAPI_RX_CHECK_TIMEOUT							((u_int08)60) /* 60 ms */
/* Setting for MAIN_ERROR timeout */
#define XbeeAPI_FSM_ERROR_TIMEOUT							((u_int08)250) /* 250 ms */


/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/* Type returned by XBeeAPI_Manager routine */
typedef struct XBeeAPI_MainFsmInfo_s
{
  u_int08 ErrMainFsm;
  bool_t  NewDataRead;
}XBeeAPI_MainFsmInfo_t;


/*______ E X T E R N - G L O B A L - D A T A _________________________________*/

/* TODO - da rimettere statica */
//extern u_int08 XbeeAPI_RxPayloadBuffer[XBeeAPI_MAX_RX_BUFFER_SIZE];

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*----------------------------------------------------------------------------*/
/* Name: XbeeAPI_Init                                                         */
/* Role: Initialize the XbeeAPI library                                       */
/*                                                                            */
/* Interface: IN - PortNmb: VCP number where is inserted the Xstick           */
/*            IN - BaudRate: Standard baud rate for serial communication.     */
/*            OUT - ErrStsLib: XBeeAPI_NO_ERROR, XBeeAPI_NO_OPEN_SERIAL_COMM, */
/*                             XBeeAPI_NO_SET_BAUD_RATE                       */
/*                                                                            */
/* Pre-condition: VCP driver installation in a port USB                       */
/* Constraints:   - Must be call for use the XbeeAPI library                  */
/*                - If baud rate parameter isn't 9600 (default value), must   */
/*                  configure the Xstick (by X-CTU tool) with new setting     */
/* Created by:    Carmine Celozzi                                             */
/* Creation date: OCT 14 2012                                                 */
/*----------------------------------------------------------------------------*/
extern "C"
{
  u_int08 XBeeAPI_Init(u_int08 PortNmb, unsigned long BaudRate);
}

/*----------------------------------------------------------------------------*/
/* Name: XBeeAPI_StopZigBeeComm                                               */
/* Role: Stop the ZigBee communication and then the serial COM communication  */
/*                                                                            */
/* Interface: IN - none                                                       */
/*            OUT - none                                                      */
/*                                                                            */
/* Pre-condition: none                                                        */
/* Constraints: none                                                          */
/* Created by:    Carmine Celozzi                                             */
/* Creation date: NOV 08 2012                                                 */
/*----------------------------------------------------------------------------*/
extern "C"
{
  void XBeeAPI_StopZigBeeComm(void);
}

/*----------------------------------------------------------------------------*/
/* Name: XBeeAPI_Manager                                                      */
/* Role: Routine that manage the main FSM for protocol of communication.      */
/*       The FSM states are: - MAIN_IDLE --> Start state                      */
/*       - MAIN_RX_TX_CHECK --> It's the main state. Check the tx pending     */
/*         requests and manage their sending. Manage the timeout for rx       */
/*         frames management.                                                 */
/*       - MAIN_RX --> Manage the reception of ZigBee frame.                  */
/*       - MAIN_TX --> Manage the sending ZigBee frame.                       */
/*       - MAIN_ERROR --> Manage the error presence and their storage.        */
/*                                                                            */
/* Interface: IN - none                                                       */
/*            OUT - XbeeAPI_MainFsmInfo: has two fields                       */
/*            - ErrMainFsm: return the communication error managed by FSM.    */
/*              For now (TODO): XBeeAPI_NO_ERROR, XBeeAPI_SERIAL_NO_RX,       */
/*                              XBeeAPI_SERIAL_NO_TX.                         */
/*            - NewDataRead: a flag that notifies the presence of new data    */
/*              read. This flag remain to TRUE until a new valid data occur.  */
/*              Just read this flag, must read the payload by routine         */
/*              XBeeAPI_GetRxPayloadBuffer and clear the flag and buffer by   */
/*              routine XBeeAPI_SetRxPayloadBufferToUsed. If a new data occur */
/*              the current payload will be lost (TODO - must be changed).    */
/*                                                                            */
/* Pre-condition: Must be call the routine XBeeAPI_Init                       */
/* Constraints:   - Must be call for use the XbeeAPI library                  */
/*                - Can be scheduled with a time ranging from 5 to 20 ms      */
/* Created by:    Carmine Celozzi                                             */
/* Creation date: OCT 18 2012                                                 */
/*----------------------------------------------------------------------------*/
extern "C"
{
  XBeeAPI_MainFsmInfo_t XBeeAPI_Manager(void);
}

/*----------------------------------------------------------------------------*/
/* Name: XBeeAPI_GetRxPayloadBuffer                                           */
/* Role: Return the rx payload by a buffer and own size                       */
/*                                                                            */
/* Interface: IN/OUT - *Payload: pointer to rx payload buffer                 */
/*            IN/OUT - *PayloadSize: rx payload size                          */
/*                                                                            */
/* Pre-condition: Should be called only after a notify of new data read by    */
/*                XBeeAPI_Manager routine.                                    */
/* Constraints:   Must be called before of XBeeAPI_SetRxPayloadBufferToUsed   */
/*                routine for because after the buffer will be deleted.       */
/* Created by:    Carmine Celozzi                                             */
/* Creation date: NOV 04 2012                                                 */
/*----------------------------------------------------------------------------*/
extern "C"
{
  u_int16 XBeeAPI_GetRxPayloadBuffer(u_int08 *RxPayload);
}


extern "C"
{
  void XBeeAPI_DisableRxState(void);
}

/*----------------------------------------------------------------------------*/
/* Name: XBeeAPI_ATCommand                                                    */
/* Role: Send an AT command by a frame with ID 0x08. If FSM is busy, request  */
/*       a pending sending that will be processed at the right time by FSM.   */
/*       For details about AT command frame see the product datasheet.        */
/*                                                                            */
/* Interface: IN - SizeParamValue: Parameter value size. If the parameter     */
/*                 must be read this value must be 0 and the *ParamValue will */
/*                 be ignored. If must be written must be the prameter size   */
/*                 that will be written.                                      */
/*            IN - FrameID: If set to zero, the modem will not send an ack    */
/*                 about the frame status. If different to zero, will be sent */
/*                 an ack and its will be recognized along with other rx data */
/*                 by the same frame ID.                                      */
/*            IN/OUT - *ATCommand: pointer to two characters for AT command   */
/*            IN/OUT - *ParlamValue: Parameter value. Will be ignored if       */
/*                     SizeParamValue is set to zero.                         */
/*            OUT - ErrSts: XBeeAPI_NO_ERROR, XBeeAPI_TX_BUFFER_IS_FULL,      */
/*                  XBeeAPI_FSM_IN_ERROR, XBeeAPI_MODEM_BUSY                  */
/*                                                                            */
/* Pre-condition: none                                                        */
/* Constraints:   For know if frame was really sent should be monitored       */
/*                the ErrMainFsm field returned by XBeeAPI_Manager routine.   */
/* Created by:    Carmine Celozzi                                             */
/* Creation date: OCT 18 2012                                                 */
/*----------------------------------------------------------------------------*/
extern "C"
{
  u_int08 XBeeAPI_ATCommand(char    *ATCommand,     u_int08 *ParamValue,
                            u_int08 SizeParamValue, u_int08 FrameID);
}

/*----------------------------------------------------------------------------*/
/* Name: XBeeAPI_ZigBeeTxRequest                                              */
/* Role: Send a ZigBee data packet by a frame with ID 0x10. This API use the  */
/*       MAC address to 64 bit for destination node because it's born for a   */
/*       static configuration of WPAN. For details about ZigBeeTxRequest      */
/*       frame see the product datasheet.                                     */
/*                                                                            */
/* Interface: IN - MacAddrLSB: The last 4 bytes of destination MAC address.   */
/*                 The LSB of this parameter is the LSB of MAC address.       */
/*            IN - MacAddrMSB: The first 4 bytes of destination MAC address.  */
/*                 The MSB of this parameter is the MSB of MAC address.       */
/*            IN - SizePayload: Payload size.                                 */
/*            IN - FrameID: If set to zero, the modem will not send an ack    */
/*                 about the frame status. If different to zero, will be sent */
/*                 an ack and its will be recognized along with other rx data */
/*                 by the same frame ID.                                      */
/*            IN/OUT - Payload: pointer to payload buffer.                    */
/*            OUT - ErrSts: XBeeAPI_NO_ERROR, XBeeAPI_TX_BUFFER_IS_FULL,      */
/*                  XBeeAPI_FSM_IN_ERROR, XBeeAPI_MODEM_BUSY                  */
/*                                                                            */
/* Pre-condition: none                                                        */
/* Constraints:   For know if frame was really sent should be monitored       */
/*                the ErrMainFsm field returned by XBeeAPI_Manager routine.   */
/* Created by:    Carmine Celozzi                                             */
/* Creation date: NOV 03 2012                                                 */
/*----------------------------------------------------------------------------*/
extern "C"
{
  u_int08 XBeeAPI_ZigBeeTxRequest(u_int32 MacAddrLSB, u_int32 MacAddrMSB, u_int08 *Payload,
                                  u_int08 SizePayload, u_int08 FrameID);
}


#endif /* end XBEE_API_H */

/*______ E N D _____ (XbeeAPI.h) _____________________________________________*/

