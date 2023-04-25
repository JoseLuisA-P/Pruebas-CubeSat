#include <SoftwareSerial.h>

#define RXD2 2
#define TXD2 3

SoftwareSerial mySerial(RXD2, TXD2); // RX, TX

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200); //Utilizando el 2do serial para poder mostrar el echo

}


void loop() {
  if(mySerial.available() > 0){
      String inMes = mySerial.readString();

      Serial.println(inMes);      
       
      mySerial.println(inMes);    

  }


}
