/*
 * SERVIÇO MOTOR GIRANDO CONTINUAMENTE
 * Código para servo comum (0° a 180°)
 * 
 * Conexões:
 * - Vermelho -> 5V
 * - Marrom/Preto -> GND
 * - Laranja/Amarelo -> Pino 9
 */

#include <Servo.h>
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

Servo meuServo;
const int pinoServo = 10;

// Configurações ajustáveis
int velocidade = 10;  // Quanto menor, mais rápido (ms)
int angulo = 0;
bool subindo = true;

void setup() {
  meuServo.attach(pinoServo);
  Serial.begin(9600);
  Serial.println("Servo girando continuamente!");
  Serial.println("Comandos:");
  Serial.println("  + : Aumentar velocidade");
  Serial.println("  - : Diminuir velocidade");
  Serial.println("  numero (1-9) : Definir velocidade");
  Serial.println("  p : Parar");
  Serial.println("  r : Recomeçar");

  
  for (int btn = 2; btn <= 8; btn++ ) {
    pinMode(btn, INPUT_PULLUP);
  }
  Serial.println("Sistema iniciado. Pressione um botao...");


}

void loop() {
  // Controle via Serial Monitor
  if (Serial.available()) {
    char cmd = Serial.read();
    
    switch(cmd) {
      case '+':
        if (velocidade > 1) {
          velocidade--;
          Serial.print("Velocidade aumentada: ");
          Serial.println(velocidade);
        }
        break;
        
      case '-':
        if (velocidade < 50) {
          velocidade++;
          Serial.print("Velocidade diminuída: ");
          Serial.println(velocidade);
        }
        break;
        
      case 'p':
        Serial.println("MOTOR PARADO!");
        while (!Serial.available()) {
          delay(100);  // Aguarda comando
        }
        Serial.read(); // Limpa buffer
        Serial.println("Continuando...");
        break;
        
      case 'r':
        angulo = 0;
        subindo = true;
        Serial.println("Reiniciando...");
        break;
        
      default:
        if (cmd >= '1' && cmd <= '9') {
          velocidade = 11 - (cmd - '0');  // 1=mais rápido, 9=mais lento
          Serial.print("Velocidade: ");
          Serial.println(velocidade);
        }
        break;
    }
  }
  
  // Movimento contínuo do servo
  if (subindo) {
    angulo++;
    meuServo.write(angulo);
    
    if (angulo >= 180) {
      subindo = false;
      delay(50);  // Pequena pausa na virada
    }
  } else {
    angulo--;
    meuServo.write(angulo);
    
    if (angulo <= 0) {
      subindo = true;
      delay(50);  // Pequena pausa na virada
    }
  }
  
  delay(velocidade);


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