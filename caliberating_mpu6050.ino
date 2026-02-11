#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Calibration offsets
int16_t ax_offset = 0, ay_offset = 0, az_offset = 0;
int16_t gx_offset = 0, gy_offset = 0, gz_offset = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  
  Serial.println("Place MPU6050 on flat surface, don't move!");
  delay(3000);
  
  calibrateMPU();
  
  Serial.println("Calibration complete!");
  Serial.print("Accel Offsets: ");
  Serial.print(ax_offset); Serial.print(", ");
  Serial.print(ay_offset); Serial.print(", ");
  Serial.print(az_offset); Serial.println(" (normally 16384)");
  
  Serial.print("Gyro Offsets: ");
  Serial.print(gx_offset); Serial.print(", ");
  Serial.print(gy_offset); Serial.print(", ");
  Serial.print(gz_offset); Serial.println("");
}

void loop() {
  // Your main code here
}

void calibrateMPU() {
  const int samples = 1000;
  long ax_sum = 0, ay_sum = 0, az_sum = 0;
  long gx_sum = 0, gy_sum = 0, gz_sum = 0;
  
  for (int i = 0; i < samples; i++) {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    ax_sum += ax;
    ay_sum += ay;
    az_sum += az;
    gx_sum += gx;
    gy_sum += gy;
    gz_sum += gz;
    
    delay(2); // Small delay between samples
  }
  
  // Average the readings
  ax_offset = ax_sum / samples;
  ay_offset = ay_sum / samples;
  az_offset = (az_sum / samples) - 16384; // 16384 = 1g in normal mode
  gx_offset = gx_sum / samples;
  gy_offset = gy_sum / samples;
  gz_offset = gz_sum / samples;
}