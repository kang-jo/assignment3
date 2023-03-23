//Devan Al Fauzi
#include <EEPROM.h>  

#define aPin 2  //        
#define bPin 3  //      _____
#define cPin 4  //     |  A  |
#define dPin 5  //   F |_____| B
#define ePin 6  //     |  G  |
#define fPin 7  //   E |_____| C
#define gPin 8  //        D     
#define dotPin 13

#define c1Pin 9  
#define c2Pin 10 
#define c3Pin 11 
#define c4Pin 12 

int Common = 1;   
int Set_mode = 1; 

#define bt_set  A0
#define bt_up   A1
#define bt_down A2

#define buzzerPin A5

int hh=0, mm=0, ss=0;
word MilliSecond = 0; 
bool timerStart = false, play = true;

int flag1=0, timer=0, Set=0, Mode=1;

int On, Off, Off_C; 
int DTime = 4; 

void setup(){ 

 pinMode(bt_set, INPUT_PULLUP); 
 pinMode(bt_up,    INPUT_PULLUP);
 pinMode(bt_down,  INPUT_PULLUP);

 pinMode(aPin, OUTPUT);
 pinMode(bPin, OUTPUT);
 pinMode(cPin, OUTPUT);
 pinMode(dPin, OUTPUT);
 pinMode(ePin, OUTPUT); 
 pinMode(fPin, OUTPUT);
 pinMode(gPin, OUTPUT);
 pinMode(dotPin, OUTPUT);

 pinMode(c1Pin, OUTPUT);
 pinMode(c2Pin, OUTPUT);
 pinMode(c3Pin, OUTPUT);
 pinMode(c4Pin, OUTPUT);

 if(Common==1){On=0, Off=1, Off_C=0;} 
          else{On=1, Off=0, Off_C=1;} 

 // Indicate that system is ready
 for (int i = 9; i >=0; i--) {
 showNumber(i);
 digitalWrite(c1Pin, Common);
 digitalWrite(c2Pin, Common);
 digitalWrite(c3Pin, Common);
 digitalWrite(c4Pin, Common);
 delay(1000); 
 } 

 noInterrupts();         
 TCCR1A = 0;             
 TCCR1B = 0;             
 TCNT1  = 0;             
 OCR1A = 1999;           
 TCCR1B |= (1 << WGM12); 
 TCCR1B |= (1 << CS11);  
 TIMSK1 |= (1 << OCIE1A);
 interrupts();           

read_eeprom();
}

void loop(){  

if(digitalRead (bt_set) == 0){ 
if(flag1==0 && Mode==1){ flag1=1; timer = 30;
tone(A5, 800, 50); 
Set = Set+1;
if(Set>2){Set=0;} 
read_eeprom(); 
 }
}else{flag1=0;}

if(digitalRead (bt_up) == 0 && timer==0){ timer = 20;
tone(A5, 800, 50);
if(Set==0){Mode = !Mode;
if(hh>0 || mm>0){
if(Mode==0){timerStart = true;}
}else{Mode=1;}

if(Mode==1){timerStart = false;}
}

if(Set==1){mm = mm+1;
  if(mm>59)mm=0;
EEPROM.write(11, mm);
}

if(Set==2){hh = hh+1;
  if(hh>99)hh=0;
EEPROM.write(12, hh);
}
}

if(digitalRead (bt_down) == 0 && timer==0){ timer = 20;
tone(A5, 800, 50);
if(Set==0){read_eeprom(); timerStart = true; Mode=0;}

if(Set==1){mm = mm-1;
if(mm<0)mm=59;
EEPROM.write(11, mm);
}

if(Set==2){hh = hh-1;
if(hh<0)hh=99;
EEPROM.write(12, hh);
}

}

if(hh==0 && mm==0 && Mode==0){Mode=1; timerStart = false;
timer = 50;
if (play == true) {
    makeBeep(0, 1, 1000); 
    makeBeep(2, 1, 1000);
    makeBeep(2, 1, 1000);
    makeBeep(2, 1, 1000);
    makeBeep(2, 1, 1000);
    makeBeep(6, 1, 1000); 
    makeBeep(2, 1, 1000);
    makeBeep(2, 1, 1000);
    makeBeep(2, 1, 1000);
    makeBeep(2, 1, 1000);
    makeBeep(6, 1, 1000); 
    makeBeep(2, 1, 1000);
    makeBeep(2, 2000, 1000);
}
play = false;

}  

if(Set==1){all_off();}
else{showNumber((hh/10)%10);}
digitalWrite(c1Pin, Common);
delay(DTime);
digitalWrite(c1Pin, Off_C);

if(Set==1){all_off();}
else{showNumber(hh%10);}
digitalWrite(c2Pin, Common);
delay(DTime);
digitalWrite(c2Pin, Off_C);

if(Set==2){all_off();}
else{showNumber((mm/10)%10);
if(MilliSecond<500 && Mode==0){digitalWrite( dotPin, Off);}
else{digitalWrite( dotPin, On);}
}
digitalWrite(c3Pin, Common);
delay(DTime);
digitalWrite(c3Pin, Off_C);

if(Set==2){all_off();}
else{showNumber(mm%10); }
digitalWrite(c4Pin, Common);
delay(DTime);
digitalWrite(c4Pin, Off_C);
digitalWrite( dotPin, Off);

if(timer>0){timer=timer-1;}
}

