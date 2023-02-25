namespace CloudChamber
{
    const uint8_t oneWirePin {2};
    const uint8_t LEDPin {3};
    const uint8_t numberOfLEDs {10};
    const char* chipset {"WS2812B"};
    const char* colorOrder {"RGB"};
    const unsigned long sensorUpdateInterval {2000};
    //2810F219000000CB
    //2841691900000015
    //282FFE18000000AC
    const DeviceAddress chamber{0x28, 0x10, 0xF2, 0x19, 0x00, 0x00, 0x00, 0xCB};
    const DeviceAddress hotSide{0x28, 0x41, 0x69, 0x19, 0x00, 0x00, 0x00, 0x15};
    const DeviceAddress ambient{0x28, 0x2F, 0xFE, 0x18, 0x00, 0x00, 0x00, 0xAC};
    const DeviceAddress* temperatureAddresses[] {&hotSide, &chamber, &ambient};

}
