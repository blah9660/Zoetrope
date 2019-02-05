#define forward 1
#define reverse 0
unsigned long old_value = 0;
unsigned long new_value;
int time_flash;
unsigned long TP = 0;
int spacing;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), detect, FALLING);
}

void loop() {
  motor(reverse);
  int sensorValue = analogRead(A0) / 4;
  //Serial.println(sensorValue);
  analogWrite(3, sensorValue);
  if (millis() >= TP) {
    TP = millis();
    TP = TP + spacing;
    flash();
  }


}

void motor(int spin) {
  if (spin == forward)
  {
    digitalWrite(4, HIGH);
  }
  if (spin == reverse)
  {
    digitalWrite(4, LOW);
  }
}

void detect() {
  new_value = millis();
  time_flash = new_value - old_value;
  old_value = new_value;
  Serial.println(time_flash);
  spacing = (time_flash) / 12;
}

void flash() {
  digitalWrite(11, HIGH);
  delayMicroseconds(1000);
  digitalWrite(11, LOW);
}
