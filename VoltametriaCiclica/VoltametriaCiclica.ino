#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x4A); // Confira o endereco do ADC
Adafruit_MCP4725 dac;
int16_t adc0;
int16_t adc1;

void setup(void) {
  Serial.begin(115200); //Mude a velocidade no Monitor Serial
  dac.begin(0x62);
  ads.begin();
  Wire.setClock(400000);
}

void loop(void) {
  Serial.println("INICIO");
  Serial.println("TENSAO    CORRENTE");
  delay(1000);
  uint32_t VDAC = 750; //Inicio da varredura - mude o valor se quiser
  while (VDAC < 3500) //3500 representa a maxima tensao - mude se quiser
  {
    dac.setVoltage(VDAC, false);
    delayMicroseconds(5000);
    adc0 = ads.readADC_SingleEnded(0);
    adc1 = ads.readADC_SingleEnded(1);
    Serial.print(adc0);
    Serial.print("\t");
    Serial.println(adc1);
    VDAC = VDAC + 1; //incremento (rampa de subida de tensao)
  }
  VDAC = 3500;
  while (VDAC > 750)
  {
    dac.setVoltage(VDAC, false);
    delayMicroseconds(5000);
    adc0 = ads.readADC_SingleEnded(0);
    adc1 = ads.readADC_SingleEnded(1);
    Serial.print(adc0);
    Serial.print("\t");
    Serial.println(adc1);
    VDAC = VDAC - 1; //decremento (rampa de descida de tensao)
  }
  Serial.println("FIM------------------------");
  delay(5000);
}
