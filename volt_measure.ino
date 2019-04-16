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
#include <Wire.h>
#include <Adafruit_ADS1015.h>
int sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
double voltage = 0.0;           // calculated voltage
const double magicNumber = 5.34392;
SoftwareSerial XBee(2, 3); // RX, TX
Adafruit_ADS1015 ads;

void setup()
{
    Serial.begin(9600);
    XBee.begin(9600);
    ads.begin();
    ads.setGain(GAIN_ONE); 
    //Serial.begin(9600);
    //ads.setGain(GAIN_EIGHT); 
}

void loop()
{
    int adc0, adc1, adc2, adc3;

    adc0 = ads.readADC_SingleEnded(0);
    adc1 = ads.readADC_SingleEnded(1);
    adc2 = ads.readADC_SingleEnded(2);
    adc3 = ads.readADC_SingleEnded(3);
    

    Serial.print("ADC 0 -");
    Serial.print(adc0);
    Serial.println("");
    XBee.print(adc0);
    XBee.print(" ");
    XBee.print(adc1);
    XBee.print(" ");
    XBee.print(adc2);
    XBee.print(" ");
    XBee.print(adc3);

    XBee.println();


    delay(100);
}