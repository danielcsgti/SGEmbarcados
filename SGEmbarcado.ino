/*
 * SISTEMA DE GESTAO DE EMBARCADOS
 * 
 * DESCRICAO: cadastrar, excluir, atualizar e localizar as informacoes sobre o embarcado,
 * rede, sensores e atuadores utilizando a plataforma ESP32 da Espressif.
 * 
 */

#include "configuration.h"
 
void setup() {
  Serial.begin(115200);
}

void loop() {

  Network net("Redmi","12345678");
  //Boarded embedded();
  net.toAccessPoint();
  //net.toConnected();
  net.toPrintNetwork();

  for(;;){
    
  }
  

}
