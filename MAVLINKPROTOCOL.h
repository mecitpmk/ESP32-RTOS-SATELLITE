#pragma once
#include <Arduino.h>
#include <string.h>
#include "enums.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"


// #include <WiFiUdp.h>
// #include "SENSORS.h"
// #include "STORAGE.h"
// #include <ESP32Servo.h>

#define MAX_TELEMETRY_LENGTH 2 // 2kb is probably too much but anyways. I don't wanna fail because of this in tests


class OLDDATACLASS
{
    public:
        // Bu kısımda oluşturulmuş array'ların amacı, Okunan değeri direkt olarak array'a yazmak.
        // Array'ın boyutunu 5 yaptım, normalde 1 veya 2 bile olabilirdi sıkıntı yok.
        float altitude[5];
        float pressure[5];
        float temperature[5];
        float turn_number[5];
        float pitch[5];
        float yaw[5];
        float roll[5];

        float* altPtr = &altitude[1]; // En son arrayın kaçıncı indexinde kaldığımızı bulmaya yarayacak.
        float* presPtr;
        float* tempPtr ;
        float* turnPtr ;
        float* pitchPtr ;
        float* yawPtr ;
        float* rollPtr;
        OLDDATACLASS();
};


class Communucation
{
    public:
        // SENSORS sensors = SENSORS();
        // STORAGE storage = STORAGE();
        uint16_t package_number = 1     ; 
        const uint16_t TEAM_ID  = 29779 ; // Takım Numarası
        OLDDATACLASS old_datas  =  OLDDATACLASS(); 
        
        
        const uint16_t oneHzInterval = 1000 ;
        unsigned long oneHZ                 ;


        const uint16_t testMotorsInterval = 10000 ;
        unsigned long motorElapsedTime            ; 
        
        uint16_t COMMAND      = 0   ;
        uint16_t bufferCt     = 0   ;
        uint8_t MAX_GCS_BYTES = 0   ;


        uint8_t Buffer[MAX_GCS_PACKET]  ;
        uint16_t INTERV                 ;
        int VID_LENGTH_CHCK_S           ;



        // Before sending any dataFrame or ACK frame 
        // This frame should be send.
        
        struct GCSFrame
        {
            uint8_t tagType;
            /*
                M 88 5 11111
                0 -> N
                1 -> M
                2 -> VS
                3 -> V
            */
            uint8_t command ;
           /*
                88..
                99..
                77..
           */

            uint8_t bufferSize;      // For example video data is 11111 Buffer size will be = 5
            
            uint8_t bufferArray[MAX_GCS_PACKET]; // Max 500 Byte!
        }gcsPacket;

       

        // Data and Interval should be sended from here.
        struct dataFrame
        {
            uint8_t FrameType; // Says ACK or DataFrame
            uint8_t FLIGHT_STATUS; // send Coded info? 
                        // 0 is WAITING
                        // 1 is RISING 
                        // 2    SEPERATING
                        // 3    FLIGHTFALL
                        // 4    PAYFALL
                        // 5    FIXEDALT
                        // 6    RESCUE

            uint8_t VIDEO_TRANSMISSION_INFO;
                        // 0 is No
                        // 1 is Yes
            

            float altitude          ;   // Yukseklik
            float pressure          ;   //Basınç
            float temperature       ; //Sıcaklık

            float turn_number       ; // Dönüş Sayısı
            float pitch             ; // Pitch
            float yaw               ; // Yaw
            float roll              ; // Roll

            float batteryVoltage    ;
            float descentSpeed      ;

            uint16_t Interval       ;
            uint16_t TEAM_ID        ;
            uint16_t package_number ;

            float latitude          ;
            float longtitude        ;

            // Add time infos..
            
            
        } __attribute__((packed)) dataPacket;
        
        struct dataFrame backupDataPacket;
     
        struct DescentControlVelocity
        {
            TickType_t oldReadedTime;
            TickType_t newReadedTime;
            float oldAltitude;
            float newAltitude;
            float Velocity;
            
        }descentControl;

