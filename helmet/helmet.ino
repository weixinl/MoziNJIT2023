#include "pitches.h"
#include "themes.h"
#include "ArduinoJson.h"
#include <SoftwareSerial.h>
#define RXpin 5
#define TXpin 4
// ultrasonic receivers
const int ultrasonic_trigpins[] = {12, 10, 8, 6};
// ultrasonic senders
const int ultrasonic_echopins[] = {13, 11, 9, 7};
const int ultrasonic_num = 4;
int left_front_i = 0;
int left_rear_i = 1;
int right_front_i = 2;
int right_rear_i = 3;
const int buzzer_pins[] = {3, 2};
const int buzzer_num = 2;
int buzzer_left_i = 0;
int buzzer_right_i = 1;
int distances[] = {0, 0, 0, 0};
const int DANGER_DISTANCE = 1000; // mm
const int serialoutpin = 4;

// defines variables
long duration;
int distance;
SoftwareSerial Serial1(RXpin, TXpin); // RX, TX
void setup() 
{
  for(int i = 0; i < ultrasonic_num; ++ i)
  {
    pinMode(ultrasonic_trigpins[i], OUTPUT); // Sets the trigPin as an Output
    pinMode(ultrasonic_echopins[i], INPUT); // Sets the echoPin as an Input
  }
  for(int i = 0; i < buzzer_num; ++ i)
  {
    pinMode(buzzer_pins[i], OUTPUT);
  }
  Serial.begin(9600); // Starts the serial communication
  Serial1.begin(9600);
}
void loop() 
{
  // Clears the trigPins
  for(int i = 0; i < ultrasonic_num; ++ i)
  {
    digitalWrite(ultrasonic_trigpins[i], LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(ultrasonic_trigpins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonic_trigpins[i], LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(ultrasonic_echopins[i], HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // mm
    // Prints the distance on the Serial Monitor
    Serial.print("Ultrasonic#");
    Serial.print(i);
    Serial.print(" , Distance: ");
    Serial.println(distance);
    distances[i] = distance;
  }
    // Create the JSON document
  StaticJsonDocument<200> doc;
  doc["lf"] = distances[0];
  doc["lr"] = distances[1];
  doc["rf"] = distances[2];
  doc["rr"] = distances[3];
  // Send the JSON document over the "link" serial port
  serializeJson(doc, Serial1);

  if(distances[left_front_i] < DANGER_DISTANCE || distances[left_rear_i] < DANGER_DISTANCE)
  {
    if(distances[left_front_i] < distances[left_rear_i])
      ring4front(buzzer_pins[buzzer_left_i]);
    else
      ring4rear(buzzer_pins[buzzer_left_i]);
  }
  if(distances[right_front_i] < DANGER_DISTANCE || distances[right_rear_i] < DANGER_DISTANCE)
    {
      if(distances[right_front_i] < distances[right_rear_i])
        ring4front(buzzer_pins[buzzer_right_i]);
      else
        ring4rear(buzzer_pins[buzzer_right_i]);
    }
}

void ring4front(int buzzer_pin)
{
  tone(buzzer_pin, 1000);
  delay(500);
  noTone(buzzer_pin);
  delay(500);
}

void ring4rear(int buzzer_pin)
{
  tone(buzzer_pin, 1000);
  delay(150);
  noTone(buzzer_pin);
  delay(200);
  tone(buzzer_pin, 1000);
  delay(150);
  noTone(buzzer_pin);
  delay(500);
}
