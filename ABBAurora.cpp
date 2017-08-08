#include "ABBAurora.h"

void ABBAurora::clearData(byte *data, byte len) {
    for (int i = 0; i < len; i++) {
        data[i] = 0;
    }
}

int ABBAurora::Crc16(byte *data, int offset, int count)
{
    byte BccLo = 0xFF;
    byte BccHi = 0xFF;

    for (int i = offset; i < (offset + count); i++)
    {
        byte New = data[offset + i] ^ BccLo;
        byte Tmp = New << 4;
        New = Tmp ^ New;
        Tmp = New >> 5;
        BccLo = BccHi;
        BccHi = New ^ Tmp;
        Tmp = New << 3;
        BccLo = BccLo ^ Tmp;
        Tmp = New >> 4;
        BccLo = BccLo ^ Tmp;

    }

    return (int)word(~BccHi, ~BccLo);
}

bool ABBAurora::Send(byte address, byte param0, byte param1, byte param2, byte param3, byte param4, byte param5, byte param6)
{

    SendStatus = false;
    ReceiveStatus = false;

    byte SendData[10];
    SendData[0] = address;
    SendData[1] = param0;
    SendData[2] = param1;
    SendData[3] = param2;
    SendData[4] = param3;
    SendData[5] = param4;
    SendData[6] = param5;
    SendData[7] = param6;

    int crc = Crc16(SendData, 0, 8);
    SendData[8] = lowByte(crc);
    SendData[9] = highByte(crc);

    clearReceiveData();

    for (int i = 0; i < this->MaxAttempt; i++)
    {
        digitalWrite(this->TXPinControl, RS485Transmit);
        delay(50);

        if (Serial.write(SendData, sizeof(SendData)) != 0) {
            Serial.flush();
            SendStatus = true;

            digitalWrite(this->TXPinControl, RS485Receive);

            if (Serial.readBytes(ReceiveData, sizeof(ReceiveData)) != 0) {
                if ((int)word(ReceiveData[7], ReceiveData[6]) == Crc16(ReceiveData, 0, 6)) {
                    ReceiveStatus = true;
                    break;
                }
            }
        }
    }
    return ReceiveStatus;
}

ABBAurora::ABBAurora(byte address) {
    this->Address = address;
    this->TXPinControl = SSerialTxControl;

    SendStatus = false;
    ReceiveStatus = false;

    clearReceiveData();
}

ABBAurora::ABBAurora(byte address, byte TXPinControl) {
    this->Address = address;
    this->TXPinControl = TXPinControl;

    SendStatus = false;
    ReceiveStatus = false;

    clearReceiveData();
}

void ABBAurora::clearReceiveData() {
    clearData(ReceiveData, 8);
}

String ABBAurora::TransmissionState(byte id) {
    switch (id)
    {
        case 0:
            return F("Everything is OK.");
            break;
        case 51:
            return F("Command is not implemented");
            break;
        case 52:
            return F("Variable does not exist");
            break;
        case 53:
            return F("Variable value is out of range");
            break;
        case 54:
            return F("EEprom not accessible");
            break;
        case 55:
            return F("Not Toggled Service Mode");
            break;
        case 56:
            return F("Can not send the command to internal micro");
            break;
        case 57:
            return F("Command not Executed");
            break;
        case 58:
            return F("The variable is not available, retry");
            break;
        default:
            return F("Sconosciuto");
            break;
    }
}

