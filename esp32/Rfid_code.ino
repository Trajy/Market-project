//#include <SoftwareSerial.h>
#include <RDM6300.h>

#define LED LED_BUILTIN

SoftwareSerial Rfid(2, 3); // Inicializa a serial nos pinos 2 (RX) e 3 (TX)
uint8_t Payload[6]; // array para armazenar a tag lida
RDM6300 Rdm6300(Payload); // objedo para tratar os dados lidos

void setup() {
  pinMode(LED, OUTPUT); // define o pino do led como saida, para sinalizar leituras
  Rfid.begin(115200); // Inicializa a serial para o leitor RDM6300
  Serial.begin(115200); // Inicializa a serial para comunicacao com o PC
  Serial.println("Leitor RFID RDM6300"); // Informacoes iniciais
}

void loop() {
  while (Rfid.available() > 0) { //Aguarda a aproximacao da tag RFID
    digitalWrite(LED, HIGH); // acende o led para sinalizar leitura
    uint8_t data = Rfid.read();
    if (Rdm6300.decode(data)) {
      Serial.print("ID TAG: ");
      for (int i = 0; i < 5; i++) {
        Serial.print(Payload[i], HEX); // exibe os dados no monitor serial
        Serial.println(" \n");
      }
    }
    digitalWrite(LED, LOW); // apaga o led para sinalizar que nao a leitura
  }
  delay(100); // aguarda para realizar uma nova verificacao
}
