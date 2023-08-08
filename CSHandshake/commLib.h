#ifndef COMMLIB_H
#define COMMLIB_H

#include <Arduino.h>
class UARTSocket
{
  public:
    UARTSocket(int RX,int TX,int baudrate,int timeout,int maxretries);
    // device identification
    int sendDeviceId(int device_address); // send device id
    bool checkDeviceAddress(int received_info, int my_address); // will check if the byte received matches the device address

    // parameters setting
    int setBaudRate(int baud_rate);

    // transaction flow


    void SendPackage(uint8_t* message,size_t messlen);
    uint16_t calculateCRC(uint8_t* data, size_t length); 
    


  private:
    SoftwareSerial *uart;
    int _timeout;
    int _maxretries;
    bool _ACK;
    uint16_t _CRC_POLYNOMIAL = 0x1021;  // CRC-16-CCITT polynomial
    uint16_t _CRC_INITIAL = 0xFFFF;  // Initial value for CRC calculation
};
#endif