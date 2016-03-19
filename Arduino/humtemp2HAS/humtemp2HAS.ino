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
#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

#define SENSOR_ID "Schlafzimmer"

// MAC Address for Ethernetshield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte my_ip[] = { 199, 168, 222, 18 }; // google will tell you: "public ip address"
byte HAS_ip[] = { 192, 168, 178, 28 }; // IP Adress of the Home Automation Server

EthernetClient client;

DHT dht(DHTPIN, DHTTYPE);

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

  // Read Temperature Values
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");

  String Start( "*MyHomeProto;HumTemp;" );
  String End(";END#");

  String Sensor_ID( SENSOR_ID );

  String Hum(  h *  10, 0 );
  String Temp( t * 100, 0 );

  String message = Start + Sensor_ID + ";" + Hum + ";" + Temp + End;
  
  int maxAttempts = 3;
  
  // Try establishing a connection to the HAS
  //while(client.connect(HAS_ip, 12000) != 1)
  while(client.connect("raspberrypi2.fritz.box", 12000) != 1)
  {
    Serial.println("Error connecting to HAS! Next attempt in 5s");
    delay(5000);
    maxAttempts--;
    if(maxAttempts==0)
      break;
  }

  Serial.println("Connected to HAS...");

  // Dummy Message: 
  //String message = "*MyHomeProto;HumTemp;Schlafzimmer;450;2100;END#";

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

  


