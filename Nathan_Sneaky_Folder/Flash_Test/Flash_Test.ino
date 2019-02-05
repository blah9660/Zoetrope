unsigned long TP = 0;
int old_value = 0;
int new_value;
int time_flash;
int spacing;

void setup() {
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (millis() >= TP) {
    TP = millis();
    TP = TP + 100;
    Serial.println(TP);
    flash();
  }
}

void flash() {
      digitalWrite(11, LOW);
      delayMicroseconds(1000);
      digitalWrite(11, HIGH);
}
