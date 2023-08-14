#include <SoftwareSerial.h>
#include "commLib.h"

#define RX_PIN      10
#define TX_PIN      11
#define EN1_PIN      9
#define EN2_PIN      8

#define BAUDRATE    9600
#define TIMEOUT     1000
#define MAXRETRIES  3

UARTSocket uart(RX_PIN,TX_PIN,BAUDRATE,TIMEOUT,MAXRETRIES,EN1_PIN,EN2_PIN);

uint8_t test[] = {42,43,44,45};

uint8_t destination = 020;
uint8_t messageSize = 000;
uint8_t selfAddress = 001;
size_t size = 000;

uint16_t SendCRC = 0;

void setup() 
{
  Serial.begin(9600); //Monitor serial de arduino para los loggs
}

void loop() 
{
  messageSize = sizeof(test);
  uart.SendPackage(test,messageSize);
  SendCRC = uart.calculateCRC(test,messageSize);
  Serial.println(SendCRC);
  delay(1000);
}