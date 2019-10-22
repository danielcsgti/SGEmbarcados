#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

class Network {

  private:
    const char* ssid;
    const char* password;
    const char* ip;
    const char* mask;
    const char* ipGateway;
    const char* modeOperation;

  public:
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // CONSTRUTOR

    Network(char *ssid, char *password) {
      this->ssid = ssid;
      this->password = password;
    };
    
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // SET ATRIBUTOS

    void setNetwork(const char* ssid, const char* ip, const char* mask, const char* ipGateway, const char* modeOperation) {
      this->ssid = ssid;
      this->ip = ip;
      this->mask = mask;
      this->ipGateway = ipGateway;
      this->modeOperation = modeOperation;
    };

    //--------------------------------------------------------------
    // Configura o ESP32 como Estação Cliente

    void toConnected() {
      WiFi.begin(this->ssid, this->password);
      Serial.print("[ net \t ] - Conectando a rede: ");
      Serial.print(this->ssid);
      while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(5000);
      }
      this->ip = WiFi.localIP().toString().c_str();
      this->mask = WiFi.subnetMask().toString().c_str();
      this->ipGateway = WiFi.gatewayIP().toString().c_str();
      this->modeOperation = "CLIENT_STATION";
      Serial.println(WiFi.localIP());
    }
    //--------------------------------------------------------------
    // Configura o ESP32 como Access Point

    void toAccessPoint() {
      WiFi.softAP(this->ssid, this->password);
      this->ipGateway = WiFi.softAPIP().toString().c_str();
      this->modeOperation = "ACCESS_POINT";
      Serial.println(WiFi.softAPIP());
    }

    //--------------------------------------------------------------
    // Salvar as informações no arquivo JSON

    void saveNetwork(JsonDocument obj) {
      obj["network"]["ip"].set(this->ip);
      obj["network"]["mask"].set(this->mask);
      obj["network"]["gateway"].set(this->ipGateway);
      obj["network"]["ssid"].set(this->ssid);
      obj["network"]["password"].set(this->password);
      obj["network"]["modeOperation"].set(this->modeOperation);
    }

    //--------------------------------------------------------------
    // Imprime as informações sobre a Rede

    void toPrintNetwork() {

      if (strcmp(this->modeOperation, "CLIENT_STATION") == 0) {
        Serial.println();
        Serial.print("[ net \t ] - Modo de Operacao: ");
        Serial.println(this->modeOperation );
        Serial.print("[ net \t ] - SSID: ");
        Serial.println(this->ssid);
        Serial.print("[ net \t ] - IP: ");
        Serial.println(this->ip );
        Serial.print("[ net \t ] - Mascara de rede: ");
        Serial.println(this->mask);
        Serial.print("[ net \t ] - Gateway: ");
        Serial.println(this->ipGateway);
      } else if (strcmp(this->modeOperation, "ACCESS_POINT") == 0) {
        Serial.print("[ net \t ] - Modo de Operacao: ");
        Serial.println(this->modeOperation );
        Serial.print("[ net \t ] - SSID:");
        Serial.println(this->ssid);
        Serial.print("[ net \t ] - Gateway: ");
        Serial.println(this->ipGateway);
      }
    }

    //--------------------------------------------------------------
    // METODO LOAD E SAVE

    void loadNetwork(JsonDocument obj) {
      this->ip = obj["network"]["ip"].as<char*>();
      this->mask = obj["network"]["mask"].as<char*>();
      this->ipGateway = obj["network"]["gateway"].as<char*>();
      this->ssid = obj["network"]["ssid"].as<char*>();
      this->password = obj["network"]["password"].as<char*>();
      this->modeOperation = obj["network"]["modeOperation"].as<char*>();
    }


    //----------------------------------------------------------------
    // METODO SERVIR PAGINA HTML

};

#endif
