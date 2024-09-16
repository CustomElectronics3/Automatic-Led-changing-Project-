#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

// Define LED pins
const int led1 = 2;  // LED 1 to Pin 2
const int led2 = 3;  // LED 2 to Pin 3
const int led3 = 4;  // LED 3 to Pin 4
const int led4 = 5;  // LED 4 to Pin 5

// Define time slots for LEDs
const int led1_start_hour = 0;   // LED 1 starts at 00:00 AM
const int led1_end_hour = 6;     // LED 1 ends at 6:00 AM

const int led2_start_hour = 6;   // LED 2 starts at 6:00 AM
const int led2_end_hour = 12;    // LED 2 ends at 12:00 PM

const int led3_start_hour = 12;  // LED 3 starts at 12:00 PM
const int led3_end_hour = 18;    // LED 3 ends at 6:00 PM

const int led4_start_hour = 18;  // LED 4 starts at 6:00 PM
const int led4_end_hour = 24;    // LED 4 ends at 12:00 AM

void setup() {
  // Initialize the LED pins as OUTPUT
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // Turn off all LEDs initially
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize RTC
  Wire.begin();
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);  // Stop if RTC not found
  }

  // Uncomment and set the RTC to the current time if needed (for testing)
 // rtc.adjust(DateTime(2024, 9, 14, 14, 10, 30));  // Adjust time if needed
}

void loop() {
  DateTime now = rtc.now();  // Get the current time from the RTC

  // Print current time to the Serial Monitor
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());

  // Get the current hour
  int currentHour = now.hour();

  // Determine which LED should be on based on the current hour
  if (currentHour >= led1_start_hour && currentHour < led1_end_hour) {
    // Between 00:00 AM and 6:00 AM - Turn on LED 1
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    Serial.println("LED 1 ON");
  } else if (currentHour >= led2_start_hour && currentHour < led2_end_hour) {
    // Between 6:00 AM and 12:00 PM - Turn on LED 2
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    Serial.println("LED 2 ON");
  } else if (currentHour >= led3_start_hour && currentHour < led3_end_hour) {
    // Between 12:00 PM and 6:00 PM - Turn on LED 3
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    Serial.println("LED 3 ON");
  } else if (currentHour >= led4_start_hour && currentHour < led4_end_hour) {
    // Between 6:00 PM and 00:00 AM - Turn on LED 4
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    Serial.println("LED 4 ON");
  } else {
    // Turn off all LEDs if no condition is met
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    Serial.println("All LEDs OFF");
  }

  // Check every second
  delay(1000);
}
