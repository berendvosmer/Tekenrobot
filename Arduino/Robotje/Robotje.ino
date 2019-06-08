#include <AFMotor.h>
#include <Servo.h> 
#include <AccelStepper.h>
#include <MultiStepper.h>


const float pen_offset = 56.75; //right is positive
const float wheel_diameter = 42.436;
const float half_track_width = 40.05;//39.89;39.875

const float steps_per_rev = 4096;
const float steps_per_mil = steps_per_rev / (wheel_diameter * 2.0 * PI);
const int pen_up = 150;
const int pen_down = 10;

float pivot_point = 0; //right is positive

AF_Stepper motor1(steps_per_rev, 1);
AF_Stepper motor2(steps_per_rev, 2);

MultiStepper multi_stepper;

void forwardstep1() {  
  motor1.onestep(FORWARD, SINGLE);
}
void backwardstep1() {  
  motor1.onestep(BACKWARD, SINGLE);
}
// wrappers for the second motor!
void forwardstep2() {  
  motor2.onestep(BACKWARD, SINGLE);
}
void backwardstep2() {  
  motor2.onestep(FORWARD, SINGLE);
}

// Motor shield has two motor ports, now we'll wrap them in an AccelStepper object
AccelStepper leftstepper(forwardstep1, backwardstep1);
AccelStepper rightstepper(forwardstep2, backwardstep2);

Servo pen;

void runSpeedToPosition() {
  while (!(leftstepper.distanceToGo() == 0) || !(rightstepper.distanceToGo() == 0)) {
    multi_stepper.runSpeedToPosition();
  }
  
}
void penUp() {
  pen.write(pen_up);
  delay(500);
}

void penDown() {
  pen.write(pen_down);
  delay(500);
}

void right(uint8_t degrees) {
  float radians = DEG_TO_RAD * degrees ;
  float distance_right_wheel = radians * (half_track_width + pivot_point);
  float distance_left_wheel = - radians * (half_track_width - pivot_point);
  long steps_left = long (distance_left_wheel * steps_per_mil);
  long steps_right = long (distance_right_wheel * steps_per_mil);

  long target[2]; 
  target[0] = leftstepper.currentPosition() + steps_left;
  target[1] = rightstepper.currentPosition() + steps_right;
  
  multi_stepper.moveTo(target);
  runSpeedToPosition();
}

void left(uint8_t degrees) {
  float radians = DEG_TO_RAD * degrees ;
  float distance_right_wheel = - radians * (half_track_width + pivot_point);
  float distance_left_wheel = radians * (half_track_width - pivot_point);
  long steps_left = long (distance_left_wheel * steps_per_mil);
  long steps_right = long (distance_right_wheel * steps_per_mil);

  long target[2]; 
  target[0] = leftstepper.currentPosition() + steps_left;
  target[1] = rightstepper.currentPosition() + steps_right;
  
  multi_stepper.moveTo(target);
  runSpeedToPosition();
}

void forward(uint16_t millimeters) {
  long steps = millimeters * steps_per_mil;  
  long target[2]; 
  target[0] = leftstepper.currentPosition() + steps;
  target[1] = rightstepper.currentPosition() + steps;
  
  multi_stepper.moveTo(target);

  runSpeedToPosition();
}

void backward(uint16_t millimeters) {
  long steps = millimeters * steps_per_mil;

  long target[2]; 
  target[0] = leftstepper.currentPosition() - steps;
  target[1] = rightstepper.currentPosition() - steps;
  
  multi_stepper.moveTo(target);
  runSpeedToPosition();

}


void release() {
  motor1.release();
  motor2.release();
}
  

void setPivotOnPen() {
  pivot_point = pen_offset;
}

void setPivotOnCenter() {
  pivot_point = 0;
}

void reset() {
  leftstepper.setCurrentPosition(0);
  rightstepper.setCurrentPosition(0);
  penUp();
}

void setup() {
  // put your setup code here, to run once:
  leftstepper.setMaxSpeed(300.0);
  leftstepper.setAcceleration(100.0);
  rightstepper.setMaxSpeed(300.0);
  rightstepper.setAcceleration(100.0);

  multi_stepper.addStepper(leftstepper);
  multi_stepper.addStepper(rightstepper);
  pen.attach(9);  

// Give the robot instructions below using the functions provided

setPivotOnPen();
penDown();
int i;
for (i=1;i<16;i++) {
  forward(100);
  right(95);
}
setPivotOnCenter();
penUp();
release();
}


void loop() {
  // put your main code here, to run repeatedly:


}
