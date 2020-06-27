
  #include <HCSR04.h>

  int motorsPin = 3;
  
  int triggerPin = 8;
  int echoPin = 6;
  UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

  int minDist = 5;
  int reactDist = 100;
  int prevIntensity = 0;
  
  int intensityMin = 35;
  int intensityMax = 70;
  
  int cycleTime = 100;

  int onsetDelay = 50;

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
  if (prevIntensity == 0 && intensity != 0)   
  {
    kickStartMotors();
  }
  setMotors(intensity);
  delay(cycleTime);
  prevIntensity = intensity;
}

void kickStartMotors()
{
  setMotors(intensityMax);
  delay(onsetDelay);
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
