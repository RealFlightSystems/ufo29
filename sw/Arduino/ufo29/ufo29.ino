//29mm UFO saucer - 2 Sides, 105 WS2812 LED's per side

#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Attiny85
#endif

//Attiny85 pins 
#define PIN         PB4

//Bringup with one pixel for safety
//#define N_PIXELS    1
//Full array
#define N_PIXELS   105
#define BUTTON_PIN  PB3


boolean oldState = HIGH;
boolean newState = HIGH;

#define STATE_CHANGE (newState ^ oldState)


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoPixel pixel(N_PIXELS, PIN, NEO_GRB+ NEO_KHZ800);
int i,j;

void setRandomColor(int i)
{
    pixel.setPixelColor(i, random(255), random(255), random(255));
}

//Effects Library
void setDisplay(int r, int g, int b, int d)
{
  for (int i = 0; i < N_PIXELS; i++) { 
      pixel.setPixelColor(i, r, g, b);
  }
  pixel.show();
  delay(d);
}

void setAll(uint32_t color){
  for(int i=0; i<pixel.numPixels(); i++) { // For each pixel in pixel...
    pixel.setPixelColor(i, color);         //  Set pixel's color (in RAM)
  }
  pixel.show();                          //  Update strip to match
}

//Inner Ring: 25 leds
void setRing0(uint32_t color)
{
  for(int i=0; i< 25; i++) { 
    pixel.setPixelColor(i, color);  
  }
  //pixel.show();
}

//Middle Ring: 35 leds
void setRing1(uint32_t color)
{
  for(int i=25; i< 60; i++) { 
    pixel.setPixelColor(i, color);  
  }
  //pixel.show();
}

//Outer Ring: 45 leds
void setRing2(uint32_t color)
{
  for(int i=60; i< 105; i++) { 
    pixel.setPixelColor(i, color);  
  }
  //pixel.show();
}

void setRing(int ring, uint32_t color)
{

    ring %= 3;
#if 0    
    if (ring < 0){
      ring = 0;
    }
  
    if (ring >= 3) {
        ring = 0;
    }
#endif
    switch(ring) { 
    case 0: 
      setRing0(color);
      break;
    case 1:
      setRing1(color);
      break;
    case 2:
      setRing2(color);
      break;
    }
}


#define RED     pixel.Color(255,0, 0)
#define ORANGE  pixel.Color(255,69,0)
#define YELLOW  pixel.Color(255,255,0)
#define GREEN   pixel.Color(0,255,0)
#define BLUE    pixel.Color(0,0,255)
#define INDIGO  pixel.Color(75,0,130)
#define VIOLET  pixel.Color(143,0,255)
#define WHITE   pixel.Color(255,255,255)


//https://www.comfsm.fm/~dleeling/cis/hsl_rainbow.html

/*  red hsl(0,100%,50%)
    orange hsl(30,100%,50%)
    yellow hsl(60,100%,50%)
    green hsl(120,100%,50%)
    cyan hsl(180,100%,50%)
    blue hsl(240,100%,50%)
    purple hsl(270,100%,50%)
    magenta hsl(300,100%,50%)
*/

// Emulate a Cuttlefish in the Abyss
void cuttleFish(int wait) 
{
   //Ring 0
   setRing(i, pixel.Color(255,0, 0)); //Red
   pixel.show();
   delay(wait); 
   i++;
   //Ring 1
   setRing(i, pixel.Color(255,69,0)); //Orange
   pixel.show();
   delay(wait);
   i++;   
   //Ring 2
   setRing(i, pixel.Color(255,255,0));//Yellow
   pixel.show();   
   delay(wait);
   i++;   
   setRing(i, pixel.Color(0,255,0)); //Green
   pixel.show();   
   delay(wait);   
   i++;   
   setRing(i, pixel.Color(0,0,255)); //Blue
   pixel.show();   
   delay(wait);   
   i++;   
   setRing(i, pixel.Color(75,0,130));//Indigo
   pixel.show();   
   delay(wait);   
   i++;   
   setRing(i, pixel.Color(143,0,255));//Violet
   pixel.show();   
   delay(wait);
   i++;
   setRing(i, pixel.Color(255,255,255));
   pixel.show();   
   delay(wait);   
   i++;
   
}

