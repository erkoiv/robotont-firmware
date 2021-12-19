#include "mbed.h"

float sensitivity = 0.0363, current, rawVoltage, batMax = 16.8, batMin = 14.8, stepdownRatio = 16.8/1.8263, ref = 3.29;
// Sensitivity of ACS711 +-25A model at 5V is 0.055V, which was recalculated to correspond to 3.3V reference with formula 0.055*(3.3/5)=0.0363
// Battery max and min were taken as healthy operation range of two volts above nominal
// Stepdown ratio corresponds to the mulitplier by which the measured voltage value is smaller than the real battery voltage
// Ref is the self-reported voltage at which the on-board ADC of the Nucleo runs


// In both functions 1.654 is subtracted from the read value, because for some unknown reason the Nucleo ADC reads 1.654 even when no voltage is being applied
float readCurrent(uint16_t readValue)
{
    rawVoltage = ((float) readValue * ref / 65535)-1.654;
    current = rawVoltage/sensitivity;
    if (rawVoltage < 0.005)
    {
        current = 0.0;
    }
    return current;
    
}

float batteryVoltage(uint16_t ADCv)
{
    float raw = ((((float) ADCv * ref / 65535))-1.654)*1.0125*2; // 1.0125 multiplier is for the 1.25% real error of the ADC, multiplier 2 is there because only then is the final result correct
    float batV = (raw*stepdownRatio);

    return batV;
}
