#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Configurações da rede WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configurações do Broker MQTT
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

// Configuração do DHT22
#define DHTPIN 15      // Pino de dados do DHT22
#define DHTTYPE DHT22  // Modelo do sensor DHT22
DHT dht(DHTPIN, DHTTYPE);

// Configuração do potenciômetro (simulando poeira)
#define LDR_PIN 34 // Pino conectado ao potenciômetro (poeira)

// Configuração do LED de alerta
#define LEDPIN 2 // Pino conectado ao LED de alerta (saída digital)

WiFiClient espClient;
PubSubClient client(espClient);

// Função para reconectar ao broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.println("Tentando conectar ao broker MQTT...");
    if (client.connect("mqtt-explorer-272ff78e")) {
      Serial.println("Conectado ao broker MQTT!");
    } else {
      Serial.print("Falha na conexão. Código: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Configuração do LED como saída digital
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);

  // Inicialização do sensor DHT22
  dht.begin();
  delay(2000);

  // Conectar ao WiFi
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");

  // Configurar o MQTT
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  // Verifica e reconecta ao MQTT, se necessário
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Ler dados do DHT22
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  
  // Ler valor do potenciômetro (simulando poeira em g/m³)
  int ldrValue = analogRead(LDR_PIN);
  float poeira = (ldrValue / 4095.0) * 50.0; // Escala para valores entre 0 e 50 g/m³

  bool alerta = false; // Variável para controlar o estado do LED

  if (!isnan(temperatura) && !isnan(umidade)) {
    // Publicar temperatura no MQTT
    char tempString[8];
    dtostrf(temperatura, 1, 2, tempString);
    client.publish("monitoramento/temperatura", tempString);
    Serial.printf("Temperatura: %.2f °C\n", temperatura);

    // Publicar umidade no MQTT
    char humString[8];
    dtostrf(umidade, 1, 2, humString);
    client.publish("monitoramento/umidade", humString);
    Serial.printf("Umidade: %.2f %%\n", umidade);

    // Publicar poeira no MQTT
    char dustString[8];
    dtostrf(poeira, 1, 2, dustString);
    client.publish("monitoramento/poeira", dustString);
    Serial.printf("Poeira: %.2f g/m³\n", poeira);

    // Verificar e emitir alertas de temperatura
    if (temperatura > 40.0) {
      client.publish("monitoramento/alertas", "ALERTA: Temperatura alta!");
      Serial.println("ALERTA: Temperatura alta!");
      alerta = true;
    } else if (temperatura < 0.0) {
      client.publish("monitoramento/alertas", "ALERTA: Temperatura baixa!");
      Serial.println("ALERTA: Temperatura baixa!");
      alerta = true;
    }

    // Verificar e emitir alertas de poeira
    if (poeira > 10.0) {
      client.publish("monitoramento/alertas", "ALERTA: Poeira acima do limite!");
      Serial.println("ALERTA: Poeira acima do limite!");
      alerta = true;
    }

    // Controle do LED de alerta
    if (alerta) {
      digitalWrite(LEDPIN, HIGH); // Ativar LED se houver alerta
    } else {
      digitalWrite(LEDPIN, LOW); // Desativar LED se não houver alerta
    }
  } else {
    // Erro ao ler os dados do DHT22
    Serial.println("Erro ao ler os dados do DHT22.");
  }

  // Atraso de 2 segundos antes da próxima leitura
  delay(2000);
}
