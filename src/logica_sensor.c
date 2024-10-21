#include "DHT.h"

// Definindo pinos para os sensores e o LED
#define DHTPIN 4          // Pino conectado ao DHT22
#define DHTTYPE DHT22     // Tipo de sensor DHT
#define TRIG_PIN 5        // Pino Trigger do HC-SR04
#define ECHO_PIN 18       // Pino Echo do HC-SR04
#define PIR_PIN 27        // Pino do sensor PIR
#define LDR_AO_PIN 34     // Pino ADC para a leitura analógica do LDR
#define LED_PIN 2         // Pino do LED (simulando o sistema de irrigação)

// ===== Definições de Thresholds =====
#define UMIDADE_MINIMA 40         // Umidade mínima para ativar a irrigação (%)
#define NIVEL_AGUA_MINIMO 10      // Distância mínima para considerar o nível de água adequado (cm)
#define NIVEL_AGUA_MAXIMO 30      // Distância máxima para considerar o nível de água adequado (cm)
#define LDR_THRESHOLD_ENSOLARADO 1500  // Valor de LDR abaixo do qual consideramos que está ensolarado

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  // Inicializa sensores
  dht.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("Sistema de Monitoramento Iniciado");
}

// Função para medir a distância com o HC-SR04
float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.034) / 2;
  return distance;
}

void loop() {
  // ===== Monitoramento Climático (DHT22) =====
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Erro na leitura do DHT22");
    delay(2000);  // Pausa de 2 segundos entre leituras
    return;
  }

  // ===== Controle de Nível de Água (HC-SR04) =====
  float distance = measureDistance();
  Serial.print("Nível de água no tanque: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > NIVEL_AGUA_MAXIMO) {
    Serial.println("Nível de água excede o máximo permitido");
    // Não desliga a irrigação aqui, mas emite o aviso.
  }

  // ===== Leitura da Luminosidade (LDR) =====
  int ldrValue = analogRead(LDR_AO_PIN);
  Serial.print("Intensidade de luz (LDR): ");
  Serial.println(ldrValue);

  // ===== Detecção de Movimento (PIR) =====
  int pirState = digitalRead(PIR_PIN);
  if (pirState == HIGH) {
    Serial.println("Movimento detectado! Irrigação desativada.");
    digitalWrite(LED_PIN, LOW);  // Desliga a irrigação
    delay(2000);
    return;
  }

  // ===== Condições para DESLIGAR a irrigação =====
  if (humidity >= UMIDADE_MINIMA) {
    Serial.println("Umidade acima do mínimo, desativando irrigação.");
    digitalWrite(LED_PIN, LOW);  // Desliga a irrigação
    delay(2000);
    return;
  }

  if (distance < NIVEL_AGUA_MINIMO) {
    Serial.println("Nível de água abaixo do mínimo, desativando irrigação.");
    digitalWrite(LED_PIN, LOW);  // Desliga a irrigação
    delay(2000);
    return;
  }

  if (ldrValue >= LDR_THRESHOLD_ENSOLARADO) {
    Serial.println("Dia nublado (pouca luz), desativando irrigação.");
    digitalWrite(LED_PIN, LOW);  // Desliga a irrigação
    delay(2000);
    return;
  }

  if (humidity < UMIDADE_MINIMA && distance < NIVEL_AGUA_MINIMO) {
    Serial.println("Umidade e nível de água abaixo do mínimo, desativando irrigação.");
    digitalWrite(LED_PIN, LOW);  // Desliga a irrigação
    delay(2000);
    return;
  }

  // ===== Condições para LIGAR a irrigação =====
  if (humidity < UMIDADE_MINIMA && distance >= NIVEL_AGUA_MINIMO && ldrValue < LDR_THRESHOLD_ENSOLARADO) {
    Serial.println("Condições adequadas, ativando irrigação.");
    digitalWrite(LED_PIN, HIGH);  // Liga a irrigação
  }

  delay(2000);  // Pausa de 2 segundos entre leituras
}
