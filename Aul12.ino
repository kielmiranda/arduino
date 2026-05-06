/*
    Aula 12 - 06/05
    
    Objetivo: Estudar o comportamento do LED RGB
*/

#define led_R 11
#define led_G 9
#define led_B 10

#define pot_R A2
#define pot_G A1
#define pot_B A0


void setup () {
  pinMode(led_R, OUTPUT);
  pinMode(led_G, OUTPUT);
  pinMode(led_B, OUTPUT);
  pinMode(led_R, INPUT);
  pinMode(led_G, INPUT);
  pinMode(led_B, INPUT);
}

void loop () {
  //Lê os valores do pontenciaômetro (0 a 1023)
  int leituraR = analogRead(pot_R);
  int leituraG = analogRead(pot_G);
  int leituraB = analogRead(pot_B);
  //Converte para a escala do LED (0 a 255)
  int brilhoR = map(leituraR, 0, 1023, 0, 255);
  int brilhoG = map(leituraG, 0, 1023, 0, 255);
  int brilhoB = map(leituraB, 0, 1023, 0, 255);
  
  analogWrite(led_R, brilhoR);
  analogWrite(led_G, brilhoG);
  analogWrite(led_B, brilhoB);
}