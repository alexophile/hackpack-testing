#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#define PIN 1
#include "RGB.h"

//initialize the matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
NEO_GRB            + NEO_KHZ800);

void setup() {
  matrix.begin();
  matrix.setBrightness(30);
  matrix.setTextColor( matrix.Color(255, 255, 255) );
  matrix.setTextWrap(false);

}

void loop() {
  crossFade(testgrey, swuorange, 50, 5);
  delay(1000);
  
 // scrollText("sendwithus", 90);
  
  crossFade(swuorange, testgrey, 50, 5);
  delay(1000);
  
  //drawFrameMono(swuorange, testgrey, envelope);
  //delay(1000);
  
  colorWipe(testgrey, 0);
  delay(1000);  
  
}

void scrollDownMono(RGB color, RGB bgColor, int drawing[][8]){
  
}

void drawFrameMono(RGB color, RGB bgColor, int frame[][8]){
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(frame[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(color.r, color.g, color.b));
     }
     else{
       matrix.drawPixel(column, row, matrix.Color(bgColor.r, bgColor.g, bgColor.b));
     }
   }
  }
  matrix.show();
}

void colorWipe(RGB color, uint8_t wait) {
  for(uint16_t row=0; row < 8; row++) {
    for(uint16_t column=0; column < 8; column++) {
      matrix.drawPixel(column, row, matrix.Color(color.r, color.g, color.b));
      matrix.show();
      delay(wait);
    }
  }
}

void fadePixel(int x, int y, RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++) 
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;
     
     matrix.drawPixel(x, y, matrix.Color(newR, newG, newB));
     matrix.show();
     delay(wait);
  }
}

void crossFade(RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++)
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;
     
     matrix.fillScreen(matrix.Color(newR, newG, newB));
     matrix.show();
     delay(wait);
  }
}

void scrollText(String textToDisplay, int scrollDelay) {
  int x = matrix.width();
  
  // Account for 6 pixel wide characters plus a space
  int pixelsInText = textToDisplay.length() * 7;
  
  matrix.setCursor(x, 0);
  matrix.print(textToDisplay);
  matrix.show();
  
  while(x > (matrix.width() - pixelsInText)) {
    matrix.fillScreen(matrix.Color(swuorange.r, swuorange.g, swuorange.b));
    matrix.setCursor(--x, 0);
    matrix.print(textToDisplay);
    matrix.show();
    delay(scrollDelay);
  }
}

