/* Flicker - Challenge Code for Ladies Learning Code Arduino Workshop; 
 * Written By Kelsey Shorten
 * 15/08/2018
 */


#include <FastLED.h>
    #define DATA_PIN 6
    #define ANALOG_READ 0
    #define NUM_LEDS 70
    #define SAMPLE_LENGTH 3 // How many samples to average by 
    
    
    // Colour variables 
    int r = 25;
    int g = 100;
    int b = 200;
    int red_change = 10;
    int blue_change = 10;
    int green_change = 10;
    int pulse = 100; 
    int pulse_change = 1;
    
    // counter variable
    int k = 0;
    
    // array, with length of the number of samples, for holding the other samples for the average
    int previousLED[SAMPLE_LENGTH];
    
    CRGB leds[NUM_LEDS];
    

    void setup() {
        Serial.begin(9600);
        // put your setup code here, to run once:
        
        // LED strip setup
        FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
        k = 0;
        // set samples to zero 
        for (int j = 0; j < SAMPLE_LENGTH; j++) {
          previousLED[j] = 0;
        }

    }
    void loop() {
      
        // Read the sensor value
        int sensor_value = analogRead(ANALOG_READ);
        
        // get rolling average
        float sum = 0;
        for(int j = 0; j < SAMPLE_LENGTH; j++){
          sum += previousLED[j]; 
        }
        float avg = sum / SAMPLE_LENGTH;
        
        
        // Set your colour change. IF it's getting louder, get redder, if quieter, get bluer.
        // We set this colour change using a custom function (fadeTo). 
        // Green is set to just pulse from 0 to 255 and back again 
        
        if ( avg < sensor_value) {
          fadeTo(240-red_change, pulse, 0 + blue_change);
        } else {
          fadeTo(0+red_change, pulse , 240 - blue_change);
        }
        
        // Figure out how many LED lights you want to light up 
        int numLedsToLight = map(sensor_value, 50, 875, 0, NUM_LEDS);
        
        // Light up the LEDs with the colours we set earlier
        for (int led = 0; led <= numLedsToLight; led++) {
            leds[led] = CRGB( r , g, b) ;
        }
        
        // Turn off LEDs that aren't supposed to light up with a fade function
        for (int i = NUM_LEDS; i >= 0; i --){
          leds[i].fadeToBlackBy(10);
        }
        // Show all the LEDs
        FastLED.show();
        
        // store the previos n samples 
        previousLED[k] = sensor_value; 
        
        if (k < SAMPLE_LENGTH ){
          k = k +1;
        } else {
          k = 0; 
        }
        
        // Update the pulse value: 
        pulse = pulse + pulse_change;
        if (pulse > 255 || pulse  < 0){
          pulse_change = pulse_change * -1;
          pulse = pulse + pulse_change; 
        }
        
    }
    
    // Custom function to create the fade effect 
      void fadeTo(int r_target,int g_target, int b_target) {
      if ( r < r_target){
         r = r + red_change;
         
      } else {
        r = r - red_change;
      }
      
      if (g < g_target){
        g = g + green_change;
      } else {
        g = g - green_change;
      }
      
      if (b < b_target){
        b = b + blue_change;
      } else {
        b = b - blue_change;
      }
      
      
    }
    
