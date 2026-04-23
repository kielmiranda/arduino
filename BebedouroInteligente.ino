/*
 * PROJETO: BEBEDOURO INTELIGENTE ACESSÍVEL
 * AUTORES: Kiel Grobe de Miranda 25; Renan 34
 * OBJETIVO: Acionar válvula solenoide automaticamente via sensor de proximidade.
 * LÓGICA: Se distância < LIMITE (10 cm), relé é ATIVADO (água liberada).
 *         Caso contrário, relé DESATIVADO.
 */

// --- DEFINIÇÃO DE PINOS ---
#define TRIG_PIN   9      // Pino de disparo do ultrassom
#define ECHO_PIN   10     // Pino de eco do ultrassom
#define RELE_PIN   7      // Pino de controle do relé

// --- CONSTANTES DE OPERAÇÃO ---
#define DISTANCIA_ACIONAMENTO  10   // Distância em cm que dispara a água
#define TEMPO_LEITURA          200  // Intervalo entre medições (ms)
#define NUM_AMOSTRAS           5    // Amostras para filtro de média móvel

// --- VARIÁVEIS GLOBAIS ---
unsigned long ultimoTempo = 0;
bool estadoValvula = false;        // false = fechada, true = aberta

// =============================================
// FUNÇÃO: medirDistancia()
// Retorna a distância medida em centímetros.
// Usa média móvel para reduzir ruídos.
// =============================================
float medirDistancia() {
  long somaDistancias = 0;
  int leiturasValidas = 0;

  for (int i = 0; i < NUM_AMOSTRAS; i++) {
    // Gera pulso de 10us no TRIG
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Mede duração do pulso ECHO
    long duracao = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms (~5m)

    if (duracao > 0) {
      // Conversão para cm: distância = duração * 0.034 / 2
      float distancia = duracao * 0.017;
      
      // Filtra valores absurdos (fora do alcance prático do sensor)
      if (distancia > 2.0 && distancia < 400.0) {
        somaDistancias += distancia;
        leiturasValidas++;
      }
    }
    delay(5); // Pequena pausa entre amostras
  }

  // Retorna média se houve pelo menos metade das amostras válidas
  if (leiturasValidas >= NUM_AMOSTRAS / 2) {
    return (float)somaDistancias / leiturasValidas;
  } else {
    return 999.0; // Valor de erro (objeto muito longe ou falha)
  }
}

// =============================================
// FUNÇÃO: controlarValvula()
// Ativa ou desativa o relé com base na distância medida.
// =============================================
void controlarValvula(float distancia) {
  if (distancia > 0 && distancia < DISTANCIA_ACIONAMENTO) {
    // Objeto detectado dentro da zona de acionamento
    if (!estadoValvula) {
      digitalWrite(RELE_PIN, LOW);  // Relé LOW = ligado (módulo típico)
      estadoValvula = true;
      Serial.println(">> AGUA LIBERADA <<");
    }
  } else {
    // Nenhum objeto ou fora da zona
    if (estadoValvula) {
      digitalWrite(RELE_PIN, HIGH); // Relé HIGH = desligado
      estadoValvula = false;
      Serial.println(">> VALVULA FECHADA <<");
    }
  }
}

// =============================================
// SETUP: Inicialização do sistema
// =============================================
void setup() {
  // Configura pinos
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELE_PIN, OUTPUT);

  // Garante que o relé inicie DESLIGADO
  digitalWrite(RELE_PIN, HIGH); // Módulo ativo em LOW, HIGH = desligado
  estadoValvula = false;

  // Inicia comunicação serial para depuração
  Serial.begin(9600);
  Serial.println("=== BEBEDOURO INTELIGENTE INICIADO ===");
  Serial.print("Distancia de acionamento: ");
  Serial.print(DISTANCIA_ACIONAMENTO);
  Serial.println(" cm");
  Serial.println("----------------------------------------");
}

// =============================================
// LOOP PRINCIPAL
// =============================================
void loop() {
  // Controle de tempo para leituras periódicas (não bloqueante)
  unsigned long tempoAtual = millis();
  
  if (tempoAtual - ultimoTempo >= TEMPO_LEITURA) {
    ultimoTempo = tempoAtual;

    // 1. Mede distância com filtro
    float distancia = medirDistancia();

    // 2. Exibe no Monitor Serial (opcional, remover em produção)
    if (distancia < 400.0) {
      Serial.print("Distancia: ");
      Serial.print(distancia);
      Serial.println(" cm");
    } else {
      Serial.println("Distancia: Fora de alcance");
    }

    // 3. Controla a válvula conforme distância
    controlarValvula(distancia);
  }

  // Outras tarefas podem ser executadas aqui sem bloquear o loop
}