void makeBeep(int intervalSeconds, int howlongSeconds, int freq) {
  delay(intervalSeconds * 100);
  tone(buzzerPin, freq, howlongSeconds * 100);
}

void read_eeprom(){
mm = EEPROM.read(11);
hh = EEPROM.read(12); 
}

void showNumber(int x){
  
   switch(x){
     case 1: one();   break;
     case 2: two();   break;
     case 3: three(); break;
     case 4: four();  break;
     case 5: five();  break;
     case 6: six();   break;
     case 7: seven(); break;
     case 8: eight(); break;
     case 9: nine();  break;
     default: zero(); break;
   }
}

void all_off(){
  digitalWrite( aPin, Off); //      
  digitalWrite( bPin, Off); //      
  digitalWrite( cPin, Off); //      
  digitalWrite( dPin, Off); //      
  digitalWrite( ePin, Off); //      
  digitalWrite( fPin, Off);
  digitalWrite( gPin, Off);
  digitalWrite( dotPin, Off);
}

void one(){
  digitalWrite( aPin, Off); //      
  digitalWrite( bPin, On);  //      |
  digitalWrite( cPin, On);  //      |
  digitalWrite( dPin, Off); //      |
  digitalWrite( ePin, Off); //      |
  digitalWrite( fPin, Off);
  digitalWrite( gPin, Off);
}

void two(){
  digitalWrite( aPin, On);  //  ____
  digitalWrite( bPin, On);  //      | 
  digitalWrite( cPin, Off); //  ____|
  digitalWrite( dPin, On);  // |     
  digitalWrite( ePin, On);  // |____
  digitalWrite( fPin, Off);
  digitalWrite( gPin, On);
}

void three(){
  digitalWrite( aPin, On);  //  ____
  digitalWrite( bPin, On);  //      |
  digitalWrite( cPin, On);  //  ____|
  digitalWrite( dPin, On);  //      |
  digitalWrite( ePin, Off); //  ____|
  digitalWrite( fPin, Off); 
  digitalWrite( gPin, On);
}

void four(){
  digitalWrite( aPin, Off); //  
  digitalWrite( bPin, On);  // |    |
  digitalWrite( cPin, On);  // |____|
  digitalWrite( dPin, Off); //      |
  digitalWrite( ePin, Off); //      |
  digitalWrite( fPin, On);
  digitalWrite( gPin, On);
}

void five(){
  digitalWrite( aPin, On);  //  ____
  digitalWrite( bPin, Off); // |
  digitalWrite( cPin, On);  // |____
  digitalWrite( dPin, On);  //      |
  digitalWrite( ePin, Off); //  ____|
  digitalWrite( fPin, On);  
  digitalWrite( gPin, On);
}

void six(){
  digitalWrite( aPin, On);  //  ____
  digitalWrite( bPin, Off); // |
  digitalWrite( cPin, On);  // |____
  digitalWrite( dPin, On);  // |    |
  digitalWrite( ePin, On);  // |____|
  digitalWrite( fPin, On);
  digitalWrite( gPin, On);
}

void seven(){
  digitalWrite( aPin, On);  //  ____
  digitalWrite( bPin, On);  //      |
  digitalWrite( cPin, On);  //      |
  digitalWrite( dPin, Off); //      |
  digitalWrite( ePin, Off); //      |
  digitalWrite( fPin, Off);
  digitalWrite( gPin, Off);
}

void eight(){
  digitalWrite( aPin, On); //  ____
  digitalWrite( bPin, On); // |    |
  digitalWrite( cPin, On); // |____|
  digitalWrite( dPin, On); // |    |
  digitalWrite( ePin, On); // |____|
  digitalWrite( fPin, On); 
  digitalWrite( gPin, On); 
}

void nine(){
  digitalWrite( aPin, On);  //  ____
  digitalWrite( bPin, On);  // |    |
  digitalWrite( cPin, On);  // |____|
  digitalWrite( dPin, On);  //      |
  digitalWrite( ePin, Off); //  ____|
  digitalWrite( fPin, On); 
  digitalWrite( gPin, On);
}

void zero(){                 
  digitalWrite( aPin, On); //  ____
  digitalWrite( bPin, On); // |    |
  digitalWrite( cPin, On); // |    |
  digitalWrite( dPin, On); // |    |
  digitalWrite( ePin, On); // |____|
  digitalWrite( fPin, On); 
  digitalWrite( gPin, Off);   
}


ISR(TIMER1_COMPA_vect){   
if(timerStart == true){MilliSecond++;
    if(MilliSecond >= 1000){MilliSecond = 0;
       if(Set_mode==0){ss--;
       if(ss<0){ss=59; mm--;}
       }else{mm--;}
       if(mm<0){mm=59; hh--;}
    }
  }  
}
