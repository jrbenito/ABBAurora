#ifndef ABBAurora_h
#define ABBAurora_h
#include <Arduino.h>
#include <Wire.h>

//RS485 control
#define RS485Transmit HIGH
#define RS485Receive LOW

class ABBAurora
{
private:
    int MaxAttempt = 1;
    byte Address = 0;
    static byte TXPinControl;
    static HardwareSerial *serial;

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

    static void setup(HardwareSerial &serial, byte RXGpioPin, byte TXGpioPin, byte TXControllPin);

    ABBAurora(byte address);

    void clearReceiveData();

    typedef struct
    {
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

    typedef struct
    {
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

    typedef struct
    {
        byte TransmissionState;
        byte GlobalState;
        float Value;
        bool ReadState;
    } DataDSP;

    DataDSP DSP;

    bool ReadDSPValue(DSP_VALUE_TYPE type, byte global);

    typedef struct
    {
        byte TransmissionState;
        byte GlobalState;
        unsigned long Seconds;
        bool ReadState;
    } DataTimeDate;

    DataTimeDate TimeDate;

    bool ReadTimeDate();

    typedef struct
    {
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
    typedef struct
    {
        String PN;
        bool ReadState;
    } DataSystemPN;

    DataSystemPN SystemPN;

    bool ReadSystemPN();

    typedef struct
    {
        String SerialNumber;
        bool ReadState;
    } DataSystemSerialNumber;

    DataSystemSerialNumber SystemSerialNumber;

    bool ReadSystemSerialNumber();

    typedef struct
    {
        byte TransmissionState;
        byte GlobalState;
        String Week;
        String Year;
        bool ReadState;
    } DataManufacturingWeekYear;

    DataManufacturingWeekYear ManufacturingWeekYear;

    bool ReadManufacturingWeekYear();

    typedef struct
    {
        byte TransmissionState;
        byte GlobalState;
        String Release;
        bool ReadState;
    } DataFirmwareRelease;

    DataFirmwareRelease FirmwareRelease;

    bool ReadFirmwareRelease();

    typedef struct
    {
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

enum DSP_VALUE_TYPE
{
    GRID_VOLTAGE = 1,
    GRID_CURRENT = 2,
    GRID_POWER = 3,
    FREQUENCY = 4,
    V_BULK = 5,
    I_LEAK_DC_DC = 6,
    I_LEAK_INVERTER = 7,
    POWER_IN_1 = 8,
    POWER_IN_2 = 9,
    TEMPERATURE_INVERTER = 21,
    TEMPERATURE_BOOSTER = 22,
    V_IN_1 = 23,
    I_IN_1 = 25,
    V_IN_2 = 26,
    I_IN_2 = 27,
    DC_DC_GRID_VOLTAGE = 28,
    DC_DC_GRID_FREQUENCY = 29,
    ISOLATION_RESISTANCE = 30,
    DC_DC_V_BULK = 31,
    AVERAGE_GRID_VOLTAGE = 32,
    V_BULK_MID = 33,
    POWER_PEAK = 34,
    POWER_PEAK_TODAY = 35,
    GRID_VOLTAGE_NEUTRAL = 36,
    WIND_GENERATOR_FREQENCY = 37,
    GRID_VOLTAGE_NEUTRAL_PHASE = 38,
    GRID_CURRENT_PHASE_R = 39,
    GRID_CURRENT_PHASE_S = 40,
    GRID_CURRENT_PHASE_T = 41,
    FREQUENCY_PHASE_R = 42,
    FREQUENCY_PHASE_S = 43,
    FREQUENCY_PHASE_T = 44,
    V_BULK_POSITIVE = 45,
    V_BULK_NEGATIVE = 46,
    TEMPERATURE_SUPERVISOR = 47,
    TEMPERATURE_ALIM = 48,
    TEMPERATURE_HEAT_SINK = 49,
    TEMPERATURE_1 = 50,
    TEMPERATURE_2 = 51,
    TEMPERATURE_3 = 52,
    FAN_SPEED_1 = 53,
    FAN_SPEED_2 = 54,
    FAN_SPEED_3 = 55,
    FAN_SPEED_4 = 56,
    FAN_SPEED_5 = 57,
    POWER_SATURATION_LIMIT = 58,
    V_PANEL_MICRO = 60,
    GRID_VOLTAGE_PHASE_R = 61,
    GRID_VOLTAGE_PHASE_S = 62,
    GRID_VOLTAGE_PHASE_T = 63

};

#endif
