#include <Arduino.h>
#include <UltrasonicSensor.h>

UltrasonicSensor uss;

void setup()
{
  delay(2000); // for things to catch up

  Serial.begin(115200);
  Serial.printf("\nStarting up... \n");

  // Trigger is default to D3 (Tri = 3)
  // Echo is default to D5  (E is 5th)
  UltrasonicSensorInput ussInput = UltrasonicSensorInput();
  ussInput.DebugToSerial = true; // default is false

  uss.Init(ussInput); // initialize

  Serial.printf("Setup completed!\n\n");
}

void loop()
{
  //Serial.printf("Current Distance: %d\n", uss.Distance());
  //Serial.printf("Direction: %d\n", uss.Direction());
  Serial.printf("Decreasing: %s\n\n", uss.isDecreasing() ? "True" : "False");

  delay(500);
}