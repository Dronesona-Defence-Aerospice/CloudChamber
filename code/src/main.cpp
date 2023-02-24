#include <Arduino.h>
#include "FastLED.h"
#include "DallasTemperature.h"
#include "OneWire.h"
#include "constants.h"

OneWire oneWire(2);
DallasTemperature temperatureSensors(&oneWire);
CRGB leds[CloudChamber::numberOfLEDs];
template<class T> inline Print &operator <<(Print& obj, T arg) { obj.print(arg); return obj; } 


void printAddresses(DallasTemperature& ds)
{
    auto amount = ds.getDS18Count();
    for(uint8_t i = 0; i < amount; ++i )
    {
        DeviceAddress deviceAddress;
        ds.getAddress(deviceAddress, i);
        for (uint8_t i = 0; i < 8; i++)
        {
            // zero pad the address if necessary
            if (deviceAddress[i] < 16) Serial.print("0");
            Serial.print(deviceAddress[i], HEX);
        }
        Serial.println();
    }
}


void setup()
{
    using namespace CloudChamber;
    FastLED.addLeds<WS2812B, CloudChamber::LEDPin, RGB>(leds, CloudChamber::numberOfLEDs);
    Serial.begin(115200);
    printAddresses(temperatureSensors);
    Serial << "### Dronesona Defence and Aerospice presents ### \n";
    Serial << "SpiceChamber\n";
    temperatureSensors.begin();
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
        temperatureSensors.requestTemperatures();
        Serial << "Inside: " << temperatureSensors.getTempC(CloudChamber::chamber) << "°C\n";
        Serial << "Hotside: " << temperatureSensors.getTempC(CloudChamber::hotSide) << "°C\n";
        Serial << "Ambient: " << temperatureSensors.getTempC(CloudChamber::ambient) << "°C\n";
        timestamp = {millis()};
    }
    
}
