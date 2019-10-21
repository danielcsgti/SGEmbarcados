#ifndef COMUNICATIONMQTT_H
#define COMUNICATIONMQTT_H

class ServerMqtt {

  private:
    int id;
    const char* ipHost;
    const char* porta;
    const char* user;
    const char* password;
    const char* listTopics[6];

  public:
    ServerMqtt() {}
    void toSubscribeTopic() {}
    void toPublishTopic() {}
    void loadMqtt(JsonDocument obj) {
      this->ipHost = obj["serverMqtt"]["ipHost"].as<char*>();
      this->porta = obj["serverMqtt"]["porta"].as<char*>();
      this->user = obj["serverMqtt"]["user"].as<char*>();
      this->password = obj["serverMqtt"]["password"].as<char*>();
      for (int i = 0; i < 6; i++) {
        this->listTopics[i] = obj["serverMqtt"]["listTopics"][i].as<char*>();
      }
    }
    void saveMqtt(JsonDocument obj) {
      obj["serverMqtt"]["ipHost"].set(this->ipHost);
      obj["serverMqtt"]["porta"].set(this->porta);
      obj["serverMqtt"]["user"].set(this->user);
      obj["serverMqtt"]["password"].set(this->password);
      for (int i = 0; i < 6; i++) {
        obj["serverMqtt"]["listTopics"][i].set(this->listTopics[i]);
      }
    }
    void toPrintMqtt() {
      Serial.println("\n\nServer Mqtt :::");
      Serial.print("ipHost: ");
      Serial.println(this->ipHost);
      Serial.print("porta: ");
      Serial.println(this->porta);
      Serial.print("user: ");
      Serial.println(this->user);
      Serial.print("password: ");
      Serial.println(this->password);
      for (int i = 0; i < 6; i++) {
        Serial.print("listTopics[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.println(this->listTopics[i]);
      }
    }
};
#endif
