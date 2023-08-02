#include <SoftwareSerial.h>
#include "commLib.h"

#define RX_PIN      10
#define TX_PIN      11
#define BAUDRATE    9600
#define TIMEOUT     1000
#define MAXRETRIES  3

UARTSocket uart(RX_PIN,TX_PIN,BAUDRATE,TIMEOUT,MAXRETRIES);
uint8_t test[] = {42,43,44,45};
size_t size = sizeof(test);

void setup() 
{
  Serial.begin(9600); //Monitor serial de arduino para los loggs
}

void loop() 
{
  uart.SendPackage(&test,size);
  delay(1000);
}