#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>
#define buzzer A6
#define jumlahnomor 1

#define kontaktor1 A0
#define kontaktor2 A1
#define kontaktor3 A2
#define kontaktor4 A3

#define adrk1 1
#define adrk2 2
#define adrk3 3
#define adrk4 4


SMSGSM sms;

int r0 = 0;      
int r1 = 0;   
int r2 = 0; 
int tegangan[10];
bool volt[10];
char* myphone[jumlahnomor]={"+6285648912728"};
int numdata;
boolean started=false;
char sms_position;
char phone_number[20];
char sms_text1[200];
String sms_text;
bool sudah_sms[10];
String nama_panel[]={"AC1","AC2","AC3","AC4","AC5","AC6","AC7","AC8","AC9"};
int pin[]={kontaktor1,kontaktor2,kontaktor3,kontaktor4};

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

void setup() {
pinMode(kontaktor1,OUTPUT);
pinMode(kontaktor2,OUTPUT);
pinMode(kontaktor3,OUTPUT);
pinMode(kontaktor4,OUTPUT);

digitalWrite(kontaktor1,LOW);
digitalWrite(kontaktor2,LOW);
digitalWrite(kontaktor3,LOW);
digitalWrite(kontaktor4,LOW);


pinMode(buzzer, OUTPUT);
digitalWrite(buzzer,LOW);

Serial.begin(9600);
lcd.begin(16, 2);
lcd.clear();
lcd.print("Checking Wavecom...!!!");
bep(3);        
if (gsm.begin(9600)) 
{
        Serial.println("\nstatus=READY");
        lcd.clear();
        lcd.print("System Ready !!!");
        delay(3000);
        read_con();
} 
else
    {
      int data=1;
      Serial.println("\nTry and Reset");
      lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Device Not Ready");
            lcd.setCursor(0,1);
            lcd.print("Reset Device");
      while(data==1){

       
      }
     
    }
       
}

void loop() {
 read_sensor();
 checkcondition();
sms_position = sms.IsSMSPresent(SMS_UNREAD);
 if (sms_position)
      {
        Serial.print("SMS postion:");
        Serial.println(sms_position, DEC);
        sms.GetSMS(sms_position, phone_number, sms_text1, 100);
        Serial.println(phone_number);
        Serial.println(sms_text1);
        sms_text=String(sms_text1);
        Serial.println(sms_text);
        activation_sms();
        if (sms_position>1){
          for (int i=1;i<=sms_position;i++)
          {
            sms.DeleteSMS(i);
            delay(2000);
          }
        }
        else
        {
          sms.DeleteSMS(sms_position);
        }
        
     }

lcd.setCursor(0,0);
lcd.print ("AC="+String(volt[1])+String(volt[2])+String(volt[3])+String(volt[4])+String(volt[5])+String(volt[6])+
String(volt[7])+String(volt[8])+String(volt[9])+ "      ");
lcd.setCursor(0,1);
lcd.print ("RELAY="+ String(digitalRead(kontaktor1))+String(digitalRead(kontaktor2)));
lcd.print (String(digitalRead(kontaktor3))+String(digitalRead(kontaktor4))+"        ");
delay(1000);       
}


