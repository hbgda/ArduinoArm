#include <Arduino.h>
#include <Servo.h>

// Servo objects for controlling the position
Servo baseServo;   
Servo baseHingeServo;
Servo hingeServo;
Servo grabberServo;

// Potentiometer pin positions
int baseControl = A0;
int baseHingeControl = A1;
int hingeControl = A2;
int grabberControl = A3;

// Default angle for servos
int angle = 90; 
int angle1 = 90;
int angle2 = 90;
int angle3 = 90;
int angleStep = 5;

void setup() {

    // Initial Setup
    Serial.begin(9600); 
    baseServo.attach(8);  
    baseHingeServo.attach(9);
    hingeServo.attach(12);
    grabberServo.attach(13);
  
    // Set servo roations to a default of 90 degrees
    baseServo.write(angle);
    baseHingeServo.write(angle1);
    hingeServo.write(angle2); 
    grabberServo.write(angle3); 
    
}

void loop() {

    // Control Code
    int baseVal = analogRead(baseControl);
    float baseSetVal = map(baseVal, 0, 1023, 0, 180);
    baseServo.write(baseSetVal);
    delay(15);     

    int baseHingeVal = analogRead(baseHingeControl);
    float baseHingeSetVal = map(baseHingeVal, 0, 1023, 0, 180);
    baseHingeServo.write(baseHingeSetVal);
    delay(15);     

    int hingeVal = analogRead(hingeControl);
    float hingeSetVal = map(hingeVal, 0, 1023, 0, 180);
    baseServo.write(hingeSetVal);
    delay(15);     

    int grabberVal = analogRead(grabberControl);
    float grabberSetVal = map(grabberVal, 0, 1023, 0, 180);
    baseServo.write(grabberSetVal);
    delay(15);

}

// Will be used to control servos based on user input
char keyboardInput(){
    if(Serial.available() > 0){
        char key_input = Serial.read();
        Serial.println("Input: " + key_input);
        return key_input;
    }
}





 
