#ifndef BOARDED_H
#define BOARDED_H

class Boarded{
  private:
    int id;
    String marca;
    String descHardware;
    String firmware;
    String location;
    
  public:
    Boarded(){}
    void toSetup(){}
    void toRestart(){
        Serial.println("Restartando o sistema embarcado ...");
        ESP.restart();
      }
    void toRegiterLog(){}
};

#endif
