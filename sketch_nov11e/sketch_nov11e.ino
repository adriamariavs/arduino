#include <SPI.h>
#include <Ethernet.h>

#define LED 13 

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetServer server(80);

void setup() {
  Ethernet.begin(mac);
  server.begin();
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(10, LOW);
  Serial.print("Servidor inicializado: IP ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Novo cliente!");
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        if (request.indexOf("/ligar1") != -1) {
          digitalWrite(LED, HIGH);
        } else if (request.indexOf("/desligar1") != -1) {
          digitalWrite(LED, LOW);
        } else if (request.indexOf("/ligar2") != -1) {
          digitalWrite(10, HIGH);
        } else if (request.indexOf("/desligar2") != -1) {
          digitalWrite(10, LOW);
        }
      }
    }
    client.stop();
  }
}