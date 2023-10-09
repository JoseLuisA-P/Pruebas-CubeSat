#include <SoftwareSerial.h>
#include "commLib.h" // Libreria en proceso para OBC

#define RX_PIN 10
#define TX_PIN 11
#define EN1_PIN 9 // enable de MAX485 master (Arduino)
#define EN2_PIN 8 // enable de MAX485 slave (PC - py script TTL)

#define BAUDRATE 9600
#define TIMEOUT 1000
#define MAXRETRIES 3

UARTSocket uart(RX_PIN, TX_PIN, BAUDRATE, TIMEOUT, MAXRETRIES, EN1_PIN, EN2_PIN);


uint8_t destination = 020;
uint8_t messageSize = 000;
uint8_t selfAddress = 001;
size_t size = 000;

uint8_t startByte ='i'; // 'i' de inicio de trama
uint16_t SendCRC = 0;
int dato = 0;

void setup() {
  Serial.begin(9600); // Monitor serial de arduino para los loggs
  
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
