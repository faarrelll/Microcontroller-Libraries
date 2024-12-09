#define pin_col1 A0 //A3
#define pin_col2 A1 //A2
#define pin_col3 A2 //A1
#define pin_col4 A3 //A0

#define pin_bar1 A4 //A7
#define pin_bar2 A5 //A6
#define pin_bar3 A6 //A5
#define pin_bar4 A7 //A4

#define col1_on digitalWrite(pin_col1,LOW)
#define col1_off digitalWrite(pin_col1,HIGH)

#define col2_on digitalWrite(pin_col2,LOW)
#define col2_off digitalWrite(pin_col2,HIGH)


#define col3_on digitalWrite(pin_col3,LOW)
#define col3_off digitalWrite(pin_col3,HIGH)

#define col4_on digitalWrite(pin_col4,LOW)
#define col4_off digitalWrite(pin_col4,HIGH)

#define bar4 !convert(analogRead(pin_bar4))
#define bar3 !convert(analogRead(pin_bar3))
#define bar2 !digitalRead(pin_bar2)
#define bar1 !digitalRead(pin_bar1)

bool convert(int data){
  bool hasil = false;
  if (data>500){hasil=true;}
  return hasil;
}
void setup() {
  Serial.begin(9600);
  pinMode(pin_col1,OUTPUT);
  pinMode(pin_col2,OUTPUT);
  pinMode(pin_col3,OUTPUT);
  pinMode(pin_col4,OUTPUT);


  pinMode(pin_bar1,INPUT_PULLUP);
  pinMode(pin_bar2,INPUT_PULLUP);


  
}

void loop() {
Serial.println(get_keypad());
delay(100);
}

void xloop() {
col1_off;col2_off;col3_off;col4_on;
Serial.print(bar1);
Serial.print(bar2);
Serial.print(bar3);
Serial.println(bar4);
delay(100);
}
