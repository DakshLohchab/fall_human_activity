#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(115200);

  // Start I2C
  Wire.begin(21, 22);

  Serial.println("Initializing MPU6050...");

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 Connected Successfully");
  } else {
    Serial.println("MPU6050 Connection Failed");
  }
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  // Read raw accel + gyro
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.println("------");

  Serial.print("Accel X: "); Serial.println(ax);
  Serial.print("Accel Y: "); Serial.println(ay);
  Serial.print("Accel Z: "); Serial.println(az);

  Serial.print("Gyro X: "); Serial.println(gx);
  Serial.print("Gyro Y: "); Serial.println(gy);
  Serial.print("Gyro Z: "); Serial.println(gz);

  delay(500);
}
