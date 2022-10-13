#include <SoftwareSerial.h>
SoftwareSerial RFID(4,2); // RX and TX

String text;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
  RFID.begin(9600);
  Serial.println("Aproxime a TAG ao Leitor.");
  digitalWrite(LED_BUILTIN, LOW);
}
char c;

void loop()
{
  while (RFID.available() > 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(5);
    c = RFID.read();
    text += c;
    digitalWrite(LED_BUILTIN, LOW);
  }
  if (text.length() > 11)
  check();
  text = "";
}

void check()
{
  text = text.substring(1, 11);
  Serial.println("TAG ID : " + text);
}