        // When the GCS waits respond from us
        // Send that frame
        struct ACKFrame
        {
            uint8_t FrameType;
            uint8_t ACKType;
            uint8_t ACK;
            /*

                ACKType:
                    0 -> VS   ACK
                    1 -> V    ACK
                    2 -> E    ACK (COMM ENDED)
                    3 -> None None
                ACK :
                    0 -> UNSUCCESSFULLY
                    1 -> SUCCESSFULLY
                    2 -> if ACKType is  1 (V), Make ACK 2. Means Completed.
                    3-> VS ENDED
                    4-> None
            */
        }ACKPacket;

        union xControlVars// I am not giving that union as a param so make it global
        {

            struct 
            {
                uint8_t Readed                  : 1 ;
                uint8_t protocolReaded          : 1 ;
                uint8_t systemActivated         : 1 ;
     
                uint8_t startReaded             : 1 ;
                uint8_t fixAltitude             : 1 ;
                uint8_t fixAltitudeBefore       : 1 ;
                uint8_t seperatedBefore         : 1 ;
                
                uint8_t manupulationFalling     : 1 ; 

                uint8_t videoTransferCompleted  : 1 ;

                uint8_t videoSizeTransferred    : 1 ;


                

                uint8_t bmpReaded               : 1 ;
                uint8_t imuReaded               : 1 ;
                uint8_t gpsReaded               : 1 ;

                uint8_t sensorsReaded           : 1 ;

                
                /* Total 9 bit. -7 Bit UNUSED!-
                            We can Use Later!*/
                                
            }FLAGS;
            
            uint16_t resetFlag;
            
        }controlVar = {.resetFlag = RESET_FLAGS};
        
        static uint8_t activatedTelemTimer  ; 
        static uint8_t isTelemReadyTimer    ;

        struct timerStructure
        {
            TimerHandle_t timerfixedAlt;
            TimerHandle_t timerTelemetry;
        }timerPackage;

        unsigned long REACHED_SIZE = 0        ;
        unsigned long VIDEO_SIZE   = 10000000 ;
        

        unsigned long beforeReading ;
        unsigned long afterReading  ;
        unsigned long RemainTime    ;
        
        uint16_t CHCKSM             ;
        uint16_t VIDEO_BIN_LENGHT   ;
        // const char* udpAddress = "192.168.1.100"; // 192.168.1.7 works ?
        // const int udpPort = 3333;   

        
        //unsigned long testCalibration ;

        // MOTORS..
        // Servo ESC; // create servo object to control the ESC

        /* DECLARED ALLREADY END OF STRUCTURE */
        // struct dataFrame dataPacket ; 
        // struct ACKFrame ACKPacket   ;
        // struct GCSFrame gcsPacket   ;
        
        const uint8_t  pwmPin = 4                   ;
        char telemetryBuffer[MAX_TELEMETRY_LENGTH]  ;




        uint8_t HEADER = NOTHING_MISSED_H; // HEADER OF PACKAGE
        
        Communucation();                    //constructor.
        
        void sendPackage(void) ; // First send 
        void sendACK(void);
        void stringCopies(void); // in setup() run this function to copy.
        void readPressure(void);    //Basıncı okuma fonksiyonu
        void readAltitude(void);    //Yüksekliği okuma fonksiyonu
        void readTemperature(void); //Temp okuma fonk.
        void readTurnNumber(void); // Dönüş Sayısı okuma fonk.
        void mainLp(void); // Tek tek fonksiyonları çalıştırıp dataları auto gönderiyor.
        void readPitch(void); // Pitch'i oku
        void readRoll(void); // Roll'u oku
        void readYaw(void); // Yaw'u oku.
        void setNewStatus(void);
        bool waitforResponse(void);
        void releasePayload(void);
        void manualServiceCheck(void);
        void manualmotorActivation(bool fortesting);
        void getDatas(void);
        void getProtocolStatus(void);
        
        void readSerialDatas(void);
        void readIMU(void);
        void readGPS(void);
        void readBMP(void);
        static void fixAltTimer( TimerHandle_t xTimer );
        static void telemTimer( TimerHandle_t xTimer );
        
        

}; 

