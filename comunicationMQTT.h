#ifndef COMUNICATIONMQTT_H
#define COMUNICATIONMQTT_H

class ComunicationMQTT{

  private:
    int id;
    String ipHost;
    String porta;
    char *topics[];

   public:
    ComunicationMQTT(){}
    void toSubscribeTopic(){}
    void toPublishTopic(){}
    
};
#endif