String ABBAurora::GlobalState(byte id) {
    switch (id)
    {
        case 0:
            return F("Sending Parameters");
            break;
        case 1:
            return F("Wait Sun / Grid");
            break;
        case 2:
            return F("Checking Grid");
            break;
        case 3:
            return F("Measuring Riso");
            break;
        case 4:
            return F("DcDc Start");
            break;
        case 5:
            return F("Inverter Start");
            break;
        case 6:
            return F("Run");
            break;
        case 7:
            return F("Recovery");
            break;
        case 8:
            return F("Pausev");
            break;
        case 9:
            return F("Ground Fault");
            break;
        case 10:
            return F("OTH Fault");
            break;
        case 11:
            return F("Address Setting");
            break;
        case 12:
            return F("Self Test");
            break;
        case 13:
            return F("Self Test Fail");
            break;
        case 14:
            return F("Sensor Test + Meas.Riso");
            break;
        case 15:
            return F("Leak Fault");
            break;
        case 16:
            return F("Waiting for manual reset");
            break;
        case 17:
            return F("Internal Error E026");
            break;
        case 18:
            return F("Internal Error E027");
            break;
        case 19:
            return F("Internal Error E028");
            break;
        case 20:
            return F("Internal Error E029");
            break;
        case 21:
            return F("Internal Error E030");
            break;
        case 22:
            return F("Sending Wind Table");
            break;
        case 23:
            return F("Failed Sending table");
            break;
        case 24:
            return F("UTH Fault");
            break;
        case 25:
            return F("Remote OFF");
            break;
        case 26:
            return F("Interlock Fail");
            break;
        case 27:
            return F("Executing Autotest");
            break;
        case 30:
            return F("Waiting Sun");
            break;
        case 31:
            return F("Temperature Fault");
            break;
        case 32:
            return F("Fan Staucked");
            break;
        case 33:
            return F("Int.Com.Fault");
            break;
        case 34:
            return F("Slave Insertion");
            break;
        case 35:
            return F("DC Switch Open");
            break;
        case 36:
            return F("TRAS Switch Open");
            break;
        case 37:
            return F("MASTER Exclusion");
            break;
        case 38:
            return F("Auto Exclusion");
            break;
        case 98:
            return F("Erasing Internal EEprom");
            break;
        case 99:
            return F("Erasing External EEprom");
            break;
        case 100:
            return F("Counting EEprom");
            break;
        case 101:
            return F("Freeze");
        default:
            return F("Sconosciuto");
            break;
    }
}

String ABBAurora::DcDcState(byte id) {
    switch (id)
    {
        case 0:
            return F("DcDc OFF");
            break;
        case 1:
            return F("Ramp Start");
            break;
        case 2:
            return F("MPPT");
            break;
        case 3:
            return F("Not Used");
            break;
        case 4:
            return F("Input OC");
            break;
        case 5:
            return F("Input UV");
            break;
        case 6:
            return F("Input OV");
            break;
        case 7:
            return F("Input Low");
            break;
        case 8:
            return F("No Parameters");
            break;
        case 9:
            return F("Bulk OV");
            break;
        case 10:
            return F("Communication Error");
            break;
        case 11:
            return F("Ramp Fail");
            break;
        case 12:
            return F("Internal Error");
            break;
        case 13:
            return F("Input mode Error");
            break;
        case 14:
            return F("Ground Fault");
            break;
        case 15:
            return F("Inverter Fail");
            break;
        case 16:
            return F("DcDc IGBT Sat");
            break;
        case 17:
            return F("DcDc ILEAK Fail");
            break;
        case 18:
            return F("DcDc Grid Fail");
            break;
        case 19:
            return F("DcDc Comm.Error");
            break;
        default:
            return F("Sconosciuto");
            break;
    }
}

