#include <WiFi.h>
#include <ThingSpeak.h>
#include <stdio.h>
const int trigPin = 15; //D15
const int echoPin = 2; //D2
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
long duration;
float distanceCm;
float distanceInch;
char ssid[] = "vivo T1 5G";
char pass[] = "achuchuchu";
WiFiClient client;
unsigned long myChannelNumber =2538359;
const char * myWriteAPIKey = "SXBNFIKC6QY18MIU";
int statusCode;
void setup()
{
Serial.begin(115200);
WiFi.mode(WIFI_STA);
ThingSpeak.begin(client);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}
void loop()
{
if (WiFi.status() != WL_CONNECTED)
{
 Serial.print("Attempting to connect to SSID: ");
 Serial.println(ssid);
 while (WiFi.status() != WL_CONNECTED)
 {
 WiFi.begin(ssid, pass);
 Serial.print(".");
 delay(5000);
 }
 Serial.println("\nConnected.");
}

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanceCm = duration * SOUND_VELOCITY/2;
distanceInch = distanceCm * CM_TO_INCH;
Serial.print("Distance = ");
Serial.print(distanceCm);
Serial.println(" cm");
delay(10);
 // Send distance measurement to ThingSpeak
  ThingSpeak.writeField(myChannelNumber, 1, distanceCm, myWriteAPIKey);

  delay(1000); // Wait for 10 seconds before sending next measurement
}