
#include <Servo.h> 
 
Servo servo[8];    // create servo object to control a servo (max 8) 

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int status[10];

void setup() 
{ 
  servo[0].attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
} 
 
 
void loop() { 
  while (Serial.available() > 0) {
    int mode = Serial.parseInt();
    int device = Serial.parseInt(); 
    int command = Serial.parseInt();
    if (Serial.read() == ';') {
      switch(mode) {
        // print status
        case 0:
          for (int i = 0; i < 10; i++) {
            Serial.print(i);
            Serial.print(":");
            Serial.print(status[i]);
            Serial.println(";");
          }
          break;
        // move servo
        case 1:
          device = constrain(device, 0, 2);
          command = constrain(command, 0, 255);
          servo[device].write(command);
          status[0+device] = command;
          Serial.print("servo ");
          Serial.print(device);
          Serial.print(" to ");
          Serial.println(command);
          break;
        // fire gun
        case 2:
          device = constrain(device, 0, 0);
          Serial.print("STUB");
          Serial.print("gun ");
          Serial.print(device);
          Serial.print(" for ");
          Serial.print(command);
          Serial.println("s");
          break;
        // switch laser
        case 3:
          device = constrain(device, 0, 2);
          break;
        default:
          break;
      }
    }
  }
} 
