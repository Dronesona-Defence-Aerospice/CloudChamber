#include <Arduino.h>
#include "FastLED.h"
#include "DallasTemperature.h"
#include "OneWire.h"
#include "constants.h"

OneWire oneWire(2);
DallasTemperature temperatureSensor(&oneWire);
CRGB leds[CloudChamber::numberOfLEDs];
template<class T> inline Print &operator <<(Print& obj, T arg) { obj.print(arg); return obj; } 


void setup()
{
    using namespace CloudChamber;
    FastLED.addLeds<WS2812B, CloudChamber::LEDPin, RGB>(leds, CloudChamber::numberOfLEDs);
    Serial.begin(115200);
    Serial << "### Dronesona Defence and Aerospice presents ### \n";
    Serial << "SpiceChamber\n";
    temperatureSensor.begin();
    for(auto& led: leds)
    {
        led = CRGB::Red;
    }
    FastLED.show();
    
}


void loop()
{
    static unsigned long timestamp;
    while (millis() - timestamp > CloudChamber::sensorUpdateInterval)
    {
        temperatureSensor.requestTemperatures();
        Serial << "Temperature: " << temperatureSensor.getTempCByIndex(0) << "°C\n";
        timestamp = {millis()};
    }
    
}
