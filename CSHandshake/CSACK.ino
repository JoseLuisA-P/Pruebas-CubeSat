#include <SoftwareSerial.h>
#include "commLib.h" // Libreria en proceso para OBC

#define RX_PIN 10
#define TX_PIN 11
#define EN1_PIN 9 
#define EN2_PIN 8

#define BAUDRATE 9600
#define TIMEOUT 1000
#define MAXRETRIES 3

UARTSocket uart(RX_PIN, TX_PIN, BAUDRATE, TIMEOUT, MAXRETRIES, EN1_PIN, EN2_PIN);

// como ahorita el arduino actua como master entonces debe enviar lo que indica la pagina 56

uint8_t destination = 020;
uint8_t messageSize = 000;
uint8_t selfAddress = 001;
size_t size = 000;
uint8_t startByte ='i'; // 'i' de inicio de trama
uint16_t SendCRC = 0;
int dato = 0;
void setup() {
  Serial.begin(9600);       //Monitor serial de arduino para los loggs

}
void loop() {
  // Envía el byte 0x20 para indicar que Python debe comenzar a transmitir
  // messageSize = 1;
  // uint8_t startByte = 0xAA;

  messageSize = sizeof(startByte);
  uart.SendPackage(&startByte,messageSize);
  SendCRC = uart.calculateCRC(startByte,messageSize);
  Serial.println(SendCRC);
  delay(1000);
  dato = uart.ReceivePackage();
  // Serial.println(dato);

}

/*
void loop() 
{
  // que el arduino envie (comience el enable para transmitir)
  // comienza enviando el paquete dado por dest. address-mess. size-src add.-mess-crc
  messageSize = sizeof(test);
  uart.SendPackage(test,messageSize); // aqui dentro esta la espera del ack
  SendCRC = uart.calculateCRC(test,messageSize);
  Serial.println(SendCRC);
  delay(1000);

  /*
  //---enviamos el ángulo para mover el servo------
  Serial.print("I"); //inicio de trama
  Serial.print("S"); //S para indicarle que vamos a mover el servo
  Serial.print(angulo); //ángulo  o dato
  Serial.print("F"); //fin de trama
  //----------------------------
  delay(50); 
  //---solicitamos una lectura del sensor----------
  Serial.print("I"); //inicio de trama
  Serial.print("L"); //L para indicarle que vamos a Leer el sensor
  Serial.print("F"); //fin de trama
  Serial.flush();    //Esperamos hasta que se envíen los datos
  //----Leemos la respuesta del Esclavo-----
  digitalWrite(EnTxPin, LOW); //RS485 como receptor
  if(Serial.find("i"))//esperamos el inicio de trama
  {
      int dato=Serial.parseInt(); //recibimos valor numérico
      if(Serial.read()=='f') //Si el fin de trama es el correcto
       {
         funcion(dato);  //Realizamos la acción correspondiente          
      }
      
  }
  digitalWrite(EnTxPin, HIGH); //RS485 como Transmisor
  //----------fin de la respuesta-----------
  */
//}