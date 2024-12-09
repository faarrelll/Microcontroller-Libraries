int iterasi=0;
 int get_keypad(){
  int data = 16;
  if (iterasi==0){col1_on;col2_off;col3_off;col4_off;}
  else if (iterasi==1){col1_off;col2_on;col3_off;col4_off;}
  else if (iterasi==2){col1_off;col2_off;col3_on;col4_off;}
  else if (iterasi==3){col1_off;col2_off;col3_off;col4_on;}
  
  if (iterasi==0){
    if(bar1){data=1;}
    else if(bar2){data=4;}
    else if(bar3){data=7;}
    else if(bar4){data=15;}
  }else  if (iterasi==1){
    if(bar1){data=2;}
    else if(bar2){data=5;}
    else if(bar3){data=8;}
    else if(bar4){data=0;}
  }else if (iterasi==2){
    if(bar1){data=3;}
    else if(bar2){data=6;}
    else if(bar3){data=9;}
    else if(bar4){data=14;}
  }else if (iterasi==3){
    if(bar1){data=10;}
    else if(bar2){data=11;}
    else if(bar3){data=12;}
    else if(bar4){data=13;}
  }
  iterasi++;
  if (iterasi>3){iterasi=0;}
  return data;
}
