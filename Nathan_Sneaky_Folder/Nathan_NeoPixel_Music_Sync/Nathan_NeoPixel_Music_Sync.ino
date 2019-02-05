 
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6
#define PIN2            7
#define PIN3            8

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8

int analogPin = A0; // MSGEQ7 OUT
int strobePin = 2; // MSGEQ7 STROBE
int resetPin = 4; // MSGEQ7 RESET
int spectrumValue[7];
 
// MSGEQ7 OUT pin produces values around 50-80
// when there is no input, so use this value to
// filter out a lot of the chaff.
int filterValue = 80;
 
// LED pins connected to the PWM pins on the Arduino
 
int ledPinR = 9;
int ledPinG = 10;
int ledPinB = 11;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  Serial.begin(9600);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  pixels2.begin(); // This initializes the NeoPixel library.
  pixels3.begin(); // This initializes the NeoPixel library.
  // Read from MSGEQ7 OUT
  pinMode(analogPin, INPUT);
  // Write to MSGEQ7 STROBE and RESET
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
 
  // Set analogPin's reference voltage
  analogReference(DEFAULT); // 5V
 
  // Set startup values for pins
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
}

void loop() {

  // Set reset pin low to enable strobe
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
 
  // Get all 7 spectrum values from the MSGEQ7
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(strobePin, LOW);
    delayMicroseconds(30); // Allow output to settle
 
    spectrumValue[i] = analogRead(analogPin);
 
    // Constrain any value above 1023 or below filterValue
    spectrumValue[i] = constrain(spectrumValue[i], filterValue, 1023);
 
 
    // Remap the value to a number between 0 and 255
    spectrumValue[i] = map(spectrumValue[i], filterValue, 1023, 0, 255);
 
    // Remove serial stuff after debugging
    Serial.print(spectrumValue[i]);
    Serial.print(" ");
    digitalWrite(strobePin, HIGH);
   }
 
   Serial.println();
 
   // Write the PWM values to the LEDs
   // I find that with three LEDs, these three spectrum values work the best
   analogWrite(ledPinR, spectrumValue[1]);
   analogWrite(ledPinG, spectrumValue[4]);
   analogWrite(ledPinB, spectrumValue[6]);





     // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    
    if (spectrumValue[5] > 80                              ) {
      //pixels.setPixelColor(i, pixels.Color(spectrumValue[1],spectrumValue[4],spectrumValue[6])); // Moderately bright green color.
      pixels.setPixelColor(i, pixels.Color(0,(spectrumValue[5] + 25),0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else {
      spectrumValue[5] = 0;
      //pixels.setPixelColor(i, pixels.Color(spectrumValue[1],spectrumValue[4],spectrumValue[6])); // Moderately bright green color.
      pixels.setPixelColor(i, pixels.Color(0,spectrumValue[5],0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }

    if (spectrumValue[3] > 65) {
    //pixels2.setPixelColor(i, pixels2.Color(spectrumValue[1],spectrumValue[4],spectrumValue[6])); // Moderately bright green color.
    pixels2.setPixelColor(i, pixels2.Color(0,0,(spectrumValue[3] - 25))); // Moderately bright green color.
    pixels2.show(); // This sends the updated pixel color to the hardware.
    }
    else {
      spectrumValue[3] = 0;
      //pixels2.setPixelColor(i, pixels2.Color(spectrumValue[1],spectrumValue[4],spectrumValue[6])); // Moderately bright green color.
      pixels2.setPixelColor(i, pixels2.Color(0,0,spectrumValue[3])); // Moderately bright green color.
      pixels2.show(); // This sends the updated pixel color to the hardware.
    }

    if (spectrumValue[0] > 120) {
    //pixels3.setPixelColor(i, pixels3.Color(spectrumValue[1],spectrumValue[4],spectrumValue[6])); // Moderately bright green color.
    pixels3.setPixelColor(i, pixels3.Color(spectrumValue[0],0,0)); // Moderately bright green color.
    pixels3.show(); // This sends the updated pixel color to the hardware.
    }
    else {
      spectrumValue[0] = 0;
      //pixels2.setPixelColor(i, pixels2.Color(spectrumValue[1],spectrumValue[4],spectrumValue[6])); // Moderately bright green color.
      pixels3.setPixelColor(i, pixels3.Color(spectrumValue[0],0,0)); // Moderately bright green color.
      pixels3.show(); // This sends the updated pixel color to the hardware.
    }

  }
  
}
