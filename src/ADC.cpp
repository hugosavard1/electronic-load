#include <ADC.h>
#include <Arduino.h>

//instanciate object
ADC::ADC(int adc, int ref) : _pin(adc), _ref(ref) ,  _lastValue(0) {
}

void ADC::begin() {
    pinMode(_pin, INPUT);
    analogReadResolution(13);
    analogSetAttenuation(ADC_11db);
    Serial.println("success instanciating");
    Serial.println(_pin);

}

float ADC::convert_ADC() {
    
    //Serial.print("tension ref =");
    //Serial.println(_lastref);



    //Serial.print("tension bit =");
    //Serial.println(_lastValue);

    float mv_per_bit = 1247.0f / (float)_lastref; // mv per bit
    //Serial.print("mv_per_bit =");
    //Serial.println(mv_per_bit, 7);
    //Serial.print("tension lu pin 4 =");
    //Serial.println(_lastValue*mv_per_bit);
    //Serial.print("tension lu pin 5 =");
    //Serial.println(_lastref);
    //Serial.print("rapport");
    //Serial.println(_rapport, 7);
    //Serial.print("mv_per_bit =");
    //Serial.println(mv_per_bit);
    //Serial.print("_rapport =");
    //Serial.println(_rapport, 7);

    //pont avec V -> 100k -> probe -> 5k1 -> GND
    //60V

    float tension_lu = ((_lastValue * mv_per_bit)*0.9803f + 22.255f);
    float tension_mili = (tension_lu/_rapport);
    float tension = tension_mili/1000.0f;
    
    
    //for conversion see excel file
    //return ((tension * 0.9797f) + 0.2469f); //for 10000 * 1000
    
    //return ((tension*0.9799) + 0.4458); //for 20000 * 1000
    return tension_lu/1000;
}

//void ADC::update() {
//    if (millis() - _lastUpdate >= _interval) {
//        _lastValue = analogRead(_pin);
//        _lastref = analogRead(_ref);
//        _lastUpdate = millis();
//    }
//}

void ADC::update() {
    if (millis() - _lastUpdate >= _interval) {
        long sumValue = 0;
        long sumRef = 0;
        int numSamples = 150; // On lit 64 fois

        for(int i = 0; i < numSamples; i++) {
            sumValue += analogRead(_pin);
            sumRef += analogRead(_ref);
        }

        _lastValue = (float)sumValue / numSamples;
        _lastref = (float)sumRef / numSamples;
        _lastUpdate = millis();
    }
}