#define START 1
#define END   65535
#define STEP 1500

// Rainbow cycle red-orange/magenta
// This range of colors works well for the blown glass jellyfish 
// I got at the Monterey Seaquarium for my daughter when she was 7 years old
void jellyRainbow2(int wait) {
  for(long firstPixelHue = START; firstPixelHue <= END; firstPixelHue +=STEP) {
      setAll(pixel.gamma32(pixel.ColorHSV(firstPixelHue)));
      delay(wait);  // Pause for a moment
      if(STATE_CHANGE)
        return;
  }
  for(long secondPixelHue = END; secondPixelHue >= START; secondPixelHue -=STEP) {
      setAll(pixel.gamma32(pixel.ColorHSV(secondPixelHue)));
      delay(wait);  // Pause for a moment
      if(STATE_CHANGE)
        return;
  }
}

// Rainbow cycle along whole pixel. Pass delay time (in ms) between frames.
void rainbow2(int wait) {
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    for(int i=0; i<pixel.numPixels(); i++) { // For each pixel in pixel...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (pixel.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / pixel.numPixels());
      // pixel.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through pixel.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      setRing(i, pixel.gamma32(pixel.ColorHSV(pixelHue)));
    }
    if(STATE_CHANGE)
        return;
    pixel.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow cycle red-orange/magenta
// This range of colors works well for the blown glass jellyfish 
// I got at the Monterey Seaquarium for my daughter when she was 7 years old
void jellyRainbow(int wait) {
  for(long firstPixelHue = START; firstPixelHue <= END; firstPixelHue +=STEP) {
      setAll(pixel.gamma32(pixel.ColorHSV(firstPixelHue)));
      pixel.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
      if(STATE_CHANGE)
        return;
  }
   for(long secondPixelHue = END; secondPixelHue >= START; secondPixelHue -=STEP) {
      setAll(pixel.gamma32(pixel.ColorHSV(secondPixelHue)));
      pixel.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
      if(STATE_CHANGE)
        return;
  }

}

// Rainbow cycle along whole pixel. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    for(int i=0; i<pixel.numPixels(); i++) { // For each pixel in pixel...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (pixel.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / pixel.numPixels());
      // pixel.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through pixel.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      pixel.setPixelColor(i, pixel.gamma32(pixel.ColorHSV(pixelHue)));
      if(STATE_CHANGE)
        return;
    }
    if(STATE_CHANGE)
        return;
    pixel.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}





#define THEATER_DITHER_VALUE 3

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la pixel.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<THEATER_DITHER_VALUE; b++) { //  'b' counts from 0 to 2...
      pixel.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<pixel.numPixels(); c += THEATER_DITHER_VALUE) {
        pixel.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        if(STATE_CHANGE)
        return;
      }
      pixel.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<THEATER_DITHER_VALUE; b++) { //  'b' counts from 0 to 2...
      pixel.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<pixel.numPixels(); c += THEATER_DITHER_VALUE) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (pixel.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / pixel.numPixels();
        uint32_t color = pixel.gamma32(pixel.ColorHSV(hue)); // hue -> RGB
        pixel.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        if(STATE_CHANGE)
        return;
      }
      pixel.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// pixel.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixel.numPixels(); i++) { // For each pixel in pixel...
    pixel.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    
    if ((i == 25)  || (i == (25 + 35)) || (i == 104)){
      pixel.show();                          //  Update strip to match
      delay(wait);                           //  Pause for a moment
    }
  }
}


void strobe(void)
{
    setDisplay(255, 255, 255, 63); 
    setDisplay(0,0,0,63);
}


void police_strobe(void)
{
    setDisplay(255, 0, 0, 163); 
    setDisplay(0,0,0,163);
    setDisplay(0, 0, 255, 163); 
    setDisplay(0,0,0,163);
}


void police_strobe2(void)
{
  for(i = 0; i < 2; i++) { 
      setDisplay(255, 0, 0, 125); 
      setDisplay(0,0,0,125);
  }
  for(i = 0; i < 2; i++) { 
    setDisplay(0, 0, 255, 125); 
    setDisplay(0,0,0,125);
  }
}

