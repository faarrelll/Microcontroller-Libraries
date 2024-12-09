bool kondisi(int adc){
bool kon;
if (adc>650){
  kon=false;
}else{
  kon=true;
}
return kon;

}

void read_con(){
for (int a=0;a<4;a++){
  int x=EEPROM.read(a+1);
  
  if (x==1&&a==0){
    digitalWrite(kontaktor1,HIGH);
  } else if (x==0 &&a==0){
    digitalWrite(kontaktor1,LOW);
  }

 if (x==1&&a==1){
    digitalWrite(kontaktor2,HIGH);
  } else if (x==0 &&a==1){
    digitalWrite(kontaktor2,LOW);
  }

   if (x==1&&a==2){
    digitalWrite(kontaktor3,HIGH);
  } else if (x==0 &&a==2){
    digitalWrite(kontaktor3,LOW);
  }

   if (x==1&&a==3){
    digitalWrite(kontaktor4,HIGH);
  } else if (x==0 &&a==3){
    digitalWrite(kontaktor4,LOW);
  }
  
  Serial.println(String(pin[a])+" "+String(x));
}
  delay(1000);
}


void bep( int x){
  for (int i=0;i<x;i++)
  {
  digitalWrite(buzzer,HIGH);
  delay(200);
   digitalWrite(buzzer,LOW);
  delay(200);
  }
  
}