String ABBAurora::InverterState(byte id) {
    switch (id)
    {
        case 0:
            return F("Stand By");
            break;
        case 1:
            return F("Checking Grid");
            break;
        case 2:
            return F("Run");
            break;
        case 3:
            return F("Bulk OV");
            break;
        case 4:
            return F("Out OC");
            break;
        case 5:
            return F("IGBT Sat");
            break;
        case 6:
            return F("Bulk UV");
            break;
        case 7:
            return F("Degauss Error");
            break;
        case 8:
            return F("No Parameters");
            break;
        case 9:
            return F("Bulk Low");
            break;
        case 10:
            return F("Grid OV");
            break;
        case 11:
            return F("Communication Error");
            break;
        case 12:
            return F("Degaussing");
            break;
        case 13:
            return F("Starting");
            break;
        case 14:
            return F("Bulk Cap Fail");
            break;
        case 15:
            return F("Leak Fail");
            break;
        case 16:
            return F("DcDc Fail");
            break;
        case 17:
            return F("Ileak Sensor Fail");
            break;
        case 18:
            return F("SelfTest: relay inverter");
            break;
        case 19:
            return F("SelfTest : wait for sensor test");
            break;
        case 20:
            return F("SelfTest : test relay DcDc + sensor");
            break;
        case 21:
            return F("SelfTest : relay inverter fail");
            break;
        case 22:
            return F("SelfTest timeout fail");
            break;
        case 23:
            return F("SelfTest : relay DcDc fail");
            break;
        case 24:
            return F("Self Test 1");
            break;
        case 25:
            return F("Waiting self test start");
            break;
        case 26:
            return F("Dc Injection");
            break;
        case 27:
            return F("Self Test 2");
            break;
        case 28:
            return F("Self Test 3");
            break;
        case 29:
            return F("Self Test 4");
            break;
        case 30:
            return F("Internal Error");
            break;
        case 31:
            return F("Internal Error");
            break;
        case 40:
            return F("Forbidden State");
            break;
        case 41:
            return F("Input UC");
            break;
        case 42:
            return F("Zero Power");
            break;
        case 43:
            return F("Grid Not Present");
            break;
        case 44:
            return F("Waiting Start");
            break;
        case 45:
            return F("MPPT");
            break;
        case 46:
            return F("Grid Fail");
            break;
        case 47:
            return F("Input OC");
            break;
        default:
            return F("Sconosciuto");
            break;
    }
}

String ABBAurora::AlarmState(byte id) {
    switch (id)
    {
        case 0:
            return F("No Alarm");
            break;
        case 1:
            return F("Sun Low");
            break;
        case 2:
            return F("Input OC");
            break;
        case 3:
            return F("Input UV");
            break;
        case 4:
            return F("Input OV");
            break;
        case 5:
            return F("Sun Low");
            break;
        case 6:
            return F("No Parameters");
            break;
        case 7:
            return F("Bulk OV");
            break;
        case 8:
            return F("Comm.Error");
            break;
        case 9:
            return F("Output OC");
            break;
        case 10:
            return F("IGBT Sat");
            break;
        case 11:
            return F("Bulk UV");
            break;
        case 12:
            return F("Internal error");
            break;
        case 13:
            return F("Grid Fail");
            break;
        case 14:
            return F("Bulk Low");
            break;
        case 15:
            return F("Ramp Fail");
            break;
        case 16:
            return F("Dc / Dc Fail");
            break;
        case 17:
            return F("Wrong Mode");
            break;
        case 18:
            return F("Ground Fault");
            break;
        case 19:
            return F("Over Temp.");
            break;
        case 20:
            return F("Bulk Cap Fail");
            break;
        case 21:
            return F("Inverter Fail");
            break;
        case 22:
            return F("Start Timeout");
            break;
        case 23:
            return F("Ground Fault");
            break;
        case 24:
            return F("Degauss error");
            break;
        case 25:
            return F("Ileak sens.fail");
            break;
        case 26:
            return F("DcDc Fail");
            break;
        case 27:
            return F("Self Test Error 1");
            break;
        case 28:
            return F("Self Test Error 2");
            break;
        case 29:
            return F("Self Test Error 3");
            break;
        case 30:
            return F("Self Test Error 4");
            break;
        case 31:
            return F("DC inj error");
            break;
        case 32:
            return F("Grid OV");
            break;
        case 33:
            return F("Grid UV");
            break;
        case 34:
            return F("Grid OF");
            break;
        case 35:
            return F("Grid UF");
            break;
        case 36:
            return F("Z grid Hi");
            break;
        case 37:
            return F("Internal error");
            break;
        case 38:
            return F("Riso Low");
            break;
        case 39:
            return F("Vref Error");
            break;
        case 40:
            return F("Error Meas V");
            break;
        case 41:
            return F("Error Meas F");
            break;
        case 42:
            return F("Error Meas Z");
            break;
        case 43:
            return F("Error Meas Ileak");
            break;
        case 44:
            return F("Error Read V");
            break;
        case 45:
            return F("Error Read I");
            break;
        case 46:
            return F("Table fail");
            break;
        case 47:
            return F("Fan Fail");
            break;
        case 48:
            return F("UTH");
            break;
        case 49:
            return F("Interlock fail");
            break;
        case 50:
            return F("Remote Off");
            break;
        case 51:
            return F("Vout Avg errror");
            break;
        case 52:
            return F("Battery low");
            break;
        case 53:
            return F("Clk fail");
            break;
        case 54:
            return F("Input UC");
            break;
        case 55:
            return F("Zero Power");
            break;
        case 56:
            return F("Fan Stucked");
            break;
        case 57:
            return F("DC Switch Open");
            break;
        case 58:
            return F("Tras Switch Open");
            break;
        case 59:
            return F("AC Switch Open");
            break;
        case 60:
            return F("Bulk UV");
            break;
        case 61:
            return F("Autoexclusion");
            break;
        case 62:
            return F("Grid df / dt");
            break;
        case 63:
            return F("Den switch Open");
            break;
        case 64:
            return F("Jbox fail");
            break;
        default:
            return F("Sconosciuto");
            break;
    }
}

