#include "ABBAuroraStrings.h"

String ABBAuroraStrings::TransmissionState(byte id)
{
    switch (id)
    {
    case 0:
        return F("Everything is OK.");
    case 51:
        return F("Command is not implemented");
    case 52:
        return F("Variable does not exist");
    case 53:
        return F("Variable value is out of range");
    case 54:
        return F("EEprom not accessible");
    case 55:
        return F("Not Toggled Service Mode");
    case 56:
        return F("Can not send the command to internal micro");
    case 57:
        return F("Command not Executed");
    case 58:
        return F("The variable is not available, retry");
    default:
        return F("Unknown");
    }
}

String ABBAuroraStrings::GlobalState(byte id)
{
    switch (id)
    {
    case 0:
        return F("Sending Parameters");
    case 1:
        return F("Wait Sun / Grid");
    case 2:
        return F("Checking Grid");
    case 3:
        return F("Measuring Riso");
    case 4:
        return F("DcDc Start");
    case 5:
        return F("Inverter Start");
    case 6:
        return F("Run");
    case 7:
        return F("Recovery");
    case 8:
        return F("Pausev");
    case 9:
        return F("Ground Fault");
    case 10:
        return F("OTH Fault");
    case 11:
        return F("Address Setting");
    case 12:
        return F("Self Test");
    case 13:
        return F("Self Test Fail");
    case 14:
        return F("Sensor Test + Meas.Riso");
    case 15:
        return F("Leak Fault");
    case 16:
        return F("Waiting for manual reset");
    case 17:
        return F("Internal Error E026");
    case 18:
        return F("Internal Error E027");
    case 19:
        return F("Internal Error E028");
    case 20:
        return F("Internal Error E029");
    case 21:
        return F("Internal Error E030");
    case 22:
        return F("Sending Wind Table");
    case 23:
        return F("Failed Sending table");
    case 24:
        return F("UTH Fault");
    case 25:
        return F("Remote OFF");
    case 26:
        return F("Interlock Fail");
    case 27:
        return F("Executing Autotest");
    case 30:
        return F("Waiting Sun");
    case 31:
        return F("Temperature Fault");
    case 32:
        return F("Fan Staucked");
    case 33:
        return F("Int.Com.Fault");
    case 34:
        return F("Slave Insertion");
    case 35:
        return F("DC Switch Open");
    case 36:
        return F("TRAS Switch Open");
    case 37:
        return F("MASTER Exclusion");
    case 38:
        return F("Auto Exclusion");
    case 98:
        return F("Erasing Internal EEprom");
    case 99:
        return F("Erasing External EEprom");
    case 100:
        return F("Counting EEprom");
    case 101:
        return F("Freeze");
    default:
        return F("Unknown");
    }
}

String ABBAuroraStrings::DcDcState(byte id)
{
    switch (id)
    {
    case 0:
        return F("DcDc OFF");
    case 1:
        return F("Ramp Start");
    case 2:
        return F("MPPT");
    case 3:
        return F("Not Used");
    case 4:
        return F("Input OC");
    case 5:
        return F("Input UV");
    case 6:
        return F("Input OV");
    case 7:
        return F("Input Low");
    case 8:
        return F("No Parameters");
    case 9:
        return F("Bulk OV");
    case 10:
        return F("Communication Error");
    case 11:
        return F("Ramp Fail");
    case 12:
        return F("Internal Error");
    case 13:
        return F("Input mode Error");
    case 14:
        return F("Ground Fault");
    case 15:
        return F("Inverter Fail");
    case 16:
        return F("DcDc IGBT Sat");
    case 17:
        return F("DcDc ILEAK Fail");
    case 18:
        return F("DcDc Grid Fail");
    case 19:
        return F("DcDc Comm.Error");
    default:
        return F("Unknown");
    }
}

String ABBAuroraStrings::InverterState(byte id)
{
    switch (id)
    {
    case 0:
        return F("Stand By");
    case 1:
        return F("Checking Grid");
    case 2:
        return F("Run");
    case 3:
        return F("Bulk OV");
    case 4:
        return F("Out OC");
    case 5:
        return F("IGBT Sat");
    case 6:
        return F("Bulk UV");
    case 7:
        return F("Degauss Error");
    case 8:
        return F("No Parameters");
    case 9:
        return F("Bulk Low");
    case 10:
        return F("Grid OV");
    case 11:
        return F("Communication Error");
    case 12:
        return F("Degaussing");
    case 13:
        return F("Starting");
    case 14:
        return F("Bulk Cap Fail");
    case 15:
        return F("Leak Fail");
    case 16:
        return F("DcDc Fail");
    case 17:
        return F("Ileak Sensor Fail");
    case 18:
        return F("SelfTest: relay inverter");
    case 19:
        return F("SelfTest : wait for sensor test");
    case 20:
        return F("SelfTest : test relay DcDc + sensor");
    case 21:
        return F("SelfTest : relay inverter fail");
    case 22:
        return F("SelfTest timeout fail");
    case 23:
        return F("SelfTest : relay DcDc fail");
    case 24:
        return F("Self Test 1");
    case 25:
        return F("Waiting self test start");
    case 26:
        return F("Dc Injection");
    case 27:
        return F("Self Test 2");
    case 28:
        return F("Self Test 3");
    case 29:
        return F("Self Test 4");
    case 30:
        return F("Internal Error");
    case 31:
        return F("Internal Error");
    case 40:
        return F("Forbidden State");
    case 41:
        return F("Input UC");
    case 42:
        return F("Zero Power");
    case 43:
        return F("Grid Not Present");
    case 44:
        return F("Waiting Start");
    case 45:
        return F("MPPT");
    case 46:
        return F("Grid Fail");
    case 47:
        return F("Input OC");
    default:
        return F("Unknown");
    }
}

