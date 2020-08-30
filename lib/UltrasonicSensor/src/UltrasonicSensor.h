#include <Arduino.h>

struct UltrasonicSensorInput
{
  uint8_t TriggerPin = D3;
  uint8_t EchoPin = D5;
  uint16_t DirectionScanDelay = 1000;
  unsigned long Timeout = 54000;
  bool DebugToSerial = false;
};

enum DistanceState
{
  Uss_Decreasing = -1,
  Uss_NoChange = 0,
  Uss_Increasing = 1
};

class UltrasonicSensor
{
public:
  UltrasonicSensor();
  void Init(const UltrasonicSensorInput userInput);
  uint16_t Distance();
  bool isDecreasing();
  DistanceState Direction();

private:
  UltrasonicSensorInput _userInput;
  uint16_t _distance;
  uint16_t _wasAt;
  uint16_t _isAt;
  
  void triggerHigh();
  void triggerLow();
};
