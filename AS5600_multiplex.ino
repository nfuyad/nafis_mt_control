#include <Wire.h>

#define TCA_ADDR 0x70          // Default TCA9548A address
#define AS5600_ADDR 0x36       // AS5600 I2C address
#define RAW_ANGLE_REG 0x0C     // Register for raw angle (2 bytes)

float targetAngle = 30.0;
const int LPin = 9;
const int RPin = 10;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(LPin, OUTPUT);
  pinMode(RPin, OUTPUT);
  delay(500);
  Serial.println("AS5600 Dual Sensor via TCA9548A Starting...");
}

// Function to select TCA9548A channel (0–7)
void selectTCAChannel(uint8_t channel) {
  if (channel > 7) return; // Safety check
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << channel); // Select channel
  Wire.endTransmission();
}

// Read raw angle from AS5600
uint16_t readRawAngle() {
  Wire.beginTransmission(AS5600_ADDR);
  Wire.write(RAW_ANGLE_REG);
  Wire.endTransmission(false);
  Wire.requestFrom(AS5600_ADDR, (uint8_t)2);
  if (Wire.available() == 2) {
    uint8_t highByte = Wire.read();
    uint8_t lowByte = Wire.read();
    return ((highByte & 0x0F) << 8) | lowByte;
  }
  return 0;
}

void scan(){
  byte error, address;
  int nDevices = 0;

  Serial.println("Scanning...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("Scan complete\n");
}

void loop() {
  // --- Sensor 1 (Channel 0) ---
  selectTCAChannel(2);
  //scan();
  uint16_t raw1 = readRawAngle();
  float angle1 = (raw1 * 360.0) / 4096.0;

  // --- Sensor 2 (Channel 1) ---
  selectTCAChannel(5);
  //scan();
  uint16_t raw2 = readRawAngle();
  float angle2 = (raw2 * 360.0) / 4096.0;

  Serial.print("Sensor 1: ");
  Serial.print(angle1, 2);
  Serial.print(",Sensor 2: ");
  Serial.println(angle2, 2);

  // Example control for one sensor (you can modify logic per sensor)
  selectTCAChannel(0); // Choose which sensor to control from
  controlMotor(angle1);

//  delay(200);
}

void controlMotor(float angle) {
  if (angle >= targetAngle && angle <= (targetAngle + 5.0)) {
    analogWrite(LPin, 0);
    analogWrite(RPin, 0);
  } else {
    if (angle > targetAngle) {
      analogWrite(LPin, 0);
      analogWrite(RPin, 255);
    } else if (angle < targetAngle) {
      analogWrite(LPin, 255);
      analogWrite(RPin, 0);
    }
  }
}
