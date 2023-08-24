#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>


MPU6050 mpu;
int16_t acelX = 0, acelY = 0, acelZ=0;
int16_t gyroscopeX = 0, gyroscopeY = 0, gyroscopeZ=0;
float last_gyroscopeX = 0, last_gyroscopeY = 0, last_gyroscopeZ=0;

unsigned long lastTime =0, simpleTime = 100;
long preview_time, dt;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  while(!mpu.testConnection()){
    Serial.print('.');
     delay(500);
  }
}

void loop() {

  if(millis()-lastTime>=simpleTime){
      
      lastTime = millis();
     
  
      // read aceleration
      mpu.getAcceleration(&acelX, &acelY, &acelZ);

      // Calculate angle of inclination 
      float aceel_anng_X = atan(acelX/sqrt(pow(acelY,2) + pow(acelZ,2))) *(180.0/3.14);
      float aceel_anng_Y = atan(acelY/sqrt(pow(acelX,2) + pow(acelZ,2))) *(180.0/3.14);
      float aceel_anng_Z = atan(acelZ/sqrt(pow(acelX,2) + pow(acelY,2))) *(180.0/3.14);

      // show angles
      Serial.print("Acelerometro X: ");
      Serial.print(aceel_anng_X);
      Serial.print("  Acelerometro Y: ");
      Serial.print(aceel_anng_Y);
      Serial.print("  Acelerometro Z: ");
      Serial.println(aceel_anng_Z);
    
      //Read angular speed
      mpu.getRotation(&gyroscopeX, &gyroscopeY, &gyroscopeZ );

      dt = millis()-preview_time;
      preview_time = millis();

      // Claculation angle of rotation
      float girosc_ang_X= (gyroscopeX/131)*(dt/1000.0) + last_gyroscopeX;
      float girosc_ang_Y= (gyroscopeY/131)*(dt/1000.0) + last_gyroscopeY;
      float girosc_ang_Z= (gyroscopeZ/131)*(dt/1000.0) + last_gyroscopeZ;

      last_gyroscopeX = girosc_ang_X;
      last_gyroscopeY = girosc_ang_Y;
      last_gyroscopeZ = girosc_ang_Z;
      // show angles
       Serial.print("Giroscopio X: ");
      Serial.print(gyroscopeX);
      Serial.print("  Giroscopio Y: ");
      Serial.print(gyroscopeY);
      Serial.print("  Giroscopio Z: ");
      Serial.println(gyroscopeZ);



  }


 
}