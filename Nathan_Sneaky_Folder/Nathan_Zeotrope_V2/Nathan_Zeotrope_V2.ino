/**
  Project Name: Arduino Projects Book - Project 10: Zoetrope

  File Name: zoetrope.ino

  Description: Controls the speed and the direction of the DC motor using
  two switches and a potentiometer.

  Author: Phi Luu
  Location: Portland, Oregon, United States
  Created: August 21, 2016
  Updated: June 22, 2017
*/
// Required hardware I/O connections
const byte POT_PIN              = A0; // connect potentiometer to A0
const byte IC_INPUT_1           = 3;  // connect IC Input1 to ~3
const byte IC_INPUT_2           = 4;  // connect IC Input2 to 4
const byte IC_ENABLE_1          = 9;  // connect IC Enable1 t ~9
const byte DIRECTION_SWITCH_PIN = 4;  // connect direction switch to 4
const byte STATE_SWITCH_PIN     = 5;  // connect state switch to ~5
// Global variables
byte state_switch_val          = 0;   // state switch
byte direction_switch_val      = 0;   // direction switch
byte prev_state_switch_val     = 0;   // previous state switch
byte prev_direction_switch_val = 0;   // previous direction switch
byte motor_is_enabled          = 0;   // whether the motor is on/off
byte motor_direction           = 0;   // motor direction
unsigned short motor_speed     = 0;
volatile byte half_revolutions;
unsigned int rpm;
unsigned long timeold;
int old_value = 0;
int new_value;
int time_flash;
int count;
int spacing;
//int bro = 10;
//int nas = 11;
void setup() {
  pinMode(DIRECTION_SWITCH_PIN, INPUT);
  pinMode(STATE_SWITCH_PIN,     INPUT);
  pinMode(IC_INPUT_1,           OUTPUT);
  pinMode(IC_INPUT_2,           OUTPUT);
  pinMode(IC_ENABLE_1,          OUTPUT);
  pinMode(10, INPUT);
  pinMode(11, OUTPUT);
  Serial.begin(115200);
  attachInterrupt(0, magnet_detect, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)
  half_revolutions = 0;
  rpm = 0;
  timeold = 0;
  count = 10;
}
void loop() {

  state_switch_val = digitalRead(STATE_SWITCH_PIN);
  delay(1);
  direction_switch_val = digitalRead(DIRECTION_SWITCH_PIN);
  motor_speed          = analogRead(POT_PIN) / 4;

  //    if (bro == HIGH) {
  //      digitalWrite(11, LOW);
  //    }
  //    else;{
  //      digitalWrite(11, HIGH);
  //    }

  if (half_revolutions >= 20) {
    rpm = 30 * 1000 / (millis() - timeold) * half_revolutions;
    timeold = millis();
    half_revolutions = 0;
    //Serial.println(rpm,DEC);
  }

  // process the on/off state of the motor from the state switch
  if (state_switch_val != prev_state_switch_val) {
    if (state_switch_val) {
      motor_is_enabled = !motor_is_enabled;
    }
  }
  // process the direction of the motor from the direction switch
  if (direction_switch_val != prev_direction_switch_val) {
    if (direction_switch_val) {
      motor_direction = !motor_direction;
    }
  }
  // control the direction of the motor using the IC
  if (motor_direction) {
    digitalWrite(IC_INPUT_1, LOW);
    digitalWrite(IC_INPUT_2, HIGH);
  } else {
    digitalWrite(IC_INPUT_1, HIGH);
    digitalWrite(IC_INPUT_2, LOW);
  }
  // control the on/off state of the motor using PWM
  if (motor_is_enabled) {
    analogWrite(IC_ENABLE_1, motor_speed);
  } else {
    analogWrite(IC_ENABLE_1, 0);
  }
  // prep for next inputs
  prev_state_switch_val     = state_switch_val;
  prev_direction_switch_val = direction_switch_val;
}
void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
{
  half_revolutions++;
  count = 10;
  new_value = millis();
  time_flash = new_value - old_value;
  old_value = new_value;
  Serial.println(time_flash);
  (time_flash - 500) / 10 == spacing;

  flash(spacing);
  {
    while (count > 0);
    {
      digitalWrite(11, LOW);
      delay(spacing);
      digitalWrite(11, HIGH);
      delay(50);
      count = count - 1;
    }


  }

  // digitalWrite(11, LOW);
  // Serial.println(millis());
  // delay(50);
  // digitalWrite(11, HIGH);
}
