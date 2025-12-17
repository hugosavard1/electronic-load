#ifndef ADC_H
#define ADC_H


class ADC {


public:
    int getValue();
    int convert_ADC();
    void update();
    ADC(int adc, int ref);
    void begin();

private:
    int _ref;
    int _pin;
    float _lastValue;
    float _lastref;
    int _lastUpdate;
    int _interval = 10;
};


#endif