#include <Adafruit_NeoPixel.h>

#define PIN             6
#define NUMPIXELS       7

#define RED             0
#define GREEN           1
#define BLUE            2

#define PATLENGTH       8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int frequency = 15; // 30 for 60 fps
int bstring = 181;
int I [3] = {0, 255, 0};

void setup()
{
    // initialize serial connection
    Serial.begin(9600);

    // initialize the neopixel
    pixels.begin();
}

void loop()
{

    // check if there are any bytes available
    if (Serial.available() > 0)
    {

        // parse new strobe configuration
        parseConfig();

    } else {
        
        // flash LED with given pattern
        flashPattern();
    }

}

void flashPattern()
{

    for (int i = 0; i < PATLENGTH; i++)
    {
        if ((bstring >> i) & 1)
        {
            // flash
            for (int i=0; i < NUMPIXELS; i++)
            {
                pixels.setPixelColor(i, pixels.Color(I[RED], I[GREEN], I[BLUE])); 
                pixels.show();
            }

        } else {

            // flash
            for (int i=0; i < NUMPIXELS; i++)
            {
                pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
                pixels.show();
            }
        }
        
        // delay
        float T = 1.0 / frequency;
        delay(T * 1000);
    }

}

void parseConfig()
{
    // extract data from fields  
    if (Serial.find("R"))
    {
        int red = Serial.parseInt();
        I[RED] = (red > 255) ? 255 : red;
    }

    if (Serial.find("G"))
    {
        int green = Serial.parseInt();
        I[GREEN] = (green > 255) ? 255 : green;
    }

    if (Serial.find("B"))
    {
        int blue = Serial.parseInt();
        I[BLUE] = (blue > 255) ? 255 : blue;
    }

    if (Serial.find("S"))
    {
        bstring = Serial.parseInt();
    }

    if (Serial.find("F"))
    {
        frequency = Serial.parseInt();
    }

    // visual confirmation
    for (int i=0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, pixels.Color(255, 255, 255)); 
        pixels.show();
    }
    delay(3000);
}

