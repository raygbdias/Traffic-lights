#include <Servo.h>
int pedestrian01 = A0;    //Set A0(Analog Input) for LDR.
int pedestrianLED01 = 8;  //LED for the pedestrian01
int pedestrian02 = A1;      // A1 for parking
int parkingLED = 9;       // LED for barrier
Servo myServo;
const int buttonGate = 11; //variable that wont change for the servo

int pedestrian;  //Read the value of the LDR pedestrian01
int pedestrians;  //Read the value of the LDR pedestrian02
int parking;  //Read the value of the LDR
int dl = 250;    //delay for LDR
int ds = 1000;   //delay for tarffic lights
int servoPin = 10;
int L1Red = 2;
int L1Yellow = 3;
int L1Green = 4;
int L2Red = 5;
int L2Yellow = 6;
int L2Green = 7;
int buttonState = 0;  // variable for reading the pushbutton status
void setup() {
  // put your setup code here, to run once:
  pinMode(pedestrian01, INPUT); //LDR is an Input
  pinMode(pedestrian02, INPUT); //LDR is an Input
  Serial.begin(9600); //starting the serial monitor

  pinMode(buttonGate, INPUT); //button is an input 

  pinMode(servoPin, OUTPUT); //servo motor is an output
  myServo.attach(servoPin);

  pinMode(L1Red, OUTPUT);
  pinMode(L1Yellow, OUTPUT);
  pinMode(L1Green, OUTPUT);
  pinMode(L2Red, OUTPUT);
  pinMode(L2Yellow, OUTPUT);   //all Led will be output
  pinMode(L2Green, OUTPUT);
  pinMode(pedestrianLED01, OUTPUT);
  pinMode(parkingLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  pedestrian01 = analogRead(pedestrian);  //Reads the Value of LDR(light).
  pedestrian02 = analogRead(pedestrians);  //Reads the Value of LDR(light).
  parking = digitalRead(buttonState);    //Reads the Value of LDR(gate).
  Serial.println("Pedestre01");
  delay(ds);
  Serial.println(pedestrian01);  //Prints the value of LDR to Serial Monitor.
  delay(ds);
  Serial.println("Pedestre02");
  delay(ds);
  Serial.println(pedestrian02);  //Prints the value of LDR to Serial Monitor.
  delay(ds);
  Serial.println("Gate");
  delay(ds);
  Serial.println(buttonState);  //Prints the value of LDR to Serial Monitor.

  if (pedestrian01 > 100||pedestrian02 > 100) { //LDR not covered  //main traffic light
    digitalWrite(L1Green, HIGH);   //WHEN ITS HIGH IT WILL TURN ON THE LED WHEN IT'S LOW IT WILL TURN OFF LED
    digitalWrite(L2Red, HIGH);
    
  } else {
    digitalWrite(L1Green, LOW); 
    delay(ds);
    digitalWrite(L1Yellow, HIGH);
    delay(ds);
    digitalWrite(L1Yellow, LOW);
    delay(ds);
    digitalWrite(L1Red, HIGH);
    digitalWrite(pedestrianLED01, HIGH);
    delay(5000);   //big delay for the pedestrian to cross the street
    digitalWrite(L1Red, LOW);
    digitalWrite(pedestrianLED01, LOW);
    return; //end the condition 
  }
  buttonState = digitalRead(buttonGate);   // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {  //gate opening depending of the result  //LDR covered
    digitalWrite(L1Green, HIGH);
    digitalWrite(L2Red, HIGH);
    digitalWrite(L1Red, LOW);
    digitalWrite(L2Green, LOW);
    digitalWrite(parkingLED, LOW);
    myServo.write(0);   //sets the servo motor to 0 
  } else {
    digitalWrite(L1Green, LOW);
    delay(ds);
    digitalWrite(L1Yellow, HIGH);
    delay(ds);
    digitalWrite(L1Yellow, LOW);
    delay(ds);
    digitalWrite(L1Red, HIGH);
    delay(ds);
    digitalWrite(L2Red, LOW);
    delay(ds);
    digitalWrite(parkingLED, HIGH);
    digitalWrite(L2Green, HIGH);
    delay(ds);
    myServo.write(360);   //set the servo motor to a different position 
    return; // ends the condition
  }
}
