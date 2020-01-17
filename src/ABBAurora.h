#ifndef ABBAurora_h
#define ABBAurora_h
#include <Arduino.h>
#include <Wire.h> 

//RS485 control
#define SSerialTxControl 5
#define RS485Transmit HIGH 
#define RS485Receive LOW 

class ABBAurora {
    private:
        int MaxAttempt = 1;
        byte Address = 0;
        byte TXPinControl;

        void clearData(byte *data, byte len);

        int Crc16(byte *data, int offset, int count);

        bool Send(byte address, byte param0, byte param1, byte param2, byte param3, byte param4, byte param5, byte param6);

        union {
            byte asBytes[4];
            float asFloat;
        } foo;

        union {
            byte asBytes[4];
            unsigned long asUlong;
        } ulo;

    public:
        bool SendStatus = false;
        bool ReceiveStatus = false;
        byte ReceiveData[8];

        ABBAurora(byte address);
        ABBAurora(byte address, byte TXPinControl);

        void clearReceiveData();

        String TransmissionState(byte id);

        String GlobalState(byte id);

        String DcDcState(byte id);

        String InverterState(byte id);

        String AlarmState(byte id);

        typedef struct {
            byte TransmissionState;
            byte GlobalState;
            byte InverterState;
            byte Channel1State;
            byte Channel2State;
            byte AlarmState;
            bool ReadState;
        } DataState;

        DataState State;

        bool ReadState();

        typedef struct {
            byte TransmissionState;
            byte GlobalState;
            String Par1;
            String Par2;
            String Par3;
            String Par4;
            bool ReadState;
        } DataVersion;

        DataVersion Version;

        bool ReadVersion();

        typedef struct {
            byte TransmissionState;
            byte GlobalState;
            float Value;
            bool ReadState;
        } DataDSP;

        DataDSP DSP;

        bool ReadDSP(byte type, byte global);

        typedef struct {
            byte TransmissionState;
            byte GlobalState;
            unsigned long Seconds;
            bool ReadState;
        } DataTimeDate;

        DataTimeDate TimeDate;

        bool ReadTimeDate();

        typedef struct {
            byte TransmissionState;
            byte GlobalState;
            byte Alarms1;
            byte Alarms2;
            byte Alarms3;
            byte Alarms4;
            bool ReadState;
        } DataLastFourAlarms;

        DataLastFourAlarms LastFourAlarms;

        bool ReadLastFourAlarms();

        bool ReadJunctionBoxState(byte nj);

        bool ReadJunctionBoxVal(byte nj, byte par);

        // Inverters
        typedef struct {
            String PN;
            bool ReadState;
        } DataSystemPN;

        DataSystemPN SystemPN;

        bool ReadSystemPN();

        typedef struct {
            String SerialNumber;
            bool ReadState;
        } DataSystemSerialNumber;

        DataSystemSerialNumber SystemSerialNumber;

        bool ReadSystemSerialNumber();

        typedef struct {
            byte TransmissionState;
            byte GlobalState;
            String Week;
            String Year;
            bool ReadState;
        } DataManufacturingWeekYear;

        DataManufacturingWeekYear ManufacturingWeekYear;

        bool ReadManufacturingWeekYear();

        typedef struct {
            byte TransmissionState;
            byte GlobalState;
            String Release;
            bool ReadState;
        } DataFirmwareRelease;

        DataFirmwareRelease FirmwareRelease;

        bool ReadFirmwareRelease();

        typedef struct {
            byte TransmissionState;
            byte GlobalState;
            unsigned long Energy;
            bool ReadState;
        } DataCumulatedEnergy;

        DataCumulatedEnergy CumulatedEnergy;

        bool ReadCumulatedEnergy(byte par);

        bool WriteBaudRateSetting(byte baudcode);

        // Central
        bool ReadFlagsSwitchCentral();

        bool ReadCumulatedEnergyCentral(byte var, byte ndays_h, byte ndays_l, byte global);

        bool ReadFirmwareReleaseCentral(byte var);

        bool ReadBaudRateSettingCentral(byte baudcode, byte serialline);

        bool ReadSystemInfoCentral(byte var);

        bool ReadJunctionBoxMonitoringCentral(byte cf, byte rn, byte njt, byte jal, byte jah);

        bool ReadSystemPNCentral();

        bool ReadSystemSerialNumberCentral();

};
#endif
