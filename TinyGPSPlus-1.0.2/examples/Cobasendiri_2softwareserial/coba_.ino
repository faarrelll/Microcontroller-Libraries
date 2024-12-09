void proses(String datax){
    int a =datax.indexOf( "$GPRMC"); //jika ada 0
    if (a>=0){
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
