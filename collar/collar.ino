#include <NeoPixelConnect.h>

// Create an instance of NeoPixelConnect and initialize it
// to use GPIO pin 4 (D12) as the control pin, for a string
// of 8 neopixels. Name the instance p
int NUM_PIXELS = 48;
int BASE_RED = 0;
int BASE_GREEN = 50;
int BASE_BLUE = 150;


NeoPixelConnect p(23, NUM_PIXELS);

uint8_t pixelNumber1 = 1;
uint8_t pixelNumber12 = 1;

bool isReverse = false;


// select the next pixel in the string
void update_pixel_number(){

  // We hit the end of the strand. Reverse direction.
    if ( pixelNumber1 == NUM_PIXELS-1 && isReverse == false ) {
      isReverse = true;
    } 

    if ( pixelNumber1 == 1 && isReverse == true ) {
      isReverse = false;
    } 

    if ( ! isReverse ) {
      pixelNumber1++;
    } else {
      pixelNumber1--;
    }
    
}

// select a random intensity
uint8_t get_random_pixel_intensity(){
    return((uint8_t)random(0,255));
}

// uint8_t get_random_color(){
//     uint8_t random_color_setting[4];
//     random_color_setting[0] = get_random_pixel_intensity();
//     random_color_setting[1] = get_random_pixel_intensity();
//     random_color_setting[2] = get_random_pixel_intensity();
//     return random_color_setting;
// }

void setup(){
    Serial.begin(115200);
    delay(2000);
    Serial.println("In setup");
}

void loop(){
    update_pixel_number();
    // p.neoPixelClear();

    if( (pixelNumber1 - pixelNumber1/2) > 0 ) {
      delay( (pixelNumber1 - pixelNumber1/2)*2 );
    } else {
       delay( -(pixelNumber1 - pixelNumber1/2)*2 );
    }
    
    p.neoPixelSetValue( pixelNumber1-1, BASE_RED+50, BASE_GREEN, BASE_BLUE, false );
    p.neoPixelSetValue( pixelNumber1, 100, 100, 100, false );
    p.neoPixelSetValue( pixelNumber1+1, BASE_RED+50, BASE_GREEN, BASE_BLUE, true );

    // clear all pixels
    delay( 50 );
    p.neoPixelFill( BASE_RED, BASE_GREEN, BASE_BLUE );

    }
