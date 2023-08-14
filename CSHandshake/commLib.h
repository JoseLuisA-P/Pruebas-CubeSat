#ifndef COMMLIB_H
#define COMMLIB_H

#include <Arduino.h>
class UARTSocket
{
  public:
    UARTSocket(int RX,int TX,int baudrate,int timeout,int maxretries,int en1, int en2);
    void SendPackage(uint8_t* message,size_t messlen);
    uint16_t calculateCRC(uint8_t* data, size_t length); 

  private:
    SoftwareSerial *uart;
    int _timeout;
    int _maxretries;
    uint8_t _en1;
    uint8_t _en2;
    bool _ACK;
    uint16_t _CRC_POLYNOMIAL = 0x1021;  // CRC-16-CCITT polynomial
    uint16_t _CRC_INITIAL = 0xFFFF;  // Initial value for CRC calculation
};
#endif