#include "myFonctions.h"

void setup() {
  startConnexion();
  //sendCommand("AT");
  //sendCommand("AT+CIPSEND=1");
  //sendCommand("AT+CIPSTART=?");//TCP/UDP
  //establishConnection("UDP","45.77.46.150","9991");
  //sendMessage("+33000000000","Message sent by Oumar from Arduino !");
  //myWiFi("Network","12345567A@23");
  //readMessage();//From the SIM7000G --> +33 6 27 83 32 41

}

void loop() {
  readByteSerial2(); //Pour les commandes AT
  //sendData(1);


}