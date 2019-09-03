#ifndef SENSOR_H
#define SENSOR_H

class Sensor{
  private:
    int id;
    String marca;
    String descSensor;
    String sampleRate;
    float *dataRaw[];
   
   public:
    Sensor(){}
    void toReadData(){}
    void preProcessingData(){}
};

#endif
