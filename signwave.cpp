#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SIGN LANGUAGE");

  pinMode(13, OUTPUT);
}

void loop() {
  int s1 = analogRead(A0); // Ring Finger
  int s2 = analogRead(A1); // Pinky Finger
  int s3 = analogRead(A2); // Middle Finger

  // Map the sensor values to angle values (e.g., 0-1023 mapped to 0-180 degrees)
  int angle1 = map(s1, 0, 1023, 0, 180);
  int angle2 = map(s2, 0, 1023, 0, 180);
  int angle3 = map(s3, 0, 1023, 0, 180);

  Serial.print("S1 (Ring Finger): "); Serial.print(s1); Serial.print(" -> Angle: "); Serial.println(angle1);
  Serial.print("S2 (Pinky Finger): "); Serial.print(s2); Serial.print(" -> Angle: "); Serial.println(angle2);
  Serial.print("S3 (Middle Finger): "); Serial.print(s3); Serial.print(" -> Angle: "); Serial.println(angle3);

  // S1 - Ring Finger
  if (s1 >= 5 && s1 <= 100) {
    Serial.println("Restroom Needed");
    lcd.setCursor(0, 1);
    lcd.print(" RESTROOM ");
  } else if (s1 > 100 && s1 <= 200) {
    Serial.println("Please Help");
    lcd.setCursor(0, 1);
    lcd.print(" HELP ");
  } else if (s1 > 200 && s1 <= 324) {
    Serial.println("Need Assistance");
    lcd.setCursor(0, 1);
    lcd.print(" ASSISTANCE ");
  }

  // S2 - Pinky Finger
  if (s2 >= 0 && s2 <= 80) {
    Serial.println("I'm Thirsty");
    lcd.setCursor(0, 1);
    lcd.print(" THIRSTY ");
  } else if (s2 > 80 && s2 <= 150) {
    Serial.println("Water Please");
    lcd.setCursor(0, 1);
    lcd.print(" WATER ");
  } else if (s2 > 150 && s2 <= 250) {
    Serial.println("Need Beverage");
    lcd.setCursor(0, 1);
    lcd.print(" BEVERAGE ");
  }

  // S3 - Middle Finger
  if (s3 >= 0 && s3 <= 120) {
    Serial.println("I Need Food");
    lcd.setCursor(0, 1);
    lcd.print(" NEED FOOD ");
  } else if (s3 > 120 && s3 <= 250) {
    Serial.println("Hungry Now");
    lcd.setCursor(0, 1);
    lcd.print(" HUNGRY ");
  } else if (s3 > 250 && s3 <= 370) {
    Serial.println("Request Meal");
    lcd.setCursor(0, 1);
    lcd.print(" REQUEST MEAL ");
  } else if (s3 > 370 && s3 <= 380) {
    Serial.println("Specific Meal");
    lcd.setCursor(0, 1);
    lcd.print(" SPECIFIC MEAL ");
  }

  // Default message if no specific range is detected
  if (!(s1 >= 5 && s1 <= 324) && !(s2 >= 0 && s2 <= 250) &&
      !(s3 >= 0 && s3 <= 380)) {
    Serial.println("NO ACTION");
    lcd.setCursor(0, 1);
    lcd.print(" NO ACTION ");
  }

  delay(2000); // Delay to allow reading

}
