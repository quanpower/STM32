#include "mbed.h"
#include "SHTx/sht15.hpp"

Serial pc(USBTX, USBRX);
DigitalOut busy(LED1);

// I used D9 and D10 here  but you
// can use any other GPIO as well.
SHTx::SHT15 sensor(D9, D10);

int
main() {
    // Speed things up a bit.
    sensor.setOTPReload(false);
    sensor.setResolution(true);
    
    while(1) {
        busy = true;
        sensor.update();
        busy = false;
        
        // Temperature in celcius
        sensor.setScale(false);
        pc.printf("Temperature [ %3.2f C ]\r\n", sensor.getTemperature());
        
        // Temperature in fahrenheit
        sensor.setScale(true);
        pc.printf("            [ %3.2f F ]\r\n", sensor.getTemperature());
        
        // Relative Humidity
        pc.printf("Humdity     [ %3.2f %% ]\r\n\n", sensor.getHumidity());
        
        
        wait(5);
    }
}
