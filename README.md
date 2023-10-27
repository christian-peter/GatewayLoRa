# GatewayLoRa
Project ongoing...
For any questions or suggestions, put it in comment.

10/16/2023 --> HTTP Client communication en utilisant WiFi -- Done
Etablissement d'un lien GSM --> Done
INSTRUCTIONS
  //--GSM--//
  //ETABLISSEMENT DE LA COMM GSM - SFR APN
  //sendCommand("AT+SAPBR=3,1,\"Contype\", \"GPRS\"");
  //sendCommand("AT+SAPBR=3,1,\"APN\",\"sl2sfr\""); //Configure bearer profile APN SFR
  //sendCommand("AT+SAPBR=1,1"); //Open
  //sendCommand("AT+SAPBR=2,1"); //Get the IP
  //sendRequestByGSM();
  //POUR LIRE --> GET
  //sendCommand("AT+HTTPINIT");//Initialisation
  //sendCommand("AT+HTTPPARA=\"CID\",1");//Set parameters for HTTP session
  //sendCommand("AT+HTTPPARA=\"URL\",\"http://rucher.polytech.unice.fr/~cpeter/exemple.html\"");//GET Data
  //sendCommand("AT+HTTPACTION=0"); //GET session start / GET successfully
  //sendCommand("AT+HTTPREAD"); //Read the data of HTTP server
  //sendCommand("AT+HTTPTERM");//Terminer
  //sendCommand("AT+SAPBR=0,1");//To close bearer --> GSM COM CLOSE
  
void sendRequestByGSM(const char* url){
  sendCommand("AT+HTTPINIT");  // Initialisation
  sendCommand("AT+HTTPPARA=\"CID\",1");  // Set parameters for HTTP session
  String urlCommand = "AT+HTTPPARA=\"URL\",\"";
  urlCommand += url;
  urlCommand += "\"";
  sendCommand(urlCommand.c_str());  // GET Data
  sendCommand("AT+HTTPACTION=0");  // GET session start / GET successfully
  sendCommand("AT+HTTPREAD");  // Read the data of HTTP server
}