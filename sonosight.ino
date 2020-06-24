
  #include <HCSR04.h>

  int motorsPin = 3;
  int triggerPin = 8;
  int echoPin = 6;
  UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

  int minDist = 10;
  int reactDist = 100;
  int prevDist = 0;
  
  int vibrMin = 20;
  int vibrMax = 80;
  
  int cycleTime = 100;

void setup() 
{
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
}


void loop() 
{
  double distance = constrain(distanceSensor.measureDistanceCm(), 0, reactDist + 5) ;
  prevDist = distance;
  int intensity = map(constrain(distance - minDist, 0, reactDist), 0, reactDist, vibrMax, vibrMin);
  if (distance >= reactDist || distance <= minDist) 
  {
    intensity = 0;
  }
  analogWrite(3, intensity);
  delay(cycleTime);
}
