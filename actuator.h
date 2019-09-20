#ifndef ACTUATOR_H
#define ACTUATOR_H

class Actuator{

  private:
    int id;
    String marca;
    String descActuator;
    String Status;
    char *commands[];

  public:
    Actuator(){}
    void runCommandActurator(){}
};

#endif
