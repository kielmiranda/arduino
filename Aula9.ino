/*
  Colégio Estadual Gabriel de Lara - 15/04/2026
  Autor: Kiel Grobe de Miranda

  Objetivo: Estudar o funcionamento
*/

#include <MatrizLed.h>

MatrizLed Display;


void setup() {
  ////inicia o Display (DIN, CLK, qtd de matrizes)
  Display.begin(8, 10, 9, 1);
  //Intensida do brilho
  Display.setIntensidad(10);

}

void loop() {
  //limpa o display
  Display.borrar();

  //Controlar LEDs independentes
  //(n° de matriz, linha, coluna, estado)
  Display.setLed(0, 0, 0, HIGH);

  delay(1000);

}
