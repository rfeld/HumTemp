/*
 * HumTemp2Plotly - Collect Humidity and Temperature measurements and push them to Plotly
 *
 * This code was started on January the 2nd 2016.
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
#include "plotly_streaming_ethernet.h"
#include "keys_tokens.h"

// Number of Plots (= Data Traces)
#define noPlots 2

// One token per Plot/Trace
char *tokens[noPlots] = {"token_1", "token_2"};

// arguments: username, api key, streaming tokens, filename, number of Plots/Traces
plotly graph = plotly("plotly_username", "plotly_api_key", tokens, "your_filename", noPlots);

// MAC Address for Ethernetshield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte my_ip[] = { 199, 168, 222, 18 }; // google will tell you: "public ip address"

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


  graph.fileopt = "overwrite"; // See the "Usage" section in https://github.com/plotly/arduino-api for details
  bool success;
  success = graph.init();
  if (!success) {
    while (true) {}
  }
  graph.openStream();
}

void loop() {
  graph.plot(millis(), analogRead(A0), tokens[0]);
  graph.plot(millis(), analogRead(A1), tokens[1]);

  delay(5000);

}