bool ABBAurora::ReadState() {
    State.ReadState = Send(this->Address, (byte)50, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (State.ReadState == false) {
        ReceiveData[0] = 255;
        ReceiveData[1] = 255;
        ReceiveData[2] = 255;
        ReceiveData[3] = 255;
        ReceiveData[4] = 255;
        ReceiveData[5] = 255;
    }

    State.TransmissionState = ReceiveData[0];
    State.GlobalState = ReceiveData[1];
    State.InverterState = ReceiveData[2];
    State.Channel1State = ReceiveData[3];
    State.Channel2State = ReceiveData[4];
    State.AlarmState = ReceiveData[5];

    return State.ReadState;
}

bool ABBAurora::ReadVersion() {
    Version.ReadState = Send(this->Address, (byte)58, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (Version.ReadState == false) {
        ReceiveData[0] = 255;
        ReceiveData[1] = 255;
    }

    Version.TransmissionState = ReceiveData[0];
    Version.GlobalState = ReceiveData[1];

    switch ((char)ReceiveData[2])
    {
        case 'i':
            Version.Par1 = F("Aurora 2 kW indoor");
            break;
        case 'o':
            Version.Par1 = F("Aurora 2 kW outdoor");
            break;
        case 'I':
            Version.Par1 = F("Aurora 3.6 kW indoor");
            break;
        case 'O':
            Version.Par1 = F("Aurora 3.0 - 3.6 kW outdoor");
            break;
        case '5':
            Version.Par1 = F("Aurora 5.0 kW outdoor");
            break;
        case '6':
            Version.Par1 = F("Aurora 6 kW outdoor");
            break;
        case 'P':
            Version.Par1 = F("3 - phase interface (3G74)");
            break;
        case 'C':
            Version.Par1 = F("Aurora 50kW module");
            break;
        case '4':
            Version.Par1 = F("Aurora 4.2kW new");
            break;
        case '3':
            Version.Par1 = F("Aurora 3.6kW new");
            break;
        case '2':
            Version.Par1 = F("Aurora 3.3kW new");
            break;
        case '1':
            Version.Par1 = F("Aurora 3.0kW new");
            break;
        case 'D':
            Version.Par1 = F("Aurora 12.0kW");
            break;
        case 'X':
            Version.Par1 = F("Aurora 10.0kW");
            break;
        default:
            Version.Par1 = F("Sconosciuto");
            break;
    }

    switch ((char)ReceiveData[3])
    {
        case 'A':
            Version.Par2 = F("UL1741");
            break;
        case 'E':
            Version.Par2 = F("VDE0126");
            break;
        case 'S':
            Version.Par2 = F("DR 1663 / 2000");
            break;
        case 'I':
            Version.Par2 = F("ENEL DK 5950");
            break;
        case 'U':
            Version.Par2 = F("UK G83");
            break;
        case 'K':
            Version.Par2 = F("AS 4777");
            break;
        default:
            Version.Par2 = F("Sconosciuto");
            break;
    }

    switch ((char)ReceiveData[4])
    {
        case 'N':
            Version.Par3 = F("Transformerless Version");
            break;
        case 'T':
            Version.Par3 = F("Transformer Version");
            break;
        default:
            Version.Par3 = F("Sconosciuto");
            break;
    }

    switch ((char)ReceiveData[5])
    {
        case 'W':
            Version.Par4 = F("Wind version");
            break;
        case 'N':
            Version.Par4 = F("PV version");
            break;
        default:
            Version.Par4 = F("Sconosciuto");
            break;
    }

    return Version.ReadState;
}

bool ABBAurora::ReadDSP(byte type, byte global) {
    if ((((int)type >= 1 && (int)type <= 9) || ((int)type >= 21 && (int)type <= 63)) && ((int)global >= 0 && (int)global <= 1)) {
        DSP.ReadState = Send(this->Address, (byte)59, type, global, (byte)0, (byte)0, (byte)0, (byte)0);

        if (DSP.ReadState == false) {
            ReceiveData[0] = 255;
            ReceiveData[1] = 255;
        }

    }
    else {
        DSP.ReadState = false;
        clearReceiveData();
        ReceiveData[0] = 255;
        ReceiveData[1] = 255;
    }

    DSP.TransmissionState = ReceiveData[0];
    DSP.GlobalState = ReceiveData[1];

    foo.asBytes[0] = ReceiveData[5];
    foo.asBytes[1] = ReceiveData[4];
    foo.asBytes[2] = ReceiveData[3];
    foo.asBytes[3] = ReceiveData[2];

    DSP.Valore = foo.asFloat;

    return DSP.ReadState;
}

bool ABBAurora::ReadTimeDate() {
    TimeDate.ReadState = Send(this->Address, (byte)70, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (TimeDate.ReadState == false) {
        ReceiveData[0] = 255;
        ReceiveData[1] = 255;
    }

    TimeDate.TransmissionState = ReceiveData[0];
    TimeDate.GlobalState = ReceiveData[1];
    TimeDate.Secondi = ((unsigned long)ReceiveData[2] << 24) + ((unsigned long)ReceiveData[3] << 16) + ((unsigned long)ReceiveData[4] << 8) + (unsigned long)ReceiveData[5];
    return TimeDate.ReadState;
}

bool ABBAurora::ReadLastFourAlarms() {
    LastFourAlarms.ReadState = Send(this->Address, (byte)86, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (LastFourAlarms.ReadState == false) {
        ReceiveData[0] = 255;
        ReceiveData[1] = 255;
        ReceiveData[2] = 255;
        ReceiveData[3] = 255;
        ReceiveData[4] = 255;
        ReceiveData[5] = 255;
    }

    LastFourAlarms.TransmissionState = ReceiveData[0];
    LastFourAlarms.GlobalState = ReceiveData[1];
    LastFourAlarms.Alarms1 = ReceiveData[2];
    LastFourAlarms.Alarms2 = ReceiveData[3];
    LastFourAlarms.Alarms3 = ReceiveData[4];
    LastFourAlarms.Alarms4 = ReceiveData[5];

    return LastFourAlarms.ReadState;
}

bool ABBAurora::ReadJunctionBoxState(byte nj) {
    return Send(this->Address, (byte)200, nj, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
}

bool ABBAurora::ReadJunctionBoxVal(byte nj, byte par) {
    return Send(this->Address, (byte)201, nj, par, (byte)0, (byte)0, (byte)0, (byte)0);
}

// Inverters

bool ABBAurora::ReadSystemPN() {
    SystemPN.ReadState = Send(this->Address, (byte)52, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    SystemPN.PN = String(String((char)ReceiveData[0]) + String((char)ReceiveData[1]) + String((char)ReceiveData[2]) + String((char)ReceiveData[3]) + String((char)ReceiveData[4]) + String((char)ReceiveData[5]));

    return SystemPN.ReadState;
}

bool ABBAurora::ReadSystemSerialNumber() {
    SystemSerialNumber.ReadState = Send(this->Address, (byte)63, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    SystemSerialNumber.SerialNumber = String(String((char)ReceiveData[0]) + String((char)ReceiveData[1]) + String((char)ReceiveData[2]) + String((char)ReceiveData[3]) + String((char)ReceiveData[4]) + String((char)ReceiveData[5]));

    return SystemSerialNumber.ReadState;
}

bool ABBAurora::ReadManufacturingWeekYear() {
    ManufacturingWeekYear.ReadState = Send(this->Address, (byte)65, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (ManufacturingWeekYear.ReadState == false) {
        ReceiveData[0] = 255;
        ReceiveData[1] = 255;
    }

    ManufacturingWeekYear.TransmissionState = ReceiveData[0];
    ManufacturingWeekYear.GlobalState = ReceiveData[1];
    ManufacturingWeekYear.Week = String(String((char)ReceiveData[2]) + String((char)ReceiveData[3]));
    ManufacturingWeekYear.Year = String(String((char)ReceiveData[4]) + String((char)ReceiveData[5]));

    return ManufacturingWeekYear.ReadState;
}

bool ABBAurora::ReadFirmwareRelease() {
    FirmwareRelease.ReadState = Send(this->Address, (byte)72, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

    if (FirmwareRelease.ReadState == false) {
        ReceiveData[0] = 255;
        ReceiveData[1] = 255;
    }

    FirmwareRelease.TransmissionState = ReceiveData[0];
    FirmwareRelease.GlobalState = ReceiveData[1];
    FirmwareRelease.Release = String(String((char)ReceiveData[2]) + "." + String((char)ReceiveData[3]) + "." + String((char)ReceiveData[4]) + "." + String((char)ReceiveData[5]));

    return FirmwareRelease.ReadState;
}

bool ABBAurora::ReadCumulatedEnergy(byte par) {
    if ((int)par >= 0 && (int)par <= 6) {
        CumulatedEnergy.ReadState = Send(this->Address, (byte)78, par, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);

        if (CumulatedEnergy.ReadState == false) {
            ReceiveData[0] = 255;
            ReceiveData[1] = 255;
        }

    }
    else {
        CumulatedEnergy.ReadState = false;
        clearReceiveData();
        ReceiveData[0] = 255;
        ReceiveData[1] = 255;
    }

    CumulatedEnergy.TransmissionState = ReceiveData[0];
    CumulatedEnergy.GlobalState = ReceiveData[1];
    if (CumulatedEnergy.ReadState == true) {
        ulo.asBytes[0] = ReceiveData[5];
        ulo.asBytes[1] = ReceiveData[4];
        ulo.asBytes[2] = ReceiveData[3];
        ulo.asBytes[3] = ReceiveData[2];

        CumulatedEnergy.Energia = ulo.asUlong;
    }
    return CumulatedEnergy.ReadState;
}

bool ABBAurora::WriteBaudRateSetting(byte baudcode) {
    if ((int)baudcode >= 0 && (int)baudcode <= 3) {
        return Send(this->Address, (byte)85, baudcode, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
    }
    else {
        clearReceiveData();
        return false;
    }
}

// Central
bool ABBAurora::ReadFlagsSwitchCentral() {
    return Send(this->Address, (byte)67, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
}

bool ABBAurora::ReadCumulatedEnergyCentral(byte var, byte ndays_h, byte ndays_l, byte global) {
    return Send(this->Address, (byte)68, var, ndays_h, ndays_l, global, (byte)0, (byte)0);
}

bool ABBAurora::ReadFirmwareReleaseCentral(byte var) {
    return Send(this->Address, (byte)72, var, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
}

bool ABBAurora::ReadBaudRateSettingCentral(byte baudcode, byte serialline) {
    return Send(this->Address, (byte)85, baudcode, serialline, (byte)0, (byte)0, (byte)0, (byte)0);
}

bool ABBAurora::ReadSystemInfoCentral(byte var) {
    return Send(this->Address, (byte)101, var, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
}

bool ABBAurora::ReadJunctionBoxMonitoringCentral(byte cf, byte rn, byte njt, byte jal, byte jah) {
    return Send(this->Address, (byte)103, cf, rn, njt, jal, jah, (byte)0);
}

bool ABBAurora::ReadSystemPNCentral() {
    return Send(this->Address, (byte)105, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
}

bool ABBAurora::ReadSystemSerialNumberCentral() {
    return Send(this->Address, (byte)107, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0);
}