String ABBAuroraStrings::AlarmState(byte id)
{
    switch (id)
    {
    case 0:
        return F("No Alarm");
    case 1:
        return F("Sun Low");
    case 2:
        return F("Input OC");
    case 3:
        return F("Input UV");
    case 4:
        return F("Input OV");
    case 5:
        return F("Sun Low");
    case 6:
        return F("No Parameters");
    case 7:
        return F("Bulk OV");
    case 8:
        return F("Comm.Error");
    case 9:
        return F("Output OC");
    case 10:
        return F("IGBT Sat");
    case 11:
        return F("Bulk UV");
    case 12:
        return F("Internal error");
    case 13:
        return F("Grid Fail");
    case 14:
        return F("Bulk Low");
    case 15:
        return F("Ramp Fail");
    case 16:
        return F("Dc / Dc Fail");
    case 17:
        return F("Wrong Mode");
    case 18:
        return F("Ground Fault");
    case 19:
        return F("Over Temp.");
    case 20:
        return F("Bulk Cap Fail");
    case 21:
        return F("Inverter Fail");
    case 22:
        return F("Start Timeout");
    case 23:
        return F("Ground Fault");
    case 24:
        return F("Degauss error");
    case 25:
        return F("Ileak sens.fail");
    case 26:
        return F("DcDc Fail");
    case 27:
        return F("Self Test Error 1");
    case 28:
        return F("Self Test Error 2");
    case 29:
        return F("Self Test Error 3");
    case 30:
        return F("Self Test Error 4");
    case 31:
        return F("DC inj error");
    case 32:
        return F("Grid OV");
    case 33:
        return F("Grid UV");
    case 34:
        return F("Grid OF");
    case 35:
        return F("Grid UF");
    case 36:
        return F("Z grid Hi");
    case 37:
        return F("Internal error");
    case 38:
        return F("Riso Low");
    case 39:
        return F("Vref Error");
    case 40:
        return F("Error Meas V");
    case 41:
        return F("Error Meas F");
    case 42:
        return F("Error Meas Z");
    case 43:
        return F("Error Meas Ileak");
    case 44:
        return F("Error Read V");
    case 45:
        return F("Error Read I");
    case 46:
        return F("Table fail");
    case 47:
        return F("Fan Fail");
    case 48:
        return F("UTH");
    case 49:
        return F("Interlock fail");
    case 50:
        return F("Remote Off");
    case 51:
        return F("Vout Avg errror");
    case 52:
        return F("Battery low");
    case 53:
        return F("Clk fail");
    case 54:
        return F("Input UC");
    case 55:
        return F("Zero Power");
    case 56:
        return F("Fan Stucked");
    case 57:
        return F("DC Switch Open");
    case 58:
        return F("Tras Switch Open");
    case 59:
        return F("AC Switch Open");
    case 60:
        return F("Bulk UV");
    case 61:
        return F("Autoexclusion");
    case 62:
        return F("Grid df / dt");
    case 63:
        return F("Den switch Open");
    case 64:
        return F("Jbox fail");
    default:
        return F("Unknown");
    }
}

String ABBAuroraStrings::VersionPart1(byte id)
{
    switch ((char)id)
    {
    case 'i':
        return F("Aurora 2 kW indoor");
    case 'o':
        return F("Aurora 2 kW outdoor");
    case 'I':
        return F("Aurora 3.6 kW indoor");
    case 'O':
        return F("Aurora 3.0 - 3.6 kW outdoor");
    case '5':
        return F("Aurora 5.0 kW outdoor");
    case '6':
        return F("Aurora 6 kW outdoor");
    case 'P':
        return F("3 - phase interface (3G74)");
    case 'C':
        return F("Aurora 50kW module");
    case '4':
        return F("Aurora 4.2kW new");
    case '3':
        return F("Aurora 3.6kW new");
    case '2':
        return F("Aurora 3.3kW new");
    case '1':
        return F("Aurora 3.0kW new");
    case 'D':
        return F("Aurora 12.0kW");
    case 'X':
        return F("Aurora 10.0kW");
    default:
        return F("Unknown");
    }
}

String ABBAuroraStrings::VersionPart2(byte id)
{
    switch ((char)id)
    {
    case 'A':
        return F("UL1741");
    case 'E':
        return F("VDE0126");
    case 'S':
        return F("DR 1663 / 2000");
    case 'I':
        return F("ENEL DK 5950");
    case 'U':
        return F("UK G83");
    case 'K':
        return F("AS 4777");
    default:
        return F("Unknown");
    }
}

String ABBAuroraStrings::VersionPart3(byte id)
{

    switch ((char)id)
    {
    case 'N':
        return F("Transformerless Version");
    case 'T':
        return F("Transformer Version");
    default:
        return F("Unknown");
    }
}
String ABBAuroraStrings::VersionPart4(byte id)
{
    switch ((char)id)
    {
    case 'W':
        return F("Wind version");
    case 'N':
        return F("PV version");
    default:
        return F("Unknown");
    }
}