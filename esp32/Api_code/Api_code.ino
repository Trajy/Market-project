#include <WiFi.h>
#include <SoftwareSerial.h>

#define ID_ARDUINO 4
#define TAG_PEDIDO_CANCELADO ""
#define TAG_PEDIDO_FINALIZADO "";
#define API_URL "https://market-api-tcc.herokuapp.com"

// Informe as credencias da sua rede wifi
const char* ssid = "";
const char* password = "";
HTTPClient http;
SoftwareSerial rfid(5,4); // (RX, TX)

void sendRequest(String body, String path) {
    //chama a api de inicio de pedido
    //verifica qual foi o ultimo pedido
    Serial.println("Call Api: " + API_URL + path);
    http.begin(API_URL + path);
    http.addHeader("Content-Type", "application/json");
    int statusCode = http.POST(body);
    if (statusCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String resposta = http.getString();
        Serial.println(resposta);
    }
    else {
        Serial.print("Error code: ");
        Serial.println(statusCode);
    }
}

String lerTag() {
    String tag = ""; 
    while (RFID.available() > 0) {
    delay(5);
      tag += RFID.read();
    }
    if (tag.length() > 11) {
      return tag;
    }
}

void setup() {
    pinMode (LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN))
    }
    Serial.println("Wifi conectado, IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    if(while (RFID.available() <= 0) {
      return;
    }
    String tag = lerTag();
    Serial.println("Tag : " + tag);
    String body;
    String path;
    if(tag == TAG_PEDIDO_FINALIZADO) {
        body = "{\"status\":\"FINALIZADO\"}";
        path = "/orders/"
    }
    else if(tag == TAG_PEDIDO_CANCELADO) {
      body = "{\"status\":\"CANCELADO\"}";
      path = "/orders/"
    }
    else {
        body = "{\"rfid\":\"" + tag + ",\"customer\":\"" + ID_ARDUINO + "\"}";
        path = "/items-orders/"
    }
    sendRequest(body, path);
    delay(1000);
}
