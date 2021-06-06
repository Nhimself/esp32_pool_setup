/*
Made by Niki Mench

Included code from Blynk, dallas temperature examples. 
*/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>

BlynkTimer timer;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup()
{
  // Debug console
  Serial.begin(9600); 
  sensors.begin();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getTemperatur);
  //timer.setInterval(1000L, sendUptime);
}

void sendUptime()
{
  Blynk.virtualWrite(V5, millis() / 1000);
}

void getTemperatur()
{
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  int Temp = tempC;
  Blynk.virtualWrite(V0, Temp);
  Serial.println(Temp);
  /*if(tempC != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Temperature is: ");
    Serial.println(tempC);
  } 
  else
  {
    Serial.println("Error: Could not read temperature data");
    
  }
  */
}

void loop()
{
  Blynk.run();
  timer.run();
}
