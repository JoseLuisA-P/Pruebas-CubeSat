#include "Arduino.h"
#include <SoftwareSerial.h>
#include "commLib.h"

UARTSocket::UARTSocket(int RX,int TX,int baudrate,int timeout,int maxretries)
{
  uart = new SoftwareSerial(RX,TX);
  uart->begin(baudrate);
  _timeout = timeout;
  _maxretries = maxretries;
}

void UARTSocket::SendPackage(uint8_t* message,size_t messlen)
{  
  int retries = 0;

  while(!_ACK && retries<_maxretries)
  {
      uart->write(message,messlen);
    unsigned long startTime = millis();

    while (!_ACK && (millis() - startTime) < _timeout) 
    {
      byte temp = uart->read();

      if (temp == 'A') { // Recibe el ACK
        _ACK = true;
        if(Serial)Serial.println("Data sent successfully!");
      } 
        
      else if (temp == 'N') { // Recibe el NACK
        _ACK = false;
        if(Serial)Serial.println("NACK received, retrying...");
        retries++;
        break;
      }

    }
  }

  if(!_ACK)
  {
    if(Serial)Serial.println("Fallido despues de muchos intentos");
  }

  _ACK = false;
}