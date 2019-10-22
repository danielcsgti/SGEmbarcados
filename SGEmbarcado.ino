/*
   SISTEMA DE GESTAO DE EMBARCADOS

   DESCRICAO: cadastrar, excluir, atualizar e localizar as informacoes sobre o embarcado,
   rede, sensores e atuadores utilizando a plataforma ESP32 da Espressif.

*/

#include "configuration.h"

AsyncWebServer server(80);
void notFound(AsyncWebServerRequest * request) {
  request->send(404, "text/plain", "Not found");
}
char e;

void setup() {
  Serial.begin(115200);
  loadFile("/config.json");
  net.toConnected();
  net.toPrintNetwork();
  //net.toAccessPoint();

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
  }
  else {
    Serial.println("SPIFFS Mount successful!");
  }

  File file = SPIFFS.open("/index.html", FILE_READ);

  if (!file) {
    Serial.println("[  Fail \t] - Falha ao carregar o arquivo de configJSON !!");
  }
  else {
    Serial.println("SPIFFS Load successful!");
  }

  server.on("/embarcado/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/embarcado.html", "text/html");
  });

  server.on("/embarcado/get", HTTP_GET, [] (AsyncWebServerRequest * request) {
    //posso usar essas variaveis para colocar elas em qualquer lugar
    const char* hardware = request->getParam("hardware")->value().c_str();
    const char* firmware = request->getParam("firmware")->value().c_str();
    const char* location = request->getParam("location")->value().c_str();
    const char* ip = request->getParam("ip")->value().c_str();
    const char* macAndressa = request->getParam("macAddress")->value().c_str();
    const char* modo = request->getParam("modo")->value().c_str();
    const char* mask = request->getParam("mask")->value().c_str();
    const char* gateway = request->getParam("gateway")->value().c_str();
    const char* essid = request->getParam("essid")->value().c_str();

    net.setNetwork(essid, ip, mask, gateway, modo);

    Serial.println(hardware);

    saveFile("/config.json");
  });

  server.onNotFound(notFound);

  server.begin();
}

void loop() {
  for (;;) {
    //    while (Serial.available()>0){
    //          e = Serial.read(); // Lê byte do buffer serial;
    //          Serial.print(e); // Faz o eco do byte recebido;
    //          if (e == 'a')
    //              embedded.toRestart();
    //          }
  }


}
