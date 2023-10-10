#ifndef MY_COMMANDS_H
#define MY_COMMANDS_H

#include <Arduino.h>
#include <WiFi.h>

void sendCommand(String myCommand, long baudSerial, long baudSerial2);
void sendCommand(String myCommand);
void readByteSerial2();

//---------------------------------------------------------------------------//
//<<--- FONCTINO POUR ENVOYER UNE COMMANDE --->>
void sendCommand(String myCommand, long baudSerial, long baudSerial2) {
  int TX = 16;
  int RX = 17;
  Serial.begin(baudSerial);
  Serial2.begin(baudSerial2, SERIAL_8N1, TX, RX);

  Serial.println("Starting...");
  Serial2.println(myCommand);
  delay(1000);
}

void sendCommand(String myCommand) {
  sendCommand(myCommand, 9600, 115200);  //AJOUT DES PARAMETRES PAR DEFAUT
}
//--------------------------------------------------------------------------//
//<<---FONCTION POUR LIRE TOUS LES BYTES DISPONIBLES SUR LE PORT SERIAL2-->>
void readByteSerial2() {
  while (Serial2.available()) {
    // Lire des nouveaux bytes:
    Serial.print((char)Serial2.read());
  }
}
//--------------------------------------------------------------------------//
//<<-------------- FONCTION POUR ENVOYER UN MESSAGE / SMS ----------------->>
void sendMessage(const char* numero, const char* texte) {

  sendCommand("AT+CMGF=1");  //Activation mode texte
  String command = "AT+CMGS=\"";
  command += numero;
  command += "\"";
  sendCommand(command);
  delay(1000);

  Serial2.print(texte);
  //sendCommand(texte);
  Serial2.write(26);  // Envoi de Ctrl-Z pour indiquer la fin du message
  delay(1000);
  Serial.println("SMS envoyé avec succès !");
  delay(2000);
  sendCommand("AT+CMGD=1");  // Desactivation mode texte
}
//--------------------------------------------------------------------------//
//<<-------------- FONCTION POUR LIRE UN MESSAGE / SMS ------------------->>
void readMessage() {
  sendCommand("AT+CMGF=1");        // Activation du mode texte
  sendCommand("AT+CMGL=\"ALL\"");  // Lire tous les messages SMS

  while (Serial2.available()) {
    String response = Serial2.readStringUntil('\n');
    Serial.println(response);
  }

  delay(1000);
  sendCommand("AT+CMGD=1,4");  // Supprimer tous les messages SMS lus
  sendCommand("AT+CMGF=0");    // Désactivation du mode texte
}
//--------------------------------------------------------------------------//
//<<----------------- FONCTION POUR LA CONNEXION WiFi -------------------->>//
void myWiFi(const char* ssid, const char* password) {

  Serial.begin(9600);

  Serial.printf("Tentative de connexion à %s\n", ssid);
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au réseau en cours...");
    attempts++;
    if (attempts > 10) {
      Serial.println("Échec de la connexion au réseau Wi-Fi.");
      while (1) {
        // Boucle infinie
      }
    }
  }

  Serial.println("Connecté au réseau Wi-Fi");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Force du signal (RSSI) : ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}
//--------------------------------------------------------------------------//
//<<----------------- FONCTION POUR ETABLIR LA CONNEXION ------------------>>//
void establishConnection(String dataType, String IPorDomain, String portIN) {
  Serial2.println("AT+CIPSTART=\"" + dataType + "\",\"" + IPorDomain + "\"," + portIN);
  delay(1000);

  while (Serial2.available()) {
    String response = Serial2.readStringUntil('\n');
    Serial.println(response);
    if (response.indexOf("OK") != -1 || response.indexOf("ALREADY CONNECTED") != -1) {
      Serial.println("Connexion établie avec succès !");
      return;
    } else if (response.indexOf("ERROR") != -1) {
      Serial.println("Erreur lors de l'établissement de la connexion.");
      return;
    }
  }
}
//--------------------------------------------------------------------------//
//<<---------------- FONCTION POUR ENVOYER DES DONNEES ------------------->>//
void sendData(int datasize) {
  Serial2.println("AT+CIPSEND=\"" + datasize);
  delay(1000);

  while (Serial2.available()) {
    String response = Serial2.readStringUntil('\n');
    Serial.println(response);
    if (response.indexOf("OK") != -1 || response.indexOf("DEJA ENVOYE") != -1) {
      Serial.println("Donnees envoyees avec succès !");
      return;
    } else if (response.indexOf("ERROR") != -1) {
      Serial.println("Erreur lors de l'envoi des donnees.");
      return;
    }
  }
}

//CONNAITRE SI LE PACKET EST RECU OU PAS

void testCIPSRIPCommand() {
  // Envoi de la commande AT+CIPSRIP=?
  Serial2.println("AT+CIPSRIP=?");

  // Attente de la réponse
  delay(1000);  // Attendez un certain temps pour que la réponse soit reçue

  // Lecture de la réponse
  while (Serial2.available()) {
    String response = Serial2.readStringUntil('\n');
    if (response.startsWith("+CIPSRIP: ")) {
      // Affichez la liste des modes pris en charge
      Serial.print("Supported Modes: ");
      Serial.println(response.substring(10));
    } else if (response == "OK") {
      // Commande réussie
      Serial.println("Commande AT+CIPSRIP=? exécutée avec succès.");
    }
  }
}
/*********************************************************************/
// --- ETABLISSEMENT DE LA CONNEXION ---  //

void startConnexion() {
  int myAttente = 5000;
/*
  Serial.println("1. Step 1 : Data Services status ");
  sendCommand("AT+CGATT?");
  delay(myAttente); */
/*
  Serial.println("2. Step 2: Enable multi connection ");
  sendCommand("AT+CIPMUX=1");
  delay(myAttente); */


  Serial.println("3. Step 3: Start task and set APN. ");
  sendCommand("AT+CSTT=\"CMNET\"");
  delay(myAttente); /*

  Serial.println("4. Step 4: Bring up wireless connection ");
  sendCommand("AT+CIICR");
  delay(myAttente);

  Serial.println("5. Step 5: Get local IP address ");
  sendCommand("AT+CIFSR");
  delay(myAttente);

/*
  Serial.println("6. Step 6: Establish a TCP connection, connection number 0 ");
  sendCommand("AT+CIPSTART=0,\"TCP\",\"45.77.46.150\",\"8500\"");  //Update port ID
  delay(myAttente); */
/*
  Serial.println("7. Step 7: Establish a UDP connection, connection number 1");
  sendCommand("AT+CIPSTART=1,\"UDP\",\"45.77.46.150\",\"9991\"");
  delay(myAttente); */

/*
  Serial.println("8. Step 8: Send data to connection 0");
  sendCommand("AT+CIPSTART=0");
  delay(myAttente/2);
  sendCommand("TCP test");
  delay(myAttente); */
/*
  Serial.println("9. Step 9: Send data to connection 1");
  sendCommand("AT+CIPSTART=1");
  delay(myAttente/2);
  sendCommand("UDP test");
  delay(myAttente);

  Serial.println("10. Step 10: Status");
  sendCommand("AT+CIPSTATUS"); */
}



#endif
