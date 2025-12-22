#include <Arduino.h>
#include "ADC.h"
#include "PWM.h"

#if !defined(Serial) && defined(USB_SERIAL)
#define Serial USB_SERIAL
#endif


// put function declarations here:
const int ADC_PIN = 4;
const int LED_PIN = 13;
const int REF_PIN = 5;
const int PWM_PIN = 37;
const int PWM_canal = 0;
const int PWM_resolution = 12;
const int PWM_FREQ = 5000;


ADC adc_pin(ADC_PIN, REF_PIN);
PWM pwm_pin(PWM_PIN, PWM_canal, PWM_resolution, PWM_FREQ);

int desired_tension = 0;

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

  Serial.print("Lecture ADC : ");
  Serial.print(tension, 7);
  Serial.println(" V");
// On vérifie si l'utilisateur a tapé quelque chose
  if (Serial.available() > 0) {
// On lit le nombre complet (ex: 1.25)
    float nouvelle_tension = Serial.parseFloat();
// On ignore le 0 si parseFloat ne trouve rien ou si on vide le buffer
    if (nouvelle_tension > 0) {
      desired_tension = nouvelle_tension;
      Serial.print("Nouvelle tension PWM : ");
      Serial.print(desired_tension);
      Serial.println(" V");
   }
  }
pwm_pin.Ajuster_Tension(desired_tension);
delay(500);

}