//mass hysteria!
//modeled after https://www.youtube.com/watch?v=FVY5uZ18-x8
void pokemon_shock(void)
{
  //Orange flash at 18hz
  for(i = 0; i < 20; i++) { 
      setDisplay(255, 255, 0, 63); 
      setDisplay(0,0,0,63);
  }

  if(STATE_CHANGE)
      return;
      
  for(i = 0; i < 20; i++) { 
      setDisplay(255, 255, 0, 10); 
      setDisplay(0,0,0,10);
  }

  if(STATE_CHANGE)
      return;
  
  //Red/Blue 
  for(i = 0; i < 20; i++) { 
      setDisplay(255, 0, 0, 50); 
      setDisplay(0,0,0,50);
      setDisplay(0, 0, 255, 50); 
      setDisplay(0,0,0,50);
  }

  if(STATE_CHANGE)
      return;
  
  for(i = 0; i < 5; i++) { 
      setDisplay(255, 0, 0, 100); 
      setDisplay(0,0,0,5);
      setDisplay(0, 0, 255, 100); 
      setDisplay(0,0,0,5);
  }
  
  if(STATE_CHANGE)
      return;
  
  for(i = 0; i < 40; i++) { 
    setDisplay(255, 255, 255, 43); 
    setDisplay(0,0,0,43);
  }
  
  if(STATE_CHANGE)
      return;
  
  for(i = 0; i < 2; i++) { 
    setDisplay(255, 255, 255, 500); 
    setDisplay(0,0,0,500);
  }

 if(STATE_CHANGE)
      return;
  
}

//Arduino setup/loop
#define N_MODES     22
//int     mode     = 22;    
int     mode     = 0;
int     delayValue = 50;
int     demoCounter = 0;

void setup() 
{
  pinMode(BUTTON_PIN, INPUT_PULLUP); //Input button

  // These lines are specifically to support the Attiny85 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  // Attach Interrupt to Interrupt Service Routine
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),checkSwitch, FALLING); 
  
  pixel.begin();
  pixel.setBrightness(90); //production
  //pixel.setBrightness(3); //dev
  pixel.show();
}

