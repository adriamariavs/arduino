#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetServer server(80);
void setup() {
  Ethernet.begin(mac);
  server.begin();
  Serial.begin(9600);
  Serial.println("Servidor inicializado");
}
void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Novo cliente!");
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // Verifica se a requisição é para um endpoint específico
        if (c == 'A') {
          // Responde com uma mensagem específica do endpoint A
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/plain");
          client.println();
          client.println("Resposta do Endpoint A");
        } else if (c == 'B') {
          // Responde com uma mensagem específica do endpoint B
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/plain");
          client.println();
          client.println("Resposta do Endpoint B");
        }
      }
    }
    client.stop();
  }
}