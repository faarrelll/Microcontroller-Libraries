#include <TinyGPS++.h>
#include <SoftwareSerial.h>
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(11, 10);

SoftwareSerial sim(3, 2);

void setup()
{
  Serial.begin(9600);
  ss.begin(9600);
  sim.begin(9600);
  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
  delay(2000);
}
String datax;
char serial_encode[100];
void loop()
{
  /*ss.listen();
  Serial.println("Data from port one:");
  while (ss.available() > 0){
    char inByte = ss.read();
    Serial.write(inByte);
    
  }
  sim.listen();
  while (sim.available() > 0){}
  delay(2000);
  Serial.println("Ulang");

    */

  ss.listen();
  String coba;
  bool tunggu=false;
  while (ss.available() > 0) {
    char inByte = ss.read();
    if (inByte=='M'){tunggu=true;}
    if (tunggu==true && inByte=='\r'){break;}
    coba=coba+inByte;
  }
  proses(coba);

  // Now listen on the second port
  sim.listen();
  
  while (sim.available() > 0) {
    char inByte = sim.read();
    
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
