#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 11, TXPin =10;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
}
String datax;
char serial_encode[100];
void loop()
{
  
  while (ss.available() > 0){
    datax = ss.readStringUntil('\r');
    int a =datax.indexOf( "$GPRMC"); //jika ada 0
    if (a>=0){
      Serial.println(datax);
      int start = datax.indexOf("$");
      datax=datax.substring(start,datax.length());
      int panjangdata= datax.length()+1;
      datax.toCharArray(serial_encode,panjangdata);
      serial_encode[panjangdata+1]='\r';
      serial_encode[panjangdata+2]='\n';
      
      for (int i=0;i<panjangdata+2;i++){
         if (gps.encode(serial_encode[i])){
              displayInfo();
         }
         
      }
    }
  }

    

}

void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print("A");
    Serial.print(gps.location.lat(), 6);
    Serial.print("B");
    Serial.print(gps.location.lng(), 6);
    Serial.println("C");
  }
  else
  {
    //-7.3243005,
    Serial.print("A");
    Serial.print("-7.3243005");
    Serial.print("B");
    Serial.print("112.7965661");
    Serial.println("C");
  }

delay(100);
}
