/*
  Colégio Estadual Gabriel de Lara - 22/04/2026
  Autor: Kiel Grobe de Miranda

  Aula 1o

  Objetivo: Estudar o funcionamento do Joystick Shield
*/

//não alterar o número das portas
#define botaoA 2
#define botaoB 3
#define botaoC 4
#define botaoD 5
#define botaoE 6
#define botaoF 7
#define botaoK 8
// mapeamento dos eixos X e Y (0 a 1023)
#define eixoX A0
#define eixoY A1

void setup() {
  for (int btn = 2; btn <= 8; btn++ ) {
    pinMode(btn, INPUT_PULLUP);
  }
  Serial.begin(9600);
  Serial.println("Sistema iniciado. Pressione um botao...");
}

void loop() {
  // leitura dos valores analógicos de 0 a 1023
  int valorX = analogRead(eixoX);
  int valorY = analogRead(eixoY);
  int t = digitalRead(botaoA);
  int o = digitalRead(botaoB);
  int x = digitalRead(botaoC);
  int q = digitalRead(botaoD);
  int start = digitalRead(botaoE);
  int select = digitalRead(botaoF);
  int L3 = digitalRead(botaoK);

  // exibir no monitor serial
  Serial.print("X: ");
  Serial.print(valorX);
  Serial.print(" | Y");
  Serial.println(valorY);

  //Ação
  if (valorX > 600) { Serial.println("Movendo para a DIREITA");}
  if (valorX < 450) { Serial.println("Movendo para a ESQUERDA");}
  if (valorY > 600) { Serial.println("Movendo para CIMA");}
  if (valorY < 450) { Serial.println("Movendo para BAIXO");}

  delay(400);

  //verificar cada botão.Como usamos INPUT_PULLUP então LOW significa pressionando
  if (t == LOW ) {
    Serial.println ("Triangulo pressionado");
    delay(200);
  }
  if (o == LOW ) {
    Serial.println ("Bolinha pressionado");
    delay(200);
  }
  if (x == LOW ) {
    Serial.println ("Xis pressionado");
    delay(200);
  }
  if (q == LOW ) {
    Serial.println ("Quadrado pressionado");
    delay(200);
  }
  if (start == LOW ) {
    Serial.println ("Start pressionado");
    delay(200);
  }
  if (select == LOW ) {
    Serial.println ("Select pressionado");
    delay(200);
  }
  if (L3 == LOW ) {
    Serial.println ("L3 pressionado");
    delay(200);
  }

}
