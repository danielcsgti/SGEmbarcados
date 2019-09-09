/*
 * SISTEMA DE GESTAO DE EMBARCADOS
 * 
 * DESCRICAO: cadastrar, excluir, atualizar e localizar as informacoes sobre o embarcado,
 * rede, sensores e atuadores utilizando a plataforma ESP32 da Espressif.
 * 
 */

#include "configuration.h"

char e;

void setup() {
  Serial.begin(115200);
  net.toConnected();
  //net.toAccessPoint();
}

void loop() {
  
  net.toPrintNetwork();   
  for(;;){
    while (Serial.available()>0){
          e = Serial.read(); // Lê byte do buffer serial;
          Serial.print(e); // Faz o eco do byte recebido;
          if (e == 'a')
              embedded.toRestart();
          }
        }
    

}
