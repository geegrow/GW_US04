#include <GW_US04.h>

#define TRIG_PIN    2
#define ECHO_PIN    5
#define I2C_ADDR    14


/* 2 способа подключения (trig-echo и i2c). Для каждого исп. свой конструктор */
//GW_US04 sonar = GW_US04(TRIG_PIN, ECHO_PIN);
GW_US04 sonar = GW_US04(I2C_ADDR);

void setup() {
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  Serial.println(sonar.scan());
  delay(100);
}
