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
int defaultAngle = 90;

int baseCurr = 90;
int baseHingeCurr = 90;
int hingeCurr = 90;
int grabberCurr = 0;

bool shouldUseKeyboard = false;

void setup() {

    // Initial Setup
    Serial.begin(9600); 
    baseServo.attach(8);  
    baseHingeServo.attach(9);
    hingeServo.attach(12);
    grabberServo.attach(13);
  
    // Set servo roations to a default of 90 degrees
    baseServo.write(defaultAngle);
    baseHingeServo.write(defaultAngle);
    hingeServo.write(defaultAngle); 
    grabberServo.write(0); 
    
}

char keyboardInput(){
    if(Serial.available() > 0){
        char key_input = Serial.read();
        Serial.println("Input: " + key_input);
        return key_input;
    }
    return '+';
}

void loop() {

    if (shouldUseKeyboard){
        // Keyboard Control
        char control = keyboardInput();
        switch(control){
            // Rotate base hinge forward
            case 'w':
                baseHingeCurr--;
                baseHingeServo.write(baseHingeCurr);
                delay(15);
                break;

            // Rotate base hinge backward
            case 's':
                baseHingeCurr++;
                baseHingeServo.write(baseHingeCurr);
                delay(15);
                break;

            // Rotate base left
            case 'a':
                baseCurr--;
                baseServo.write(baseCurr);
                delay(15);
                break;
            
            // Rotate base right
            case 'd':
                baseCurr++;
                baseServo.write(baseCurr);
                delay(15);
                break;
            
            // Rotate arm hinge forward
            case 'i':
                hingeCurr++;
                hingeServo.write(hingeCurr);
                delay(15);
                break;

            // Rotate arm hinge backward
            case 'k':
                hingeCurr--;
                hingeServo.write(hingeCurr);
                delay(15);
                break;

            // Toggle grabber
            case '\n':
            case '\r':
                grabberCurr = grabberCurr == 180 ? 0 : 180;
                grabberServo.write(grabberCurr);
                delay(15);
                break;
            
            // Ignore if no control inputs are given
            default:
                return;
        }
    }
    else{
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

}






 
