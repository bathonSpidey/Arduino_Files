/* Code Abir Bhattcharyya 24107 behavior using field and subsumption
 */
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <hcsr04.h>
#define TRIG_PIN 12
#define ECHO_PIN 13
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(3);
HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);
void setup() {
  int releaserLeft= 500;
  int releaserRight=500;
  int obstacle= 100;
  // put your setup code here, to run once:
  Serial.begin(9600);
  AFMS.begin();
  myMotor->setSpeed(0);
  myOtherMotor->setSpeed(0);
  myMotor->run(FORWARD);
  myOtherMotor->run(FORWARD);
}
/*Filed generations*/
int avoidObs(int obstacle){
   unsigned int ultra= hcsr04.distanceInMillimeters();
   if (ultra<=obstacle){
    return 0; 
   }
   else{
    return 1;
   }
}
int followLightLeft(int releaserLeft){
  int leftSensorVal=analogRead(A1);
  if (leftSensorVal<=releaserLeft){
    return 0;
  }
  else{
    return 1;
  }
}
int followLightRight(int releaserRight){
  int rightSensorVal=analogRead(A3);
  if (rightSensorVal<=releaserRight){
    return 0;
  }
  else{
    return 1;
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  int releaserLeft= 500;
  int releaserRight=500;
  int obstacle= 100;
  int checkObstacle= avoidObs(obstacle);
  int checkLL= followLightLeft(releaserLeft);
  int checkLR= followLightRight(releaserRight);
  Serial.println(checkObstacle);
  Serial.println(checkLL);
  Serial.println(checkLR);
  /*subsumption method using fields*/
  if(checkObstacle==0){
    myMotor->setSpeed(250);
    myOtherMotor->setSpeed(250);
    myMotor->run(FORWARD);
    myOtherMotor->run(FORWARD);
    delay(2000);
  }
  else if (checkLL==1 && checkLR==1 && checkObstacle==1){
    myMotor->setSpeed(250);
    myOtherMotor->setSpeed(250);
    myMotor->run(BACKWARD);
    myOtherMotor->run(BACKWARD);
  }
  else if(checkLL==0 && checkLR==1 && checkObstacle==1){
    myMotor->setSpeed(250);
    myOtherMotor->setSpeed(250);
    myMotor->run(BACKWARD);
    myOtherMotor->run(FORWARD);
  }
  else if (checkLL==1 && checkLR==0 && checkObstacle==1){
    myMotor->setSpeed(250);
    myOtherMotor->setSpeed(250);
    myMotor->run(FORWARD);
    myOtherMotor->run(BACKWARD);
  }
  else{
    myMotor->setSpeed(50);
    myOtherMotor->setSpeed(50);
    myMotor->run(BACKWARD);
    myOtherMotor->run(BACKWARD);
}
}

