
  #include <HCSR04.h>

  int motorsPin = 3;
  
  int triggerPin = 8;
  int echoPin = 6;
  UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

  int minDist = 10;
  int reactDist = 100;
  int prevIntensity = 0;
  
  int intensityMin = 45;
  int intensityMax = 70;
  
  int cycleTime = 100;

  int onsetDelay = 30;

  float startSequenceDelay = 500;
  int startSequenceRepetitions = 4;

void setup() 
{
  pinMode(motorsPin, OUTPUT);
  startSequence();
}

void loop() 
{
  int intensity = calcIntensity();
  if (prevIntensity = 0 && intensity != 0)   
  {
    setMotors(intensityMax);
    delay(onsetDelay);
  }
  setMotors(intensity);
  delay(cycleTime);
  prevIntensity = intensity;
}

int calcIntensity()
{
  double distance = constrain(distanceSensor.measureDistanceCm(), 0, reactDist + 5) ;
  
  int intensity = map(constrain(distance - minDist, 0, reactDist), 0, reactDist, intensityMax, intensityMin);
  if (distance >= reactDist || distance <= minDist) 
  {
    intensity = 0;
  }
  return intensity;
}

void setMotors(int speed)
{
  analogWrite(motorsPin, speed);
}

void startSequence()
{
  for (int i = 0; i < startSequenceRepetitions; i++)
  {
    setMotors(intensityMax);
    delay(startSequenceDelay);
    setMotors(0);
    delay(startSequenceDelay);
  }
}
