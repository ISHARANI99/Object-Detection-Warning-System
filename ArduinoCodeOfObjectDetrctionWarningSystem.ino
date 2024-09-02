 #include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  

#define trigPin1 A0
#define echoPin1 A1
#define trigPin2 A2
#define echoPin2 A3
#define trigPin3 A4
#define echoPin3 A5

int ALARM = 9;
long duration, distance, FIRSTSensor, SECONDSensor, THIRDSensor;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.clear();

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(ALARM, OUTPUT);

  digitalWrite(ALARM, LOW);
  lcd.setCursor(0, 0); lcd.print("Object Detection");
  lcd.setCursor(0, 1); lcd.print("Warning system");
  delay(3000); lcd.clear();
  lcd.setCursor(0, 0); lcd.print("3 HC-SR04");
  lcd.setCursor(0, 1); lcd.print("Ultrasonic");
  delay(3000); lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Sensors With");
  lcd.setCursor(0, 1); lcd.print("Arduino");
  delay(3000); lcd.clear();
}

void loop() {
  // Read sensor data
  SonarSensor(trigPin1, echoPin1);
  FIRSTSensor = distance;
  SonarSensor(trigPin2, echoPin2);
  SECONDSensor = distance;
  SonarSensor(trigPin3, echoPin3);
  THIRDSensor = distance;

  digitalWrite(ALARM, LOW);

  // Print sensor data to serial monitor
  Serial.print("S1: "); Serial.println(FIRSTSensor); delayMicroseconds(10);
  Serial.print("S2: "); Serial.println(SECONDSensor); delayMicroseconds(10);
  Serial.print("S3: "); Serial.println(THIRDSensor); delayMicroseconds(10);

  // Display sensor data on LCD
  lcd.setCursor(0, 0); lcd.print("R.S: "); lcd.print(FIRSTSensor);
  lcd.setCursor(9, 0); lcd.print("L.S: "); lcd.print(SECONDSensor);
  lcd.setCursor(0, 1); lcd.print("F.S: "); lcd.print(THIRDSensor);
  delay(1000); lcd.clear();

  // Check distances and trigger alarm if needed
  if ((FIRSTSensor >= 10) && (FIRSTSensor <= 50)) {
    digitalWrite(ALARM, HIGH); delay(500);
  }
  if ((SECONDSensor >= 10) && (SECONDSensor <= 50)) {
    digitalWrite(ALARM, HIGH); delay(500);
  }
  if ((THIRDSensor >= 10) && (THIRDSensor <= 50)) {
    digitalWrite(ALARM, HIGH); delay(500);
  }
}

// SonarSensor function to calculate distance
void SonarSensor(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
}

