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

#include "boarded.h"
#include "network.h"
#include "sensor.h"
#include "actuator.h"
#include "serverMqtt.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 // VARIAVEIS GLOBAIS

 JsonObjectConst objJson;
 
 Network net("Redmi","12345678");;
 Sensor sensor;
 Actuator actuator;
 ServerMqtt serverMqtt;
 Boarded embedded;

 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  MÉTODOS DE CONFIGURAÇÃO DO EMBARCADO

//_________________________________________________________________________________________
// CARREGA ARQUIVO JSON PARA UM OBJETO JsonDocument

void load(){
  
}

//_________________________________________________________________________________________
// DESERIALIZAÇÃO DO ARQUIVO JSON

 bool deserializeConfig(Stream &file){
  DynamicJsonDocument docJson(255);
  DeserializationError error = deserializeJson(docJson,file);
  if (error)
    return false;
  else{
    return true;
  }
 }

//_________________________________________________________________________________________
// DESERIALIZAÇÃO DO ARQUIVO JSON

bool loadFile(const char *fileName){

    File file = SPIFFS.open(fileName,"r");
    
    if(!file){
      Serial.println("[  Fail \t] - Falha ao carregar o arquivo de configJSON !!");
      return false;
    }
    
    bool success = deserializeConfig(file);
    
    if(!success){
      Serial.println("[  Fail \t] - Falha ao deserializar o arquivo configJSON !!");
      return false;
    }
    return true;
  }
 
 //_________________________________________________________________________________________ 
