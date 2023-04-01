// ultrasonic receivers
const int ultrasonic_trigpins[] = {12, 10};
// ultrasonic senders
const int ultrasonic_echopins[] = {13, 11};
const int ultrasonic_num = 2;
// defines variables
long duration;
int distance;
void setup() 
{
  for(int i = 0; i < ultrasonic_num; ++ i)
  {
    pinMode(ultrasonic_trigpins[i], OUTPUT); // Sets the trigPin as an Output
    pinMode(ultrasonic_echopins[i], INPUT); // Sets the echoPin as an Input
  }
  Serial.begin(9600); // Starts the serial communication
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
    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    Serial.print("Ultrasonic#");
    Serial.print(i);
    Serial.print(" , Distance: ");
    Serial.println(distance);
  }
}
