// OE5RNL


#include <Arduino.h>

#include <TimeLib.h>
#include "p13.h"
#include <Servo.h>

Servo elevation;
Servo azimuth;

// Current UTC [NOT LOCAL TIME]
int CurrentHour   = 22;
int CurrentMin    = 38;
int CurrentSec    = 00;
int CurrentDay    = 9;
int CurrentMonth  = 7;
int CurrentYear   = 2022;

// get iss tle data
// https://celestrak.org/NORAD/elements/gp.php?CATNR=25544

const char *tleName = "ISS (ZARYA)";             
const char *tlel1   = "1 25544U 98067A   22190.57969253  .00066610  00000+0  11684-2 0  9990";
const char *tlel2   = "2 25544  51.6423 225.6846 0004496 348.1835 130.6069 15.49916440348655";

// Set your Callsign and current location details
const char  *pcMyName = "test";     // Observer name 
double       dMyLAT   = +48.2950;    // Latitude (Breitengrad): N -> +, S -> -
double       dMyLON   = +14.2812;    // Longitude (Längengrad): E -> +, W -> -
double       dMyALT   = 290.0;        // Altitude ASL (m)

int rangePin = 7;   // LED for in Range Indication
int NrangePin = 6;  // LED pin for Out of range indication

int epos = 0; 
int apos = 0;

double dSatLAT  = 0; // Satellite latitude
double dSatLON  = 0; // Satellite longitude
double dSatAZ   = 0; // Satellite azimuth
double dSatEL   = 0; // Satellite elevation

char acBuffer[20]; // Buffer for ASCII time

int led = 13;
char buff[50];
int time = 0;

void setup()
{

  pinMode(led, OUTPUT);

  Serial.begin(9600);
  Serial.print("Init");

  setTime(CurrentHour,CurrentMin,CurrentSec,CurrentDay,CurrentMonth,CurrentYear);

  elevation.attach(9);
  azimuth.attach(10);

  elevation.write(epos);
  azimuth.write(apos);

  pinMode(NrangePin, OUTPUT);
  pinMode(rangePin, OUTPUT);

  digitalWrite(NrangePin, HIGH);
  digitalWrite(rangePin, HIGH);

  delay(5000);
}


void loop()
{
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);

  int iYear    = year();        // Set start year
  int iMonth   = month();       // Set start month
  int iDay     = day();         // Set start day
  int iHour    = hour();        // Set start hour [ substract -6 from current time ???]
  int iMinute  = minute();      // Set start minute
  int iSecond  = second();      // Set start second

  //P13Sun Sun;                                                       // Create object for the sun

  P13Observer MyQTH(pcMyName, dMyLAT, dMyLON, dMyALT);              // Set observer coordinates
  P13Satellite MySAT(tleName, tlel1, tlel2);                        // Create ISS data from TLE
                
  P13DateTime MyTime(iYear, iMonth, iDay, iHour, iMinute, iSecond); // Set start time for the prediction
  MyTime.ascii(acBuffer);             // Get time for prediction as ASCII string
  MySAT.predict(MyTime);              // Predict ISS for specific time

  //MySAT.latlon(dSatLAT, dSatLON);     // Get the rectangular coordinates
  MySAT.elaz(MyQTH, dSatEL, dSatAZ);  // Get azimut and elevation for MyQTH

  Serial.print("Azimuth: "); Serial.println(dSatAZ,2);
  Serial.print("Elevation: "); Serial.println(dSatEL,2);
  Serial.println("");

  delay(500);

  // Servo calculation
  epos = (int)dSatEL;
  apos = (int)dSatAZ;

  // Range Leds and Servo Position
  if (epos < 0) {
      digitalWrite(NrangePin, HIGH);
      digitalWrite(rangePin, LOW);
  } else {
      digitalWrite(NrangePin, LOW);
      digitalWrite(rangePin, HIGH);

      if(apos < 180) {
        apos = abs(180 - (apos));
        epos = 180-epos;

      } else {
        apos = (360-apos);
        epos = epos;
      }
      azimuth.write(apos);
      delay(15);   
      elevation.write(epos);        
  }
}
