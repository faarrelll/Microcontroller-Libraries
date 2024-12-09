void activation_sms(){
  String header=sms_text.substring(0,1);
  String data[4];
  
  if (header=="1"||header=="0"){
  data[0]=sms_text.substring(0,1);
  data[1]=sms_text.substring(1,2);
  data[2]=sms_text.substring(2,3);
  data[3]=sms_text.substring(3,4);
  for (int a=0;a<4;a++){
    if (data[a]=="1"){
      digitalWrite(pin[a],HIGH);
      EEPROM.write(a+1,1);
    }else if (data[a]=="0"){
      digitalWrite(pin[a],LOW);
      EEPROM.write(a+1,0);
    }
  }
  String protokol= "AKTIVASI SUKSES K1:"+String(data[0])+" K2:"+String(data[1])+" K3:"+String(data[2])+" K4:"+String(data[3]);  
  protokol.toCharArray(sms_text1, protokol.length()+1);
  cek_panel(phone_number,sms_text1);
   
  }else{
  if (sms_text == "beban1=on" || sms_text == "BEBAN1=ON")
  {
    digitalWrite(kontaktor1, HIGH);
    Serial.println("kontaktor1=ON");
    EEPROM.write(adrk1,1);
    cek_panel(phone_number,"AKTIVASI SUKSES K1=ON");
  }
  else if (sms_text == "beban1=off" || sms_text == "BEBAN1=OFF")
  {
    digitalWrite(kontaktor1, LOW);
    Serial.println("kontaktor1=OFF");
   EEPROM.write(adrk1,0);
   cek_panel(phone_number,"AKTIVASI SUKSES K1=OFF");
    
  }

  
  else if (sms_text == "beban2=on" || sms_text == "BEBAN2=ON")
  {
    digitalWrite(kontaktor2, HIGH);
    Serial.println("kontaktor2=ON");
    EEPROM.write(adrk2,1);
    cek_panel(phone_number,"AKTIVASI SUKSES K2=ON");
  }
  else if (sms_text == "beban2=off" || sms_text == "BEBAN2=OFF")
  {
    digitalWrite(kontaktor2, LOW);
    Serial.println("kontaktor2=OFF");
   EEPROM.write(adrk2,0);
   cek_panel(phone_number,"AKTIVASI SUKSES K2=OFF");
  }


   else if (sms_text == "beban3=on" || sms_text == "BEBAN3=ON")
  {
    digitalWrite(kontaktor3, HIGH);
    Serial.println("kontaktor3=ON");
    EEPROM.write(adrk3,1);
    cek_panel(phone_number,"AKTIVASI SUKSES K3=ON");
  }
  else if (sms_text == "beban3=off" || sms_text == "BEBAN3=OFF")
  {
    digitalWrite(kontaktor3, LOW);
    Serial.println("kontaktor3=OFF");
   EEPROM.write(adrk3,0);
   cek_panel(phone_number,"AKTIVASI SUKSES K3=OFF");
  }

   else if (sms_text == "beban4=on" || sms_text == "BEBAN4=ON")
  {
    digitalWrite(kontaktor4, HIGH);
    Serial.println("kontaktor4=ON");
    EEPROM.write(adrk4,1);
    cek_panel(phone_number,"AKTIVASI SUKSES K4=ON");
  }
  else if (sms_text == "beban4=off" || sms_text == "BEBAN4=OFF")
  {
    digitalWrite(kontaktor4, LOW);
    Serial.println("kontaktor4=OFF");
   EEPROM.write(adrk4,0);
   cek_panel(phone_number,"AKTIVASI SUKSES K4=OFF");
  }
   
  else if (sms_text == "cek" || sms_text == "CEK" || sms_text == "Cek")
  {
    checkcondition();
    String kondisi_panel;
    kondisi_panel = "AC1=" + String(volt[1]) + " AC2=" + String(volt[2]) + " AC3="+String(volt[3]) +
    " AC4="+String(volt[4]) + " AC5="+String(volt[5])+ " AC6="+String(volt[6]) + " AC7="+String(volt[7]) + " AC8="+String(volt[8])+
    " AC9="+String(volt[9]); 
    kondisi_panel.toCharArray(sms_text1, kondisi_panel.length()+1);
   cek_panel(phone_number,sms_text1);
  

  }
  else
  {
    Serial.println("FORMAT SMS ANDA SALAH !!!");
    cek_panel(phone_number,"FORMAT ANDA SALAH !!!!");
   
  }
  
  }
}

void sendsms(char* txt_message)
{
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Send SMS OFF...");
 lcd.setCursor(0,1);
 lcd.print(txt_message);
  for (int i=0;i<jumlahnomor;i++)
  {

  sms.SendSMS(myphone[i],txt_message );
 
  Serial.print(myphone[i]);
  Serial.print(txt_message);
  Serial.println();
  delay(2000);
  }
} 

void cek_panel(char* nomor,char* smscek)
{
 lcd.clear();
 lcd.print ("SMS SEND....!!!!");
 sms.SendSMS(nomor,smscek );
 Serial.println("KOndisi");
 Serial.println(smscek);
 Serial.println(nomor);
 
}


void checkcondition()
{
  for (int x=1;x<=10;x++){
    if (volt[x]==false && sudah_sms[x]==false){
      bep(1);
      String protokol= "PANEL "+ nama_panel[x-1]+" MATI";
      protokol.toCharArray(sms_text1,protokol.length()+1);
      sendsms(sms_text1);
      sudah_sms[x]=1;
    } else if (volt[x]==true && sudah_sms[x]==true){
      sudah_sms[x]=false;
      bep(1);
      
    }

    
  }

}

