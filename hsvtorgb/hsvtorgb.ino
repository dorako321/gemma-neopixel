#include <Adafruit_NeoPixel.h>
 
#define PIN 0
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(24, PIN);
uint32_t hue = 0;
uint32_t roll = 0;

uint32_t hsv2rgb(uint32_t h, float s, float v)
{
    float hh, p, q, t, ff;
    long  i;
    float r, g, b;
    
    hh = h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * ff));
    t = v * (1.0 - (s * (1.0 - ff)));

    switch(i) {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;

    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    case 5:
    default:
        r = v;
        g = p;
        b = q;
        break;
    }
    uint32_t r8 = round(r * 255);
    uint32_t g8 = round(g * 255);
    uint32_t b8 = round(b * 255);
    r8 = r8 << 16;
    g8 = g8 << 8;
    return r8 + g8 + b8;
}
 
void setup() {
  pixels.begin();
  pixels.setBrightness(10);
}
 
void loop() {
  uint8_t i;
  roll++;
  float rad = (roll*5) * PI / 180.0;
  float s = 0.5;//sin(rad) / 2;
  for(i=0; i<12; i++) {
    hue += 30;
    uint32_t rgb = hsv2rgb(hue % 360, 0.5 + s, 1);
    pixels.setPixelColor((i+roll)%12, rgb);
  }
  pixels.show();
  delay(50);
}
