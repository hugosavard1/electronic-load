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

int ADC::convert_ADC() {
    
    Serial.print("tension ref =");
    Serial.println(_lastref);



    Serial.print("tension bit =");
    Serial.println(_lastValue);

    float mv_per_bit = 2500 / _lastref; // mv per bit

    Serial.print("mv_per_bit =");
    Serial.println(mv_per_bit);


    return _lastValue * mv_per_bit;
}

void ADC::update() {
    if (millis() - _lastUpdate >= _interval) {
        _lastValue = analogRead(_pin);
        _lastref = analogRead(_ref);
        _lastUpdate = millis();
    }
}

