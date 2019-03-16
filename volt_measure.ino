/*--------------------------------------------------------------
  Program:      volt_measure

  Description:  Reads value on analog input A2 and calculates
                the voltage assuming that a voltage divider
                network on the pin divides by 11.
  
  Hardware:     Arduino Uno with voltage divider on A2.
                
  Software:     Developed using Arduino 1.0.5 software
                Should be compatible with Arduino 1.0 +

  Date:         22 May 2013
 
  Author:       W.A. Smith, http://startingelectronics.org
--------------------------------------------------------------*/

// number of analog samples to take per reading
#define NUM_SAMPLES 10
#include <SoftwareSerial.h>

int sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
float voltage = 0.0;            // calculated voltage
const float magicNumber = 5.409692;
SoftwareSerial XBee(2, 3); // RX, TX

void setup()
{
    Serial.begin(9600);
    XBee.begin(9600);
    Serial.begin(9600);
}

void loop()
{
    // take a number of analog samples and add them up
    while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A2);
        sample_count++;
        delay(20);
    }
    // calculate the voltage
    // use 5.0 for a 5.0V ADC reference voltage
    // 5.015V is the calibrated reference voltage
    voltage = ((float)sum / (float)NUM_SAMPLES * 5.015) / 1024.0;
    // send voltage for display on Serial Monitor
    // voltage multiplied by 11 when using voltage divider that
    // divides by 11. 11.132 is the calibrated voltage divide
    // value
    union
    {
        float fval;
        byte bval[4];
    } volt_measure;
    
    voltage = voltage * magicNumber;
    volt_measure.fval = voltage;
    Serial.print(voltage);
    Serial.println (" V");
    XBee.println(voltage);
    sample_count = 0;
    sum = 0;
    delay(250);
}