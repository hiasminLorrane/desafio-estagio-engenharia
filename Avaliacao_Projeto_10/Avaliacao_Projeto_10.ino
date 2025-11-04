#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

float temperatura = 25.0; 
float pressao = 1013.25; 
bool sending = true;


const int LED_STATUS = 2;          
const unsigned long INTERVAL = 2000; 
unsigned long lastSend = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_STATUS, OUTPUT);
  digitalWrite(LED_STATUS, LOW);

  if (!SerialBT.begin("ESP32_Monitor")) {
    Serial.println("⚠️ Erro ao iniciar Bluetooth!");
    while (true);
  }

  Serial.println("🔥 Sistema de Monitoramento iniciado (modo simulado)");
  Serial.println("📡 Bluetooth: ESP32_Monitor pronto para conexão!");
  randomSeed(esp_random());
}

void loop() {
  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil('\n');
    cmd.trim();
    if (cmd.equalsIgnoreCase("STOP")) {
      sending = false;
      Serial.println("🛑 Envio pausado via comando remoto");
    }
    if (cmd.equalsIgnoreCase("START")) {
      sending = true;
      Serial.println("▶️ Envio retomado via comando remoto");
    }
  }

  // ----- Envio periódico -----
  if (sending && (millis() - lastSend >= INTERVAL)) {
    lastSend = millis();

    // Simula leitura dos sensores com variação suave
    temperatura += random(-2, 3) * 0.1;
    pressao += random(-2, 3) * 0.1;

    // Mantém valores dentro de faixas realistas
    if (temperatura < 20.0) temperatura = 20.0;
    if (temperatura > 30.0) temperatura = 30.0;
    if (pressao < 1010.0) pressao = 1010.0;
    if (pressao > 1016.0) pressao = 1016.0;

    // Cria mensagem JSON
    String msg = "{\"temp\":" + String(temperatura, 2) + ",\"press\":" + String(pressao, 2) + "}";

    // Envia via Serial e Bluetooth
    Serial.println(msg);
    if (SerialBT.hasClient()) SerialBT.println(msg);
    

    // Pisca LED indicando envio
    digitalWrite(LED_STATUS, HIGH);
    delay(50);
    digitalWrite(LED_STATUS, LOW);
  }
}
