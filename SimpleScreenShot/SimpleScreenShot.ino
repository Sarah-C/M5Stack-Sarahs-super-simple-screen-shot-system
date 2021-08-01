#include <M5Stack.h>

// Paste the data into this page:
// https://codepen.io/SarahC/pen/oNWqKQa?editors=1001

#define ILI9341_GREY 0x7BEF
unsigned long runTime = 0;

float sx = 0, sy = 0;
uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;

// Either one of these >

void takeScreenshot888(void) {
  uint8_t pixels[16];
  Serial.println(F("--------------- COPY CODE AFTER THIS LINE FOR RGB888 SCREEN SHOT ----------------"));
  for (int y = 0; y < 240; y++) {
    for (int x = 0; x < 320; x += 5) {
      M5.Lcd.readRectRGB(x, y, 5, 1, pixels);
      for (int arrayPtr = 0; arrayPtr < 15; arrayPtr++) {
        Serial.printf("%02X", pixels[arrayPtr]);
      }
    }
    if (y != 240) Serial.println("");
  }
  Serial.println(F("--------------- COPY CODE UP TO THIS LINE FOR RGB888 SCREEN SHOT ----------------"));
}

void takeScreenshot565(void) {
  uint16_t pixels[6];
  Serial.println(F("--------------- COPY CODE AFTER THIS LINE FOR RGB565 SCREEN SHOT ----------------"));
  for (int y = 0; y < 240; y++) {
    for (int x = 0; x < 320; x += 5) {
      M5.Lcd.readRect(x, y, 5, 1, pixels);
      for (int arrayPtr = 0; arrayPtr < 5; arrayPtr++) {
        Serial.printf("%04X", pixels[arrayPtr]);
      }
    }
    if (y != 240) Serial.println("");
  }
  Serial.println(F("--------------- COPY CODE UP TO THIS LINE FOR RGB565 SCREEN SHOT ----------------"));
}
void setup()
{
  M5.begin();
  M5.Power.begin();
}

void loop()
{
  runTime = millis();

  M5.Lcd.fillScreen(ILI9341_BLACK);
  for (int px = 1; px < 320; px++)
  {
    for (int py = 0; py < 240; py++)
    {
      float x0 = (map(px, 0, 320, -250000 / 2, -242500 / 2)) / 100000.0; //scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
      float yy0 = (map(py, 0, 240, -75000 / 4, -61000 / 4)) / 100000.0; //scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
      float xx = 0.0;
      float yy = 0.0;
      int iteration = 0;
      int max_iteration = 128;
      while ( ((xx * xx + yy * yy) < 4)  &&  (iteration < max_iteration) )
      {
        float xtemp = xx * xx - yy * yy + x0;
        yy = 2 * xx * yy + yy0;
        xx = xtemp;
        iteration++;
      }
      int color = rainbow((3 * iteration + 64) % 128);
      yield(); M5.Lcd.drawPixel(px, py, color);
    }
  }
  
  // Open the serial monitor, and look for the large block of hex numbers.
  //takeScreenshot888();
  takeScreenshot565();
  
  while (1) yield();
}

unsigned int rainbow(int value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to red = blue

  byte red = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue = 0; // Blue is the bottom 5 bits

  byte quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}
