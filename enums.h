#pragma once

#define RESET_FLAGS 0
enum // PACKAGE_ INFORMATIONS
{
    NOTHING_MISSED_H    = 0,
    MISSED_DATA_AV_H    = 1,
    VIDEO_SIZE_H        = 2,
    VIDEO_DATA_H        = 3,
    ERROR_H             = 4
}/*HEADER = NOTHING_MISSED_H*/;


enum  // ACKTYPES
{
    ACKType_VS   = 0,
    ACKType_VID  = 1,
    ACKType_END  = 2,
    ACKType_NONE = 3
};

enum // ACK
{
    ACK_UNSUCCESS  = 0,
    ACK_SUCCESS    = 1,
    ACK_VID_COMP   = 2,
    ACK_VS_END     = 3,
    ACK_END_SIGNAL = 3,
    ACK_NONE       = 4
};

enum  // FLIGHT STATUS
{
    STAT_WAITING     = 0,
    STAT_RISING      = 1,
    STAT_SEPERATING  = 2,
    STAT_FLIGHTFALL  = 3,
    STAT_PAYFALL     = 4,
    STAT_FIXEDALT    = 5,
    STAT_RESCUE      = 6
};
enum // VIDEO STATUS
{
    TRANSFER_NOT_COMPLETED = 0 ,
    TRANSFER_COMPLETED     = 1
};

enum  // Frame Headers
{
    DataFrameHeader = 0xBB,
    ACKFrameHeader  = 0xCC
};

enum // GCS Package Size info
{
    GCS_Pckt_Normal = 2,
    GCS_Pcket_VIDEO = 104,
    MAX_GCS_PACKET  = 104
};


enum
{
    BMP_NOT_READED  = 0,
    BMP_READED      = 1
};


enum
{
    IMU_NOT_READED  = 0,
    IMU_READED      = 1
};

enum
{
    GPS_NOT_READED  = 0,
    GPS_READED      = 1
};

enum
{
    SENSORS_NOT_READY   = 0,
    SENSORS_READY       = 1
};