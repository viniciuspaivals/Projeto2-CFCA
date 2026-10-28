/*
   PROJETO: Fase 1 - Clonagem
   FUNÇÃO: Ler botões do controle remoto original e descobrir seus códigos HEX
   OBS: Caso não seja o receptor VS1838B (presente na documentação fritzing) deverá ser modificada
 */

#include <IRremote.hpp> //INCLUI A BIBLIOTECA IRemote

const int IR_RECEIVE_PIN = 2; //DEFINE O PINO D2 PARA O RECEPTOR IR

void setup() {
  //INICIA A COMUNICACAO SERIAL
  Serial.begin(9600);
  
  while (!Serial); 

  Serial.println("Aponte o controle para o receptor e aperte os botoes.");
  Serial.println("#===================================================#");

  //INICIA O RECEPTOR IR NO PINO DEFINIDO E ATIVA O PISCAR DO LED INTERNO AO RECEBER SINAL
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  //VERIFICA SE CAPTUROU CODIGO INFRAVERMELHO
  if (IrReceiver.decode()) {
    
    //IGNORA CÓDIGOS DE REPETIÇÃO CONTÍNUA (BOTÃO É MANTIDO PRESSIONADO)
    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
      IrReceiver.resume();
      return;
    }

    Serial.println("--- NOVO SINAL RECEBIDO ---");
    
    //IMPRIME O PROTOCOLO IDENTIFICADO (NEC, SONY, SAMSUNG, PANASONIC...)
    Serial.print("Protocolo: ");
    Serial.println(getProtocolString(IrReceiver.decodedIRData.protocol));
    
    //IMPRIME O CÓDIGO HEXADECIMAL COMPLETO (UTILIZADO NA FASE 2)
    Serial.print("Codigo Hexadecimal (Raw Data): 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    //IMPRIME O COMANDO CURTO
    Serial.print("Comando Curto: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    
    Serial.println("");
    
    //PREPARA O MODULO PARA RECEBER O PROXIMO SINAL
    IrReceiver.resume(); 
  }
}