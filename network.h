#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>


class Network{

  private:
    char * ssid;
    char * password;
    IPAddress ip;
    IPAddress mask;
    IPAddress ipGateway;
    char *modeOperation;
  
  public:
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // CONSTRUTOR

    Network(char *ssid, char *password){
      this->ssid = ssid;
      this->password = password;
    };
  //--------------------------------------------------------------
  // Configura o ESP32 como Estação Cliente

    void toConnected(){
        WiFi.begin(this->ssid,this->password);
        Serial.print("[ net \t ] - Conectando a rede: ");
        Serial.print(this->ssid);
        while(WiFi.status() != WL_CONNECTED){
          Serial.print(".");
          delay(5000);
        }
        this->ip = WiFi.localIP();
        this->mask = WiFi.subnetMask();
        this->ipGateway = WiFi.gatewayIP();
        this->modeOperation = "CLIENT_STATION";
    }
  //--------------------------------------------------------------
  // Configura o ESP32 como Access Point
    
    void toAccessPoint(){
      WiFi.softAP(this->ssid, this->password);
      this->ipGateway = WiFi.softAPIP();
      this->modeOperation = "ACCESS_POINT";
    }

  //--------------------------------------------------------------
  // Salvar as informações no arquivo JSON

  void toSaveJSON( ﻿JsonObjectConst objJson ){
    strlcpy(this->ssid, objJson["Network"]["ssid"],sizeof(this->ssid) );
    strlcpy(this->password, objJson["Network"]["ssid"],sizeof(this->password) );
    strlcpy(this->modeOperation, objJson["Network"]["ssid"],sizeof(this->modeOperation) );
  
  }

  //--------------------------------------------------------------
  // Imprime as informações sobre a Rede

    void toPrintNetwork(){

        if( strcmp(this->modeOperation,"CLIENT_STATION")==0 ){
          Serial.println();
          Serial.print("[ net \t ] - Modo de Operacao: ");
          Serial.println(this->modeOperation );
          Serial.print("[ net \t ] - SSID:");
          Serial.println(this->ssid);
          Serial.print("[ net \t ] - IP: ");
          Serial.println(this->ip );
          Serial.print("[ net \t ] - Mascara de rede: ");
          Serial.println(this->mask);
          Serial.print("[ net \t ] - Gateway: ");
          Serial.println(this->ipGateway);
        }else if( strcmp(this->modeOperation,"ACCESS_POINT")==0 ){
            Serial.print("[ net \t ] - Modo de Operacao: ");
            Serial.println(this->modeOperation );
            Serial.print("[ net \t ] - SSID:");
            Serial.println(this->ssid);
            Serial.print("[ net \t ] - Gateway: ");
            Serial.println(this->ipGateway);
        }
    }
  
  //--------------------------------------------------------------
  // METODOS GET AND SET
    
    char * getSsid(){
      return this->ssid;
    }
    char * getPassword(){
      return this->password;
    }
};


#endif
