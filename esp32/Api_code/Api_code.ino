#include <WiFi.h>
#include <HTTPClient.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define ID_ARDUINO 1
#define TAG_PEDIDO_CANCELADO String("3A007CDE0D")
#define TAG_PEDIDO_FINALIZADO String("3900805A05")
#define API_URL String("http://market-api-tcc.herokuapp.com")

// Informe as credencias da sua rede wifi
const char* ssid = "Mortadela 2.4";
const char* password = "7890048678900486";
String pedidoId;
HTTPClient http;
SoftwareSerial rfid(5,4); // (RX, TX)
DynamicJsonDocument doc(1024);

void prepararRequest(String path) {
    Serial.println("Call Api: " + API_URL + path);
    http.begin(API_URL + path);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Connection", "keep-alive");
}

void post(String body, String path) {
    prepararRequest(path);
    http.addHeader("Content-Length", String(body.length()));
    int statusCode = http.POST(body);
    if (statusCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(statusCode);
        String resposta = http.getString();
        deserializeJson(doc, resposta);
        JsonObject obj = doc.as<JsonObject>();
        pedidoId = obj["order"].as<String>();
        Serial.println(resposta);
        Serial.println(pedidoId);
    }
    else {
        Serial.print("Error code: ");
        Serial.println(statusCode);
    }
}

void patch(String body, String path) {
    http.addHeader("Content-Length", String(body.length()));
    prepararRequest(path);
    int statusCode = http.PATCH(body);
    if (statusCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(statusCode);
        String resposta = http.getString();
        Serial.println(resposta);
    }
    else {
        Serial.print("Error code: ");
        Serial.println(statusCode);
    }
}

boolean naoTemPedido() {
    if(pedidoId != NULL) return false;
    String path = "/orders/?status=COMPRANDO&customer=" + String(ID_ARDUINO);
    Serial.println("Checando se existe pedido");
    prepararRequest(path);
    http.GET();
    String resposta = http.getString();
    deserializeJson(doc, resposta);
    Serial.println(resposta);
    JsonObject obj = doc.as<JsonObject>();
    if(obj.containsKey("id")) pedidoId = obj["id"].as<String>();
    return !obj.containsKey("id");
}

String lerTag() {
    String text = "";
    while (rfid.available() > 0) {
        delay(5);
        text += (char)rfid.read();
    }
    if (text.length() > 20) return text.substring(1,11);
}

void setup() {
    pinMode (LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    rfid.begin(9600);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Wifi conectado, IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    if(!rfid.available() > 0) return;
    String tag = lerTag();
    String body;
    String path;
    digitalWrite(LED_BUILTIN, HIGH);
    if(tag == TAG_PEDIDO_FINALIZADO) {
        if(naoTemPedido()){
          Serial.println("Não há pedido para finalizar");
          return;
        }
        body = "{\"status\":\"FINALIZADO\"}";
        path = "/orders/" + pedidoId + "/";
        patch(body, path);
    }
    else if(tag == TAG_PEDIDO_CANCELADO) {
        if(naoTemPedido()){
          Serial.println("Não há pedido para cancelar");
          return;
        }
        body = "{\"status\":\"CANCELADO\"}";
        path = "/orders/"+ pedidoId + "/";
        patch(body, path);
    }
    else {
        body = "{\"rfid\":\"" + tag + "\",\"customer\":\"" + ID_ARDUINO + "\"}";
        Serial.println("BODY: " + body);
        path = "/items-orders/";
        post(body, path);
    }
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
}
