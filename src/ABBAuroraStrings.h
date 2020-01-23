#ifndef ABBAuroraStrings_h
#define ABBAuroraStrings_h
#include <Arduino.h>

class ABBAuroraStrings {
    private:
        

    public:
       static String TransmissionState(byte id);
       static String GlobalState(byte id);
       static String DcDcState(byte id);
       static String InverterState(byte id);
       static String AlarmState(byte id);
       static String VersionPart1(byte id);
       static String VersionPart2(byte id);
       static String VersionPart3(byte id);
       static String VersionPart4(byte id);
};
#endif
