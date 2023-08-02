#ifndef COMMLIB_H
#define COMMLIB_H

#include <Arduino.h>
class UARTSocket
{
  public:
    UARTSocket(int RX,int TX,int baudrate,int timeout,int maxretries);
    void SendPackage(uint8_t(*)[] message,size_t messlen);

  private:
    SoftwareSerial *uart;
    int _timeout;
    int _maxretries;
    bool _ACK;
};
#endif