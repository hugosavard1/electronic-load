#ifndef ADC_H
#define ADC_H


class ADC {


public:
    int getValue();
    float convert_ADC();
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

    //pont diviseur
    float _grosse_res = 20130;
    float _petit_res = 1000;
    float _rapport = _petit_res/(_petit_res + _grosse_res);
};


#endif