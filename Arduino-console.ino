#define TRIGGER 12
#define ECHO 14
// NodeMCU Pin D6 > TRIGGER | Pin D5 > ECHO
#define BLYNK_PRINT Serial 
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
// You should get Auth Token in the Blynk App.
char auth[] = "TYi8HDKp7YEq_XqIIWEOrm5RhjroaAwG";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "pop";
char pass[] = "pop12345";
#define DHTPIN 16 // Digital pin 0
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21 // DHT 21, AM2301
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. 
// This means that you define how often to send data to Blynk App.
void sendSensor()
{
float h = dht.readHumidity();
float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return;
}
// You can send any value at any time.
Blynk.virtualWrite(V6, h); //V5 is for Humidity
Blynk.virtualWrite(V7, t); //V6 is for Temperature
}
void setup() {
Serial.begin (9600);
Blynk.begin(auth, ssid, pass);
pinMode(TRIGGER, OUTPUT);
pinMode(ECHO, INPUT);
pinMode(15, OUTPUT);
pinMode(BUILTIN_LED, OUTPUT);
dht.begin();
// Setup a function to be called every second
timer.setInterval(1000L, sendSensor);
}
void loop() {
long duration, distance;
digitalWrite(TRIGGER, LOW);
delayMicroseconds(2);
digitalWrite(TRIGGER, HIGH);
delayMicroseconds(10);
digitalWrite(TRIGGER, LOW);
duration = pulseIn(ECHO, HIGH);
distance = (duration/2) / 29.1;
if (distance <= 100) {
Blynk.virtualWrite(V0, 255);
}
else {
Blynk.virtualWrite(V0, 0);
}
if (distance <= 80) {
Blynk.virtualWrite(V1, 255);
}
else {
Blynk.virtualWrite(V1, 0);
}
if (distance <= 60) {
Blynk.virtualWrite(V2, 255);
}
else {
Blynk.virtualWrite(V2, 0);
}
if (distance <= 40) {
Blynk.virtualWrite(V3, 255);
}
else {
Blynk.virtualWrite(V3, 0);
}
if (distance <= 20) {
digitalWrite(15, HIGH);
delay(3000);
digitalWrite(15, LOW);
Blynk.virtualWrite(V4, 255);
Blynk.email("Lospolloshermanos696969@gmail.com", "Flood Alert", " Warning!! Flood
level 100cm please stay off of bridges over fast moving water");
Blynk.notify("Flood Alert - water level above 100cm");
}
else {
Blynk.virtualWrite(V4, 0);
}
Serial.print(distance);
Serial.println("Centimeter:");
Blynk.virtualWrite(V5, distance);
delay(200);
Blynk.run();
timer.run(); // Initiates SimpleTimer
}
