#include <WiFi.h>

#define ID_ARDUINO 4

// Informe as credencias da sua rede wifi
const char* ssid = "";
const char* password = "";
uint8_t TAG_INICIO_PEDIDO[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
uint8_t TAG_FIM_PEDIDO[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
HTTPClient http;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("Conectando no wifi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando Wifi...");
    }
    Serial.println("Wifi conectado, IP address: ");
    Serial.println(WiFi.localIP());
    pinMode (LED_BUILTIN, OUTPUT);
}

void loop() {
    String conteudo= "";
    Serial.println("Tag : " + String(conteudo));
    String conteudoTag = conteudo;
    if(conteudoTag == TAG_INICIO_PEDIDO) {
        //chama a api de inicio de pedido
        //verifica qual foi o ultimo pedido
        int ultimoPedido = verificaUltimoPedido();// criar uma api que verifica o ultimo pedido
        ultimoPedido += 1;
        NUMERO_PEDIDO = ultimoPedido;
        Serial.println("Call Api: https://market-api-tcc.herokuapp.com/orders/");
        http.begin("https://market-api-tcc.herokuapp.com/orders/");
        http.addHeader("Content-Type", "application/json");
        String dataAtual = "";
        String httpRequestData = "{\"code\":\"" + String(ultimoPedido)  + "\"}, {\"data\":\"" + String(dataAtual)  + "\"}, {\"customer\":\"" + String(ID_ARDUINO)  + "\"}";
        int httpResponseCode = http.POST(httpRequestData);
        if (httpResponseCode>0) {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            String respostaAPI = http.getString();
            Serial.println(respostaAPI);
        }
        else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
    }
    else if(conteudoTag == TAG_FIM_PEDIDO) {

    }
    else {
        String idItem = conteudoTag;//assume que o item é o valor da tag
        Serial.println("Call Api: https://market-api-tcc.herokuapp.com/items-orders/");
        http.begin("https://market-api-tcc.herokuapp.com/items-orders/");
        http.addHeader("Content-Type", "application/json");
        String httpRequestData = "{\"quantity\":\"" + String(1)  + "\"}, {\"item\":\"" + String(idItem)  + "\"}, {\"customer\":\"" + String(ID_ARDUINO)  + "\"}";
        int httpResponseCode = http.POST(httpRequestData);
        if (httpResponseCode>0) {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            String respostaAPI = http.getString();
            Serial.println(respostaAPI);
        }
        else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
    }
}
