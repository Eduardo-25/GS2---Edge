# GS2-Edge

Monitoramento de Temperatura, Umidade e Poeira com ESP32
Este projeto utiliza um ESP32 para monitorar temperatura, umidade e poeira em tempo real, publicando os dados coletados em um broker MQTT. Ele também ativa um LED de alerta em caso de condições anormais, como temperaturas fora da faixa de segurança (0°C a 40°C) ou níveis elevados de poeira.

# Descrição
O projeto foi projetado para cenários de monitoramento ambiental, como estufas, laboratórios ou ambientes industriais. Ele emprega:

• Sensor DHT22: Para leitura de temperatura e umidade.
• Potenciômetro: Simulando medições de poeira em g/m³.
• MQTT: Para envio dos dados e alertas a um broker, permitindo integração com dashboards ou outras aplicações.
• LED de Alerta: Indica visualmente quando há condições anormais de temperatura ou poeira.
Regras de Alerta:
1.Temperatura Alta: Acima de 40°C.
2.Temperatura Baixa: Abaixo de 0°C.
3.Nível de Poeira Elevado: Acima de 10 g/m³.
4.O LED permanecerá ligado enquanto qualquer alerta persistir.

# Utilidades
• Monitoramento Ambiental: Acompanhe as condições de temperatura, umidade e qualidade do ar em tempo real.
• Automação Residencial ou Industrial: Integre o sistema a aplicações IoT através do MQTT.
• Notificações de Alerta: Identifique rapidamente condições ambientais fora do padrão.

# Instruções de Uso
1.Montagem do Circuito:

• Conecte o DHT22 ao pino 15 do ESP32.
• Conecte o potenciômetro ao pino analógico 34 do ESP32.
• Conecte o LED ao pino digital 2 (com resistor de 220Ω para proteção).
2.Configuração de Rede:

• Substitua as variáveis ssid e password pelas credenciais do seu Wi-Fi.
3.Subir o Código:

• Carregue o código no ESP32 usando o Arduino IDE.
4.Monitorar Dados:

• Use um cliente MQTT (como MQTT Explorer) para se inscrever nos tópicos:
  • monitoramento/temperatura: Temperatura em °C.
  • monitoramento/umidade: Umidade em %.
  • monitoramento/poeira: Poeira em g/m³.
  • monitoramento/alertas: Alertas emitidos pelo sistema.
# Requisitos e Dependências
Hardware:
• ESP32 (ou equivalente com suporte a Wi-Fi e pinos analógicos/digitais).
• DHT22 (Sensor de Temperatura e Umidade).
• Potenciômetro (Simulando poeira).
• LED e resistor de 220Ω.
Software:
• Arduino IDE (ou plataforma equivalente).
Bibliotecas:
• WiFi.h: Conexão à rede Wi-Fi.
• PubSubClient.h: Comunicação MQTT.
• DHT.h: Leitura do sensor DHT22.
Tópicos MQTT:
• monitoramento/temperatura: Publica a temperatura atual.
• monitoramento/umidade: Publica a umidade atual.
• monitoramento/poeira: Publica o nível de poeira em g/m³.
• monitoramento/alertas: Publica mensagens de alerta.

link wokwi:https://wokwi.com/projects/415279047085187073

Eduardo da Silva Lima - 554804
