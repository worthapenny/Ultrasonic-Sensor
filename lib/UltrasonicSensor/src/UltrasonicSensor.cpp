#include <Arduino.h>
#include <UltrasonicSensor.h>

UltrasonicSensor::UltrasonicSensor()
{
}

void UltrasonicSensor::Init(const UltrasonicSensorInput userInput)
{
  _userInput = userInput;

  // define pin modes
  pinMode(_userInput.TriggerPin, OUTPUT);
  pinMode(_userInput.EchoPin, INPUT);

  if (_userInput.DebugToSerial)
    Serial.printf("Uss:: Initialized with TriggerPint = %d, EchoPin = %d\n", _userInput.TriggerPin, _userInput.EchoPin);
}

bool UltrasonicSensor::isDecreasing()
{
  _wasAt = Distance();
  delay(_userInput.DirectionScanDelay);
  _isAt = Distance();

  if (_userInput.DebugToSerial)
    Serial.printf("Uss:: Was: %d ==> Now: %d\n", _wasAt, _isAt);

  return (_wasAt - _isAt) < 0;
}

// returns the distance in cm
uint16_t UltrasonicSensor::Distance()
{
  // Clear the Trigger pin
  triggerLow();
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  triggerHigh();
  delayMicroseconds(10);
  triggerLow();

  // Calculating the distance
  // sound speed = 343 m/s => distance (m) = 343 * time (s) => d (cm) = 0.0343 * time (us)
  // Since it takes double the time to bounce back, half the time for right distance
  // d(cm) = 0.0343 * time (us) / 2 => 0.01715 * t (us)
  _distance = pulseIn(_userInput.EchoPin, HIGH, _userInput.Timeout) * 0.01715;

  if (_userInput.DebugToSerial)
    Serial.printf("Uss:: Distance: %d\n", _distance);

  return _distance;
}

DistanceState UltrasonicSensor::Direction()
{
  _wasAt = Distance();
  delay(_userInput.DirectionScanDelay);
  _isAt = Distance();

  if (_userInput.DebugToSerial)
    Serial.printf("Uss:: Was: %d ==> Now: %d\n", _wasAt, _isAt);

  if (_isAt < _wasAt)
    return Uss_Decreasing;

  if (_isAt > _wasAt)
    return Uss_Increasing;

  return Uss_NoChange;
}

void UltrasonicSensor::triggerHigh()
{
  digitalWrite(_userInput.TriggerPin, HIGH);
}
void UltrasonicSensor::triggerLow()
{
  digitalWrite(_userInput.TriggerPin, LOW);
}