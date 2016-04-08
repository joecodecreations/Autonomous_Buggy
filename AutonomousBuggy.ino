int steeringMotor = 3;
int leftMotor = 6;
int rightMotor = 9;
int sensorPin = A0;
boolean wheelsRight;
boolean wheelsLeft;
boolean triedLeft;
boolean triedRight;


/*
 * pwm pins for metro:3,6,9,
 * 0 is left, 255 is right
 */

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  int distance = sensorRead(); //keep this at the top of your code

  // put your main code here, to run repeatedly:

  if (distance > 150) { //if something is too close
    if (!triedLeft) { //if left hasn't been tried yet
      int oldDistance = distance;  //save the distance
      turnRight(); //turn the wheels right
      backward(300);
      turnLeft(); //turn the wheels
      forward(300);  //move a bit forward
      distance = sensorRead();
      if (distance > oldDistance) { // if the object is closer
        backward(300); //move back a bit
        triedLeft = true;
      }
      else if (distance < oldDistance) { //if the object is farther away, center the wheels
        turnStraight();
        triedLeft = false;
        triedRight = false;
      }
    }
    else if (triedLeft) { //if left has been tried, turn right
      int oldDistance = distance; // save the distance
      turnLeft();
      backward(600);
      turnRight();
      forward(300);
      distance = sensorRead();
      if (distance > oldDistance) { //if it's closer
        backward(600); //move back a bit
        triedRight = true;
      }
      else if (distance < oldDistance) { // if farther
        turnStraight();
        triedLeft = false;
        triedRight = false;
      }
    }
    else if (triedRight && triedLeft) { // if both have been tried back up a lot and turn a bit and start over
      backward(1500); //go back a lot
      turnLeft();
      backward(500);
      triedLeft = false;
      triedRight = false;

    }
  }
  else {
    forward(500);
  }

}






/*******************************************************
 *
 *
 * DO NOT TOUCH CODE BELOW THIS
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 ********************************************************
 */


void forward(int t) {
  analogWrite(leftMotor, 250);
  analogWrite(rightMotor, 10);
  delay(t);
  analogWrite(leftMotor, 0);
  analogWrite(rightMotor, 0);

}

void backward(int t) {
  analogWrite(leftMotor, 10);
  analogWrite(rightMotor, 250);
  delay(t);
  analogWrite(leftMotor, 0);
  analogWrite(rightMotor, 0);

}

void turnLeft() {
  if (wheelsRight){ //if the wheels are to the right
    analogWrite(steeringMotor,5);
    delay(200);
    analogWrite(steeringMotor,0);
    wheelsLeft = true;
    wheelsRight = false;
  }
    
  if ((!wheelsLeft) && (!wheelsRight)) {            //if wheels aren't already left or right
    analogWrite(steeringMotor, 5);  //send x pulses to turn left
    delay(100);
    analogWrite(steeringMotor, 0);
    wheelsLeft = true;
    wheelsRight = false;
  }
}


void turnRight() {
  if (wheelsLeft){
    analogWrite(steeringMotor, 250);  //send x pulses to turn right
    delay(200);
    analogWrite(steeringMotor, 0);
    wheelsRight = true;
    wheelsLeft = false;
  }
  if ((!wheelsLeft) && (!wheelsRight)) {            //if wheels aren't already right
    analogWrite(steeringMotor, 250);  //send x pulses to turn right
    delay(100);
    analogWrite(steeringMotor, 0);
    wheelsRight = true;
    wheelsLeft = false;
  }
}

void turnStraight() {
  if (wheelsRight) {            //if wheels are already right
    analogWrite(steeringMotor, 5);  //send x pulses to turn towards center
    delay(100);
    analogWrite(steeringMotor, 0);
  }
  if (wheelsLeft) {            //if wheels are already right
    analogWrite(steeringMotor, 250);  //send x pulses to turn towards center
    delay(100);
    analogWrite(steeringMotor, 0);
  }
  wheelsLeft = false;
  wheelsRight = false;
}


int sensorRead() {
  int value;
  value = analogRead(sensorPin);
  return value;
}

