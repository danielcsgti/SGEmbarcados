#ifndef COMUNICATIONMQTT_H
#define COMUNICATIONMQTT_H

class ServerMqtt{

  private:
    int id;
    String ipHost;
    String porta;
    String user;
    String password;
    char *listTopics[];

   public:
    ServerMqtt(){}
    void toSubscribeTopic(){}
    void toPublishTopic(){}
    
};
#endif