void checkSwitch() {
  // Check status of switch
  //if (digitalRead(BUTTON_PIN) == LOW) {
  if (digitalRead(BUTTON_PIN) ^ newState) {
      oldState = newState;
      newState ^=1;
  }
}

 
void loop()
{
    // Get current button state.
    newState = digitalRead(BUTTON_PIN);
  
    // Check if state changed from high to low (button press).
    //if((newState == LOW) && (oldState == HIGH)) {
    if(newState ^ oldState ) {
  
      // Short delay to debounce button.
      delay(20);

      // Check if button is still low after debounce.
      newState = digitalRead(BUTTON_PIN);

      //if(newState == LOW) {      // Yes, still low
      if(newState ^ oldState) {
        if(++mode > N_MODES) 
            mode = 0; // Advance to next mode, wrap around after #8

      }
    }

    delayValue -= 5;
    if (delayValue <= 0){ 

    if (mode > 0 && mode <= 6)
      delayValue = 500;

    }
    switch(mode) {           // Start the new animation...
        case 0:
          colorWipe(pixel.Color(  0,   0,   0), 10);    // Black/off
          break;
        case 1:
          colorWipe(pixel.Color(255,   0,   0), 5);    // Red
          colorWipe(pixel.Color(  0,   0,   0), 5);    // Black/off
          break;
        case 2:
          colorWipe(pixel.Color(  0, 255,   0), 5);    // Green
          colorWipe(pixel.Color(  0,   0,   0), 5);    // Black/off
          break;
        case 3:
          colorWipe(pixel.Color(  0,   0, 255), 5);    // Blue
          colorWipe(pixel.Color(  0,   0,   0), 5);    // Black/off
          break;
        case 4:
          theaterChase(pixel.Color(127, 127, 127), 5); // White
          colorWipe(pixel.Color(  0,   0,   0), 5);    // Black/off
          break;
        case 5:
          theaterChase(pixel.Color(127,   0,   0), 10); // Red
          colorWipe(pixel.Color(  0,   0,   0), 10);    // Black/off
          break;
        case 6:
          theaterChase(pixel.Color(  0,   0, 127), 10); // Blue
          colorWipe(pixel.Color(  0,   0,   0), 10);    // Black/off
          break;
        case 7:
        // rainbow(10);
         rainbow(0);
         break;
        case 8:
         rainbow2(0);
         break;
        case 9:
         jellyRainbow(10);
         break;
        case 10:
         jellyRainbow(0);
         break;
        case 11:
         theaterChaseRainbow(10);
         break;
        case 12:
         theaterChaseRainbow(50);
         break;
        case 13:
         theaterChase(RED, 50);    // Red
         theaterChase(ORANGE, 50); // Orange
         theaterChase(YELLOW, 50); // Yellow
         theaterChase(GREEN, 50);  // Green
         theaterChase(BLUE, 50);   // Blue
         theaterChase(INDIGO, 50); // Indigo
         theaterChase(VIOLET, 50); // Violet
         theaterChase(WHITE, 50);  // White
         theaterChaseRainbow(50);
         break;      
        case 14:
         colorWipe(pixel.Color(255,   0,   0), 0);    // Red
         colorWipe(pixel.Color(  0, 255,   0), 0);    // Green
         colorWipe(pixel.Color(  0,   0, 255), 0);    // Blue
         colorWipe(pixel.Color(  0,   0,   0), 0);    // Black/off
         break;

//#define STROBE_DELAY1 41
//#define STROBE_DELAY2 83

/* https://en.wikipedia.org/wiki/Flashes_per_minute
 *  Flashes per minute, or FPM, is simply the number of times a flashing light blinks per minute. 
 *  Police and emergency vehicles use warning lights with flashing rates that typically fall in 
 *  a range from 60 to 240 FPM. In North America, grade crossing signals have a flashing rate 
 *  ranging between 45 to 65 FPM with the ideal rate being 60 FPM.
 *
 *  Persons with photosensitive epilepsy may suffer a seizure in response to a specific flashing frequency, 
 *  e.g. 420 FPM, but the exact triggering frequency varies across individuals. To minimize the likelihood 
 *  of an epileptogenic response, flashing rates above 300 FPM (5 Hz) should be avoided (Harding and Jeavons, 1994).
 * For conversion purposes, 60 FPM = 1 Hz (i.e. a frequency of one per second). 
 * 
 */
#define FPM60(x) (1000/(x))
#define FPM120  (FPM60(2))
#define FPM240  (FPM60(4))
#define FPM480  (FPM60(8))

#define FPM FPM480


#define STROBE_DELAY1 125
#define STROBE_DELAY2 125

        case 15:
          //Strobe
          setAll(pixel.Color(255,   255,   255));    // White
          delay(STROBE_DELAY1);
          setAll(pixel.Color(  0,   0,   0));
          delay(STROBE_DELAY1);
          //setAll(pixel.Color(255,   255,   255));    // White
          theaterChase(pixel.Color(255, 255, 255), 0); // White
          delay(STROBE_DELAY2);
          setAll(pixel.Color(  0,   0,   0));
          delay(STROBE_DELAY2);
          break;

        case 16:
          //Strobe
          //setAll(pixel.Color(255,   0,   0));
          theaterChase(pixel.Color(255, 0, 0), 0); 
          delay(FPM);
          //setAll(pixel.Color(0, 0, 255)); 
          theaterChase(pixel.Color(0, 255, 0), 0); 
          delay(FPM);
          theaterChase(pixel.Color(0, 0, 255), 0); 
          delay(FPM);
          theaterChase(pixel.Color(255, 255, 255), 0); 
          delay(FPM);
          theaterChase(pixel.Color(random(255), random(255), random(255)), 0); 
          delay(FPM);
          break;

       case 17:
         for(i = 0; i < pixel.numPixels(); i++) { 
           setRandomColor(i);             
         }
         pixel.show();
         delay(10);
         setAll(pixel.Color(  0,   0,   0));
         break;

       case 18:
         strobe();
         break;

       case 19:
         police_strobe();
         break;
         
       case 20:
         police_strobe2();
         break;
         
       case 21: 
         pokemon_shock();
         break;
         
       case 22:
         cuttleFish(30);
         break;

    }

#if 0
//Loop through each one 10x each
    if (++demoCounter > 1) { 
      mode++;
      demoCounter = 0;
    }
#endif    

  oldState = newState;
}
