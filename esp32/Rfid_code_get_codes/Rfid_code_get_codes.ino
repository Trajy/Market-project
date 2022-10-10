#include <SoftwareSerial.h>
SoftwareSerial RFID(5,4); // RX and TX

String text;

void setup()
{
  Serial.begin(9600);
  RFID.begin(9600);
  Serial.println("Aproxime a TAG ao Leitor."); 
}
char c;

void loop()
{
  while (RFID.available() > 0) {
    delay(5);
    c = RFID.read();
    text += c;
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
