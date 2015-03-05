#include "mbed.h"
#include "SHT2x.h"

SHT2x sht21(p9, p10);

DigitalOut myled(LED2);
Serial pc(USBTX, USBRX);

int rh, temp;
int error;
float relHumidity, temperature;
int userRegister;

int main() {
    sht21.SHT2x_SoftReset();
    
    error |= sht21.SHT2x_ReadUserRegister(&userRegister);  //get actual user reg
    userRegister = (userRegister & ~SHT2x_RES_MASK) | SHT2x_RES_12_14BIT;
    error |= sht21.SHT2x_WriteUserRegister(&userRegister); //write changed user reg    
    
    while (1) {
        myled = 1;
        
        pc.printf("program start\r\n");
        error |= sht21.SHT2x_MeasureHM(HUMIDITY, &rh);
        error |= sht21.SHT2x_MeasureHM(TEMP, &temp);
        
        if (error > 0)
            pc.printf("error code %d \r\n", error);

        relHumidity = sht21.SHT2x_CalcRH(rh);
        temperature = sht21.SHT2x_CalcTemperatureC(temp);
        
        pc.printf("RH value -> %f \r\n", relHumidity);
        pc.printf("Temp in C -> %f \r\n", temperature);
        pc.printf("Dew point %f \r\n", sht21.SHT2x_GetDewpoint(relHumidity, temperature));

        myled = 0;
        wait(1);
    }
}
