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

uint16_t UARTSocket::calculateCRC(uint8_t* data, size_t length) {
  uint16_t crc = _CRC_INITIAL;

  for (size_t i = 0; i < length; i++) {
    crc ^= (uint16_t)data[i] << 8;
    for (int j = 0; j < 8; j++) {
      if (crc & 0x8000)
        crc = (crc << 1) ^ _CRC_POLYNOMIAL;
      else
        crc <<= 1;
    }
  }

  return crc;
}

/*Device identification
  sendDeviceId: 
  Params to receive > device address
  it establishes the slaves' addresses
  checkDeviceAddress:
  Params to receive >  received_info, my_address
  Each byte begins and ends with a start and stop bit,
  following the UART standard. When the address bit is set to one by any of the nodes,
  it causes an interrupt in the other nodes on the bus. Each node then checks if the
  address matches its own. If it is not addressed, the node can ignore subsequent
  bytes (address bits being zero).
*/
int UARTSocket::sendDeviceId(int device_address){
  if (device_address < 0 || device_address > 255) {
      // Handle the error
      Serial.println("Device address out of range");
      return -1; // indicate an error condition
  }

  // toggle pin to send mode
  

}

bool UARTSocket::checkDeviceAddress(int received_info, int my_address){
  
  return check;
}
