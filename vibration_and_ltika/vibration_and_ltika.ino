#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>


#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void) {
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(50);
  strip.show();

  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");

  mma.setRange(MMA8451_RANGE_2_G);

  Serial.print("Range = "); Serial.print(2 << mma.getRange());
  Serial.println("G");

}
double before_data = 0;

void loop() {
  double data;
  int threshold = 200;

  mma.read();
  data = mma.z;
  Serial.print("\tZ:\t"); Serial.print(mma.z);
  Serial.println();

  sensors_event_t event;

  mma.getEvent(&event);
  //data = event.acceleration.z;
  //Serial.print("Z: \t");
  //Serial.print(event.acceleration.z); Serial.print("\t");
  //Serial.println("m/s^2 ");

  if ((before_data - data) > threshold) {
    Flashing(strip.Color(0, 0, 255), 500);
    //rand_Flashing(strip.Color(0, 0, 255));
    Serial.println("1");
  }
  else if ((data - before_data) > threshold) {
    Flashing(strip.Color(0, 0, 255), 500);
    //rand_Flashing(strip.Color(0, 0, 255));
    Serial.println("2");
  }
  else {
    all_down();
  }

  before_data = data;
  Serial.println();
  delay(100);

}

void Flashing(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels() / 2; i++) {
    strip.setPixelColor(i * 2, c);
    strip.show();
  }
  delay(1000);
  all_down();
  for (uint16_t i = 0; i < strip.numPixels() / 2; i++) {
    strip.setPixelColor(i * 2 + 1, c);
    strip.show();
  }
  delay(1000);
  all_down();
}

void all_down() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, (0, 0, 0));
    strip.show();
  }
}

void rand_Flashing(uint32_t c) {
  randomSeed(analogRead(0));
  int ran_num = random(5, 10);
  for (uint16_t i = 0; i < strip.numPixels() / 2; i += ran_num) {
    randomSeed(analogRead(0));
    ran_num = random(5, 10);
    strip.setPixelColor(i, c);
    strip.show();
  }
  delay(500);
  all_down();
}

