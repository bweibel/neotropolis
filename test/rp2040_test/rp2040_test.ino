#include <NeoPixelConnect.h>

// Create an instance of NeoPixelConnect and initialize it
// to use GPIO pin 4 (D12) as the control pin, for a string
// of 8 neopixels. Name the instance p
int NUM_PIXELS = 48;

NeoPixelConnect p(23, NUM_PIXELS);

uint8_t pixelNumber = 0;
bool isReverse = false;

// this array will hold a pixel number and the rgb values for the
// randomly generated pixel values
uint8_t random_pixel_setting[4];

// select a random pixel number in the string
uint8_t get_pixel_number(){
    // return((uint8_t)random(0,20));
    if ( pixelNumber == NUM_PIXELS && isReverse == false ) {
      isReverse = true;
    } 

    if ( pixelNumber == 0 && isReverse == true ) {
      isReverse = false;
    } 

    if ( ! isReverse ) {
      pixelNumber++;
    } else {
      pixelNumber--;
    }
    
    // pixelNumber = 0;
    return pixelNumber;
}

// select a random intensity
uint8_t get_pixel_intensity(){
    return((uint8_t)random(0,255));
}

void get_random_pixel_and_color(){
    random_pixel_setting[0] = get_pixel_number();
    random_pixel_setting[1] = get_pixel_intensity();
    random_pixel_setting[2] = get_pixel_intensity();
    random_pixel_setting[3] = get_pixel_intensity();
}

void setup(){
    Serial.begin(115200);
    delay(2000);
    Serial.println("In setup");
}

void loop(){

  for( int i =0; i <NUM_PIXELS; i++ ) {
      p.neoPixelSetValue(i, 10, 0, 120, true);
    }

    // get a pixel number
    get_random_pixel_and_color();

    // display the randomly assigned pixel and color
    p.neoPixelSetValue(random_pixel_setting[0], random_pixel_setting[1],
                       random_pixel_setting[2],
                       random_pixel_setting[3], true);

// display the randomly assigned pixel and color
    // p.neoPixelSetValue(random_pixel_setting[0]+20, random_pixel_setting[1],
    //                    random_pixel_setting[2],
    //                    random_pixel_setting[3], true);
    
    // p.neoPixelSetValue(random_pixel_setting[0]-20, random_pixel_setting[1],
    //                    random_pixel_setting[2],
    //                    random_pixel_setting[3], true);

    // delay(50);
    // clear all pixels
    // p.neoPixelClear();

    delay(100);
}
