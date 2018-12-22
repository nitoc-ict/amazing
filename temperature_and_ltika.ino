#include <Temperature_LM75_Derived.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(61, PIN, NEO_GRB + NEO_KHZ800);

Generic_LM75 temperature;

void setup() {
  while(!Serial) {}
  Serial.begin(9600);
  Wire.begin();

  strip.begin();
  strip.setBrightness(50);
  strip.show();
}

void loop() {
  float tmp = temperature.readTemperatureC(); //get temperture 
  Serial.print("Temperature = ");
  Serial.print(tmp);
  Serial.println(" C");

  float Red;
  float Green;
  float Blue;

  if(tmp > 30){
    Red = tmp * 5;
    Green = tmp * 2;
    Blue = 0;
  }
  else if(tmp < 28){
    Red = 0;
    Green = tmp * 6;
    Blue = tmp * 10;
  }
  else {
    Red = tmp * 3;
    Green = tmp * 5; 
    Blue = 0;
  }
  Serial.println(Red);Serial.println(Green);Serial.println(Blue);
  colorFlush(strip.Color(Red, Green, Blue));
  

  delay(250);
}

void colorFlush(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
  }
  all_down();
}

void all_down() {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, (0,0,0));
      strip.show();
  }
}
