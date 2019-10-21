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
  //net.toPrintNetwork();
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
    String hardware, firmware, location, ip, macAndressa, modo, mask, gateway, essid;
    //posso usar essas variaveis para colocar elas em qualquer lugar
    hardware = request->getParam("hardware")->value();
    firmware = request->getParam("firmware")->value();
    location = request->getParam("location")->value();
    ip = request->getParam("ip")->value();
    macAndressa = request->getParam("macAddress")->value();
    modo = request->getParam("modo")->value();
    mask = request->getParam("mask")->value();
    gateway = request->getParam("gateway")->value();
    essid = request->getParam("essid")->value();
     
    net.setNetwork(essid, ip, mask, gateway, modo);
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
