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
    Network(char *ssid, char *password){
      this->ssid = ssid;
      this->password = password;
    }

    void toConnected(){
        WiFi.begin(this->ssid,this->password);
        Serial.print("[ net/t ] - Conectando a rede: ");
        Serial.println(this->ssid);
        while(WiFi.status() != WL_CONNECTED){
          Serial.print(".");
          delay(5000);
        }
        this->ip = WiFi.localIP();
        this->mask = WiFi.subnetMask();
        this->ipGateway = WiFi.gatewayIP();
        this->modeOperation = "CLIENT_STATION";
    }
    
    void toAccessPoint(){
      WiFi.softAP(this->ssid, this->password);
      this->ipGateway = WiFi.softAPIP();
      this->modeOperation = "ACCESS_POINT";
    }
    void toPrintNetwork(){

        if( strcmp(this->modeOperation,"CLIENT_STATION")==0 ){
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
};


#endif
