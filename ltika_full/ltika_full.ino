#include <Adafruit_NeoPixel.h>

#define PIN 6 //制御用のPIN番号定義

Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_GRB + NEO_KHZ800); //(NeoPixelの数、制御PIN)

void setup() {
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  //colorWipe(strip.Color(255, 0, 0), 500); // Red
  //colorWipe(strip.Color(0, 300, 0), 500); // Green
  //colorWipe(strip.Color(0, 0, 255), 500); // Blue
  rainbowCycle(20);
  //rainbow(20);
  //tenmetu(strip.Color(0,0,255),500);  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
  all_down();
}

// 自作：点滅
void tenmetu(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels() / 2; i++) {
      strip.setPixelColor(i * 2, c);
      strip.show();
  }
  delay(1000);
  all_down();
  for(uint16_t i=0; i<strip.numPixels() / 2; i++){
    strip.setPixelColor(i * 2 + 1,c);
    strip.show();
  }
  delay(1000);
  all_down();
}

//自作：全部消す
void all_down() {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, (0,0,0));
      strip.show();
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
