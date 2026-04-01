/* Aula 08 - Sensor de Distância com LCD-I2C - 01/04/2026
   
   Autor: Kiel Grobe de Miranda
 */

/* Inclui a biblioteca do sensor */
#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

/* Definições das portas utilizadas                         */

#define buzzer 8

/* Defi ne os pinos para o sensor */
int pino_Trig = 2;
int pino_Echo = 3;
/* Especifi ca o nome e os pinos para o sensor */
Ultrasonic Sensor(pino_Trig, pino_Echo);
/* Variável que armazenará as medidas. */
int distancia;


void setup() {
  /* Inicializa a comunicação serial */
  Serial.begin(9600);

  lcd.init();
  /* Liga a luz de fundo do LCD                             */
  lcd.backlight();

  /* Configura os pinos dos botões como entrada PULLUP      */
  pinMode(botao_UP, INPUT_PULLUP);
  pinMode(botao_DOWN, INPUT_PULLUP);

  /* Configura o pino do buzzer como saída                  */
  pinMode(buzzer, OUTPUT);
}




void loop() {
  /* Realiza a medição e armazena na variável “distancia”
*/
  distancia = Sensor.read();

  

  if (distancia < 100) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distancia: ");
    lcd.setCursor(0, 1);
    lcd.print(distancia);
    lcd.setCursor(3, 1);
    lcd.print("Cm");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distancia: ");
    lcd.setCursor(0, 1);
    lcd.print(distancia);
    lcd.setCursor(4, 1);
    lcd.print("Cm");
  }


  /* Imprime no Monitor Serial os valores das medidas a
cada 0,5 segundos */
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println("cm");
  delay(500);
}