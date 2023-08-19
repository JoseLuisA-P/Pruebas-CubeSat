#include <SoftwareSerial.h>
#include "commLib.h"

#define RX_PIN 10
#define TX_PIN 11
#define EN1_PIN 9
#define EN2_PIN 8

#define BAUDRATE 9600
#define TIMEOUT 1000
#define MAXRETRIES 3

UARTSocket uart(RX_PIN, TX_PIN, BAUDRATE, TIMEOUT, MAXRETRIES, EN1_PIN, EN2_PIN);

SoftwareSerial mySerial (RX_PIN, TX_PIN);
// como ahorita el arduino actua como master entonces debe enviar lo que indica la pagina 56
//uint8_t test[] = {0x20};

uint8_t destination = 020;
uint8_t messageSize = 000;
uint8_t selfAddress = 001;
size_t size = 000;

uint16_t SendCRC = 0;

void setup() {
  Serial.begin(9600);       //Monitor serial de arduino para los loggs
  Serial.setTimeout(1000);  //establecemos un tiempo de espera de 100ms
    mySerial.begin(9600);       //Monitor serial de arduino para los loggs
  mySerial.setTimeout(1000);  //establecemos un tiempo de espera de 100ms
  pinMode(EN1_PIN, OUTPUT);
  pinMode(EN2_PIN, OUTPUT);

  digitalWrite(EN1_PIN, HIGH);  // comienza en modo transmision
  digitalWrite(EN2_PIN, LOW);   // comienza en modo recepcion
}
void loop() {
  // Envía el byte 0x20 para indicar que Python debe comenzar a transmitir
  messageSize = 1;
  uint8_t startByte = 0xAA;

  digitalWrite(EN1_PIN, HIGH);  // comienza en modo transmision
  digitalWrite(EN2_PIN, LOW); // comienza en modo recepcion
  mySerial.write("0xAA");
  //uart.SendPackage(&startByte, messageSize); // aquí dentro está la espera del ACK
  Serial.println("enviado");
  // Esperar un tiempo antes de recibir la respuesta
  //delay(1000);

  // Cambia al modo de recepción
  //digitalWrite(EN1_PIN, LOW);
  //digitalWrite(EN2_PIN, HIGH);

  // Esperar a recibir una respuesta
  //uart.ReceivePackage();

  // No cambies de nuevo al modo de transmisión aquí

  // Pausa antes de iniciar el siguiente ciclo
  delay(1000);
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