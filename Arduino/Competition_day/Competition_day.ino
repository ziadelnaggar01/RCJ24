#include "functions.h"

void loop() 
{
while ( reason=='N' )
 {
  ultra();
  color();
  if (digitalRead(start)==0)
  {
  reason='S';
  }
  else if ((digitalRead(rRH)==1)||(digitalRead(rYS)==1))
  {
  if ((millis()- R_Time)>2000)
   {
    ultra();
    if(R_Distance<15){reason='C';}
   }
  }else if ((digitalRead(lRH)==1)||(digitalRead(lYS)==1))
  {
    if ((millis()- R_Time)>2000)
   {
    ultra();
    if(L_Distance<15){reason='C';}
   }
  }
  else if (C_Distance<5)
   {
    reason='U';
   }
   else if (R_Distance<5)
   {
    Move(-70,70,50);
   }
   else if (L_Distance<5)
   {
    Move(70,-70,50);
   }
  else if (Detected_Color=='B')
   {
  reason='B';
   }
  else if (Detected_Color=='A')
   {
  reason='A';
   } 
  else
   {
  Move(70,67,1);
   }
 }
Reason();
}

void Reason()
{
     if(reason=='U')
      { 
        Move(70,70,700);
        ultra();
        Move(-70,-70,500);
       if(R_Distance>30)
        {  
         turn(90);
        }
  else
        {
         turn(-90);
        }    
      }
  else if(reason=='B'){Move(-100,-100,950); ultra();if(R_Distance>30){ turn(90);}else if(L_Distance>30){turn(-90);}else{turn(183);}}
  else if(reason=='A'){Move(100,100,100); color(); if(Detected_Color=='A'){ Move(100,100,900); Move(0,0,5000); Move(100,100,12000);}}//must move& wait be 5 secs
  else if(reason=='C')
    {
      if (digitalRead(rRH)==1){deploy('r',2);}
 else if (digitalRead(lRH)==1){deploy('l',2);}
 else if (digitalRead(rYS)==1){deploy('r',1);} 
 else if (digitalRead(lYS)==1){deploy('l',1);}
    }
 else if(reason=='S'){Move(0,0,500);while(digitalRead(start)==1){Move(0,0,1);}delay(500);}   
 reason='N';
 C_Time=millis();
}
