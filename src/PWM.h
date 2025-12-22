#ifndef PWM_H
#define PWM_H


class PWM {


public:
    PWM(int pin, int canal, int resolution, int frequency);
    int Ajuster_Tension(float tension_value);
private:
    int _pin;
    int _resolution = 10;
    int _frequency;
    int _canal;
    int _max_value;
};


#endif