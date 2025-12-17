#include <Arduino.h>
#include "ADC.h"

#if !defined(Serial) && defined(USB_SERIAL)
#define Serial USB_SERIAL
#endif


// put function declarations here:
const int ADC_PIN = 4;
const int LED_PIN = 13;
const int REF_PIN = 5;
ADC adc_pin(ADC_PIN, REF_PIN);


void setup() {

  // 1. Attendre que le port série soit physiquement prêt (indispensable sur ESP32-S3/C3)
  while (!Serial) {
    delay(10); 
  }

  // 2. Petit délai supplémentaire pour laisser le temps au logiciel 
  // sur votre PC (Serial Monitor) de se stabiliser
  delay(1000);


  Serial.begin(115200);
  adc_pin.begin();
  
  Serial.println("Hello from Port 01!");
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}


void loop() {


  adc_pin.update();
  float tension = adc_pin.convert_ADC();
  Serial.print("tension = ");
  Serial.println(tension);


  delay(500);
  

}