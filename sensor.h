#ifndef SENSOR_H
#define SENSOR_H

class Sensor{
  private:
    int id;
    const char* marca;
    const char* descSensor;
    int sampleRate;
    const char* unitMeasurement;
    float dataRaw[2];
   
   public:
    Sensor(){}
    void toReadData(){}
    void preProcessingData(){}
    void loadSensor(JsonDocument obj) {
      this->marca = obj["sensor"]["brand"].as<char*>();
      this->descSensor = obj["sensor"]["descSensor"].as<char*>();
      this->sampleRate = obj["sensor"]["sampleRate"];
      this->unitMeasurement = obj["sensor"]["unitMeasurement"].as<char*>();
      this->dataRaw[0] = obj["sensor"]["dataRaw"][0];
      this->dataRaw[1] = obj["sensor"]["dataRaw"][1];
    }
    void saveSensor(JsonDocument obj) {
      obj["sensor"]["brand"].set(this->marca);
      obj["sensor"]["descSensor"].set(this->descSensor);
      obj["sensor"]["sampleRate"].set(this->sampleRate);
      obj["sensor"]["unitMeasurement"].set(this->unitMeasurement);
      obj["sensor"]["dataRaw"][0].set(this->dataRaw[0]);
      obj["sensor"]["dataRaw"][1].set(this->dataRaw[1]);
    }
    void toPrintSensor() {
      Serial.println("\n\nSensor :::");
      Serial.print("Marca: ");
      Serial.println(this->marca);
      Serial.print("descSensor: ");
      Serial.println(this->descSensor);
      Serial.print("sampleRate: ");
      Serial.println(this->sampleRate);
      Serial.print("unitMeasurement: ");
      Serial.println(this->unitMeasurement);
      Serial.print("dataRaw[0]: ");
      Serial.println(this->dataRaw[0]);
      Serial.print("dataRaw[1]: ");
      Serial.println(this->dataRaw[1]);
    }
};

#endif
