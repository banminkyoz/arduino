// Example with NODEMCU ESP8266 & TB6612 DC 1.2A
//

// Define the Pins

// Motor 1
#define pinPWMA D1 //Speed
#define pinAIN1 D2 //Direction
#define pinAIN2 D3 //Direction

// Motor 2
#define pinPWMB D6 //Speed
#define pinBIN1 D7 //Direction
#define pinBIN2 D8 //Direction

//Standby
#define pinSTBY D5

// Others
#define pinLED D4 //Led 

//Constants to help remember the parameters
static boolean turnCW = 0;  //for motorDrive function
static boolean turnCCW = 1; //for motorDrive function
static boolean motor1 = 0;  //for motorDrive, motorStop, motorBrake functions
static boolean motor2 = 1;  //for motorDrive, motorStop, motorBrake functions
 
void setup() {
  motoDriverSetup();
}

void motoDriverSetup() {
  // Set the PIN Modes
  pinMode(pinPWMA, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinAIN2, OUTPUT);

  pinMode(pinPWMB, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);

  pinMode(pinSTBY, OUTPUT);

  pinMode(pinLED, OUTPUT);

  motorDrive(motor1, turnCW, 255);
  motorDrive(motor2, turnCW, 255);
  
  delay(5000);

  motorStop(motor1);
  motorStop(motor2);

}

void loop() {

  // motorDrive(motor1, turnCW, 255);
  // motorDrive(motor2, turnCW, 255);

  //delay(5000);

  //motorStop(motor1);
  //motorStop(motor1);

  digitalWrite(pinLED, HIGH);
  delay(1000);
  digitalWrite(pinLED, LOW);
  delay(1000);
  
}

// Driver Functions
void motorDrive(boolean motorNumber, boolean motorDirection, int motorSpeed) {
  /*
  This Drives a specified motor, in a specific direction, at a specified speed:
    - motorNumber: motor1 or motor2 ---> Motor 1 or Motor 2
    - motorDirection: turnCW or turnCCW ---> clockwise or counter-clockwise
    - motorSpeed: 0 to 255 ---> 0 = stop / 255 = fast
  */

  boolean pinIn1;  //Relates to AIN1 or BIN1 (depending on the motor number specified)

  // Specify the Direction to turn the motor
  // Clockwise: AIN1/BIN1 = HIGH and AIN2/BIN2 = LOW
  // Counter-Clockwise: AIN1/BIN1 = LOW and AIN2/BIN2 = HIGH
  if (motorDirection == turnCW)
    pinIn1 = HIGH;
  else
    pinIn1 = LOW;

  // Select the motor to turn, and set the direction and the speed
  if(motorNumber == motor1) {
    digitalWrite(pinAIN1, pinIn1);
    digitalWrite(pinAIN2, !pinIn1);  //This is the opposite of the AIN1
    analogWrite(pinPWMA, motorSpeed);
  } else {
    digitalWrite(pinBIN1, pinIn1);
    digitalWrite(pinBIN2, !pinIn1);  //This is the opposite of the BIN1
    analogWrite(pinPWMB, motorSpeed);
  }

  // Finally , make sure STBY is disabled - pull it HIGH
  digitalWrite(pinSTBY, HIGH);

}

void motorBrake(boolean motorNumber) {
  /*
    This "Short Brake"s the specified motor, by setting speed to zero
  */
  if (motorNumber == motor1)
    analogWrite(pinPWMA, 0);
  else
    analogWrite(pinPWMB, 0);
}


void motorStop(boolean motorNumber) {
  /*
    This stops the specified motor by setting both IN pins to LOW
  */
  if (motorNumber == motor1) {
    digitalWrite(pinAIN1, LOW);
    digitalWrite(pinAIN2, LOW);
  } else {
    digitalWrite(pinBIN1, LOW);
    digitalWrite(pinBIN2, LOW);
  } 
}


void motorsStandby() {
  /*
    This puts the motors into Standby Mode
  */
  digitalWrite(pinSTBY, LOW);
}
