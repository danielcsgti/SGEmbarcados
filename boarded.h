#ifndef BOARDED_H
#define BOARDED_H

class Boarded{
  private:
    int id;
    const char* marca;
    const char* descHardware;
    const char* firmware;
    const char* location;
    
  public:
    Boarded(){}
    void toSetup(){}
    void toRestart(){
        Serial.println("Restartando o sistema embarcado ...");
        ESP.restart();
      }
    void toRegiterLog(){}
    void loadBoarded(JsonDocument obj) {
      this->marca = obj["boarded"]["brand"].as<char*>();
      this->descHardware = obj["boarded"]["descHardware"].as<char*>();
      this->firmware = obj["boarded"]["firmware"].as<char*>();
      this->location = obj["boarded"]["location"].as<char*>();
    }
    void saveBoarded(JsonDocument obj) {
      obj["boarded"]["brand"].set(this->marca);
      obj["boarded"]["descHardware"].set(this->descHardware);
      obj["boarded"]["firmware"].set(this->firmware);
      obj["boarded"]["location"].set(this->location);
    }
    void toPrintBoarded() {
      Serial.println("\n\nBoarded :::");
      Serial.print("Marca: ");
      Serial.println(this->marca);
      Serial.print("descHardware: ");
      Serial.println(this->descHardware);
      Serial.print("firmware: ");
      Serial.println(this->firmware);
      Serial.print("location: ");
      Serial.println(this->location);
    }
};

#endif
