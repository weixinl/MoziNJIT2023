#include <IRremote.h>
#include <AccelStepper.h>

#define MotorInterfaceType 4

const int irReceiverPin = 13; // digital in
const int moiAo = 0; // analog in
const int moiDo = 6; // digital in 
IRrecv irrecv(irReceiverPin);
decode_results results;
AccelStepper left(MotorInterfaceType, 2, 4, 3, 5);
AccelStepper right(MotorInterfaceType, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600); 
  irrecv.enableIRIn();
  
  left.setMaxSpeed(500.0);
  left.setAcceleration(100.0);
  //left.setSpeed(500.0);
  
  right.setMaxSpeed(500.0);
  right.setAcceleration(100.0);
  //right.setSpeed(-500.0);

  left.moveTo(10);
  right.moveTo(-10);
}
void loop() {

  //Serial.println(analogRead(moiAo));

  if (irrecv.decode(&results)) { 
    Serial.print("irCode: ");
    Serial.print(results.value, HEX);
    //Serial.print(", bits: ");
    //Serial.println(results.bits);
    irrecv.resume();
  } 
  //delay(600);
  int leftnext = left.currentPosition();
  int rightnext = right.currentPosition();
  if(results.value == 0xFF18E7) { // 2, move forward
    leftnext -= 100;
    rightnext += 100;    
  } else if(results.value == 0xFF4AB5) { // 8, move back
    leftnext += 100;
    rightnext -= 100;    
  } else if(results.value == 0xFF10EF) { // 4, turn left
    leftnext += 100;
    rightnext += 100;    
  } else if(results.value == 0xFF5AA5) { // 6, turn right
    leftnext -= 100;
    rightnext -= 100;    
  } else if (results.value == 0xFF38C7) { // 5, stop
    
  }
  left.moveTo(leftnext);
  right.moveTo(rightnext);
  left.run();
  right.run();

}
