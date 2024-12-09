void read_sensor(){
tegangan[0]= analogRead(A7);
tegangan[1]= analogRead(A8);
tegangan[2]= analogRead(A9);
tegangan[3]= analogRead(A10);
tegangan[4]= analogRead(A11);
tegangan[5]= analogRead(A12);
tegangan[6]= analogRead(A13);
tegangan[7]= analogRead(A14);
tegangan[8]= analogRead(A15);


Serial.println("");
Serial.println(String(tegangan[0])+" "+String(tegangan[1])+" "+String(tegangan[2])+" "+
String(tegangan[3])+" "+String(tegangan[4])+" "+String(tegangan[5])+" "+
String(tegangan[6])+" "+String(tegangan[7])+" "+String(tegangan[8])+" ");

for (int count=1;count<=9;count++){
  volt[count]=kondisi(tegangan[count-1]);
  Serial.print(volt[count]);
}
 Serial.println("");
}

