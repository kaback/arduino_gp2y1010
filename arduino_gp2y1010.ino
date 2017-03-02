/*
 Standalone Sketch to use with a Arduino UNO and a
 Sharp Optical Dust Sensor GP2Y1010AU0F
*/
 
int measurePin = 0; //Connect dust sensor to Arduino A0 pin
int ledPower = 2;   //Connect 3 led driver pins of dust sensor to Arduino D2
 
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
 
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
 
void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  analogReference(EXTERNAL); //LM4040 4.1 voltage reference connected to AREF
}
 
void loop(){
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);
 
  voMeasured = analogRead(measurePin); // read the dust value
 
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
 
  // 0 - 4.069V (LM4040 AREF) mapped to 0 - 1023 integer values
  calcVoltage = voMeasured * (4.069 / 1024.0);
 
  // linear eqaution taken from http://www.pocketmagic.net/sharp-gp2y1010-dust-sensor/

  //if (calcVoltage < 0.583)  
  //  dustDensity = 0;
  //else
    dustDensity = 6 * calcVoltage / 35 - 0.1;
 
  Serial.print(dustDensity);
  Serial.print(" ");
  Serial.print(0);
  Serial.print("\n");
  delay(1000);
}
