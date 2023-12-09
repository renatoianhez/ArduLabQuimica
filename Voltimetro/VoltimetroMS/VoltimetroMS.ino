#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);
int16_t adc0;
int16_t adc1;
const float FatorConversao = 0.0001875f;
float volt1, volt2;

void setup(void) {
  Serial.begin(9600);
  ads.begin();
}

void loop(void) {
  adc0 = ads.readADC_SingleEnded(0);
  volt1 = (adc0 * FatorConversao) - 2.35;
  adc1 = ads.readADC_SingleEnded(1);
  volt2 = (adc1 * FatorConversao) - 2.35;
  Serial.print("\tTensao 1: ");
  Serial.print(volt1);
  Serial.print(" V");
  Serial.print("\tTensao 2: ");
  Serial.print(volt2);
  Serial.println(" V");
  delay(1000);
}
