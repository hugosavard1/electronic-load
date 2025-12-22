#include "PWM.h"
#include "Arduino.h"
#include <cmath>



PWM::PWM(int pin, int canal, int resolution, int frequency) : _pin(pin), _resolution(resolution),
                                                            _canal(canal), _frequency(frequency),
                                                            _max_value(pow(2, resolution)) {
    //resolution 12bit valeur entre 0 et 4095 


    ledcSetup(_canal, _frequency, _resolution);
    ledcAttachPin(_pin, _canal);

}


int PWM::Ajuster_Tension(float value) {
    
float tension_max = 3.285;
    if (value > tension_max || value < 0) {
        ledcWrite(_canal, 0);
        return 0;
    }


    float _rapport = value / tension_max;
    //Serial.print("_rapport pwm = ");
    //Serial.println(_rapport);
    ledcWrite(_canal, (int)(_rapport * (_max_value - 1)));
    return 1;

}