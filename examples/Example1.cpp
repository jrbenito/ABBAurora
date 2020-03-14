/*
 *  Simple sketch that shows the basic usage of the ABBAurora class.
 *  Example is from an ESP32 with a MAX485 as RS485 interface.
 */
#include <Arduino.h>
#include <ABBAurora.h>



#define RX2 16
#define TX2 17
#define RX1 3
#define TX1 1
#define INVERTER_ADDRESS 2
#define TX_CONTROL_GPIO 4
#define TX_CONTROL_GPIO2 16

ABBAurora *inverter;
void setup()
{
    Serial.begin(115200);
    
#ifdef define(ESP832)
    ABBAurora::setup(Serial2, RX2, TX2, TX_CONTROL_GPIO);
  #elif defined(ESP8266)
    ABBAurora::setup(Serial, RX2, TX2, TX_CONTROL_GPIO);
#endif
    inverter = new ABBAurora(INVERTER_ADDRESS);
    Serial.println("Setup done");
}

void loop()
{
    if (inverter->ReadVersion())
    {
        Serial.print("Inverter Name: ");
        Serial.println(inverter->Version.Par1);
    }
    else
    {
        Serial.print("Inverter could not be reached");
        delay(500);
        return;
    }

    if (inverter->ReadDSPValue(POWER_IN_1, MODULE_MESSUREMENT))
    {
        Serial.print("Pin1 : ");
        Serial.print(inverter->DSP.Value);
        Serial.println(" W");
    }

    if (inverter->ReadCumulatedEnergy(CURRENT_DAY))
    {
        Serial.print("Energy: ");
        Serial.print(inverter->CumulatedEnergy.Energy);
        Serial.println(" Wh");
    }
}


#endif
