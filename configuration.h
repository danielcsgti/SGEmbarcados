//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// DEFINICAO DE PINOS

#define D2   2
#define D3   3
#define D4   4
#define D5   5
#define D6   6
#define D7   7
#define D8   8
#define D9   9
#define D10  10
#define D11  11


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// BIBLIOTECAS

#include <ArduinoJson.h>

#include "FS.h"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"

#include "boarded.h"
#include "network.h"
#include "sensor.h"
#include "actuator.h"
#include "serverMqtt.h"


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// VARIAVEIS GLOBAIS

const size_t capacity = 2 * JSON_ARRAY_SIZE(2) + JSON_ARRAY_SIZE(6) + 2 * JSON_OBJECT_SIZE(4) + 3 * JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + 750;
StaticJsonDocument<capacity> docJson;

Network net("nep-fapeg", "fapeg@Nep");
Sensor sensor;
Actuator actuator;
ServerMqtt serverMqtt;
Boarded embedded;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  MÉTODOS DE CONFIGURAÇÃO DO EMBARCADO

//_________________________________________________________________________________________
// SERIALIZACAO DO ARQUIVO JSON

bool serializeConfig(Stream &file) {
  //Salva no JsonObject as informacoes das classes
  embedded.saveBoarded(docJson);
  actuator.saveActuator(docJson);
  serverMqtt.saveMqtt(docJson);
  sensor.saveSensor(docJson);
  net.saveNetwork(docJson);
  //Serializa no documento json o JsonObject
  return (serializeJson(docJson, file) > 0);
}

bool saveFile(const char* fileName) {

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return false;
  }
  else {
    Serial.println("SPIFFS Mount successful!");
  }

  File file = SPIFFS.open(fileName, FILE_WRITE);

  if (!file) {
    Serial.println("[  Fail \t] - Falha ao carregar o arquivo de configJSON !!");
    return false;
  }
  else {
    Serial.println("SPIFFS Load successful!");
  }

  bool success = serializeConfig(file);

  if (!success) {
    Serial.println("[  Fail \t] - Falha ao serializar o arquivo configJSON !!");
    return false;

  }

  file.close();

  return true;
}

//_________________________________________________________________________________________
// DESERIALIZAÇÃO DO ARQUIVO JSON

bool deserializeConfig(Stream &file) {
  DeserializationError error = deserializeJson(docJson, file);
  if (error) {
    Serial.println(error.c_str());
    return false;
  }
  else {
    //Passa o documento JSON como um objeto para o carregamento dos atributos de cada classe
    embedded.loadBoarded(docJson);
    actuator.loadActuator(docJson);
    serverMqtt.loadMqtt(docJson);
    sensor.loadSensor(docJson);
    net.loadNetwork(docJson);

    return true;
  }
}

//_________________________________________________________________________________________
// CARREGAMENTO DO ARQUIVO JSON

bool loadFile(const char* fileName) {

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return false;
  }
  else {
    Serial.println("SPIFFS Mount successful!");
  }

  File file = SPIFFS.open(fileName, FILE_READ);

  if (!file) {
    Serial.println("[  Fail \t] - Falha ao carregar o arquivo de configJSON !!");
    return false;
  }
  else {
    Serial.println("SPIFFS Load successful!");
  }

  bool success = deserializeConfig(file);

  if (!success) {
    Serial.println("[  Fail \t] - Falha ao deserializar o arquivo configJSON !!");
    return false;
  }

  file.close();

  return true;
}

//_________________________________________________________________________________________
