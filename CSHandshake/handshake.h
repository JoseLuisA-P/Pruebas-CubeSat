#ifndef HANDSHAKE_H
#define HANDSHAKE_H

#include <Arduino.h>

// device identification
int send_device_id(int device_address); // send device id
bool check_device_address(int received_info, int my_address); // will check if the byte received matches the device address

// parameters setting
int set_baud_rate(int baud_rate);

// transaction flow




#endif