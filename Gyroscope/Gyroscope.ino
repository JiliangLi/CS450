
#include "Wire.h" 
const int MPU_ADDR = 0x68; 
int16_t accelerometer_x, accelerometer_y, accelerometer_z; 
int16_t gyro_x, gyro_y, gyro_z; 
int16_t temperature; 
char tmp_str[7]; 

int16_t AccX[50];
int16_t AccY[50];
int16_t AccZ[50];
int16_t GyX[50];
int16_t GyY[50];
int16_t GyZ[50];


char* convert_int16_to_str(int16_t i) { 
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); 
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

int16_t CalcAvg(int16_t arr[]){
  int total;
  for(int i=0; i<50; i++){
    total += arr[i];
  }

  int avg = total/50;
  return avg;
}

void loop() {

  for(int i=0; i<50; i++){
      Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); 
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 7*2, true); 
    
    accelerometer_x = Wire.read()<<8 | Wire.read(); 
    AccX[i] = accelerometer_x;
    
    accelerometer_y = Wire.read()<<8 | Wire.read(); 
    AccY[i] = accelerometer_y;
    
    accelerometer_z = Wire.read()<<8 | Wire.read();
    AccZ[i] = accelerometer_z; 
    
    temperature = Wire.read()<<8 | Wire.read(); 
    
    gyro_x = Wire.read()<<8 | Wire.read(); 
    GyX[i] = gyro_x; 

    gyro_y = Wire.read()<<8 | Wire.read(); 
    GyY[i] = gyro_x; 

    gyro_z = Wire.read()<<8 | Wire.read(); 
    GyZ[i] = gyro_x; 
  }
    
  accelerometer_x = CalcAvg(AccX); 
  accelerometer_y = CalcAvg(AccY); 
  accelerometer_z = CalcAvg(AccZ); 
  gyro_x = CalcAvg(GyX); 
  gyro_y = CalcAvg(GyY); 
  gyro_z = CalcAvg(GyZ); 

  
  // print out data
  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));

  Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  Serial.println();
  
}
