/*
 * HumTemp2HAS - Collect Humidity and Temperature measurements and push them to the Home Automation Server
 *
 * This code was started on March the 5th 2016.
 *
 * Hardware Requirements:
 *   -Arduino
 *   -Ethernet-Shield
 *   -Humidity/Temperature Sensor(s) (DHT22)
 *
 * (c) Robert Feld
 *
 */

#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <SPI.h>


// MAC Address for Ethernetshield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte my_ip[] = { 199, 168, 222, 18 }; // google will tell you: "public ip address"
byte HAS_ip[] = { 192, 168, 178, 28 }; // IP Adress of the Home Automation Server

EthernetClient client;

void setup() {

  Serial.begin(9600);

  Serial.println("... Initializing ethernet");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("... Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, my_ip);
  }
  Serial.println("... Done initializing ethernet");
  delay(1000);

}

void loop() {
  // Try establishing a connection to the HAS
  //while(client.connect(HAS_ip, 12000) != 1)
  while(client.connect("raspberrypi2.fritz.box", 12000) != 1)
  {
    Serial.println("Error connecting to HAS! Next attempt in 5s");
    delay(5000);
  }

  Serial.println("Connected to HAS...");

  // Dummy Message: 
  String message = "*MyHomeProto;HumTemp;Schlafzimmer;450;2100;END#";

  //ToDo: Auslesen der Sensoren und Versenden der Nachrichten
  
  if(client.print(message) != message.length())
  {
    Serial.println("Es wurden nicht alle Bytes gesendet!");
  }
  else
  {
    Serial.println("Message sent");
  }

  // Disconnect
  client.flush();
  client.stop();
  
  Serial.println("Disconnected! Sending next message in 10s");
  delay(10000);
}

  


