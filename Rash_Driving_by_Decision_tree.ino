// RX=11, TX =10 pins for HC-05 module 
// MPU6050 SDA--a4; SCl ---a5
//buzzer--9
//Switch --8
#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;
float pitch,roll;
int buzzerPin =9,i,c=0;
void setup() 
{ 
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  Wire.begin();
  mpu.initialize();
  mpu.CalibrateGyro();}

void loop() {
    float p1_value =pitch;
    read();
    float p2_value =pitch;
    float r2_value = roll;
    read();
    float p3_value = pitch;
    float r3_value = roll;
    
    int prediction = predictDecisionTree(p1_value, p2_value, p3_value, r2_value, r3_value);
    if( prediction){buz()}
    else{Serial.print("Nothing");}
    
}
void read(){
  int16_t accX = mpu.getAccelerationX();
  int16_t accY = mpu.getAccelerationY();
  int16_t accZ = mpu.getAccelerationZ();
  float accX_g = accX / 16384.0;
  float accY_g = accY / 16384.0;
  float accZ_g = accZ / 16384.0;
  pitch = atan2(accX_g, sqrt(accY_g * accY_g + accZ_g * accZ_g)) * 180.0 / PI;
  roll = atan2(accY_g, sqrt(accX_g * accX_g + accZ_g * accZ_g)) * 180.0 / PI;
}

int predictDecisionTree(float p1, float p2, float p3, float r2, float r3) {
    if (p3 <= -2.32) {
        if (r2 <= 13.41) {
            if (r3 <= 1.19) {
                if (p2 <= -6.04) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                if (p1 <= -4.42) {
                    if (r2 <= -0.30) {
                        return 1;
                    } else {
                        return 1;
                    }
                } else {
                    if (p2 <= -5.25) {
                        return 0;
                    } else {
                        return 1;
                    }
                }
            }
        } else {
            return 1;
        }
    } else {
        if (r3 <= 5.41) {
            if (p1 <= -14.64) {
                return 1;
            } else {
                if (p2 <= -10.72) {
                    return 0;
                } else {
                    if (r3 <= 1.78) {
                        return 0;
                    } else {
                        return 0;
                    }
                }
            }
        } else {
            if (p3 <= 9.47) {
                return 0;
            } else {
                return 1;
            }
        }
    }
}
void buz()
{
  tone(buzzerPin,1000);
  delay(1000);
  noTone(buzzerPin)
}
