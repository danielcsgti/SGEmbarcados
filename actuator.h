#ifndef ACTUATOR_H
#define ACTUATOR_H

class Actuator {

  private:
    int id;
    const char* marca;
    const char* descActuator;
    const char* state;
    const char* commands[2];

  public:
    Actuator() {}
    void runCommandActurator() {}
    void loadActuator(JsonDocument obj) {
      this->marca = obj["actuator"]["brand"].as<char*>();
      this->descActuator = obj["actuator"]["descActuator"].as<char*>();
      this->state = obj["actuator"]["state"].as<char*>();
      this->commands[0] = obj["actuator"]["commands"][0].as<char*>();
      this->commands[1] = obj["actuator"]["commands"][1].as<char*>();
    }
    void saveActuator(JsonDocument obj) {
      obj["actuator"]["brand"].set(this->marca);
      obj["actuator"]["descActuator"].set(this->descActuator);
      obj["actuator"]["state"].set(this->state);
      obj["actuator"]["commands"][0].set(this->commands[0]);
      obj["actuator"]["commands"][1].set(this->commands[1]);
    }
    void toPrintActuator() {
      Serial.println("\n\nActuator :::");
      Serial.print("Marca: ");
      Serial.println(this->marca);
      Serial.print("descActuator: ");
      Serial.println(this->descActuator);
      Serial.print("state: ");
      Serial.println(this->state);
      Serial.print("commands[0]: ");
      Serial.println(this->commands[0]);
      Serial.print("commands[1]: ");
      Serial.println(this->commands[1]);
    }
};

#endif
