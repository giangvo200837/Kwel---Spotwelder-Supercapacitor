
//#define SSD1306_RST    PIN_C0

#include <18F252.h>
#device ADC=10
#fuses HS, NOLVP, NOBROWNOUT, PUT, NOWDT, NOPROTECT
#use delay(clock=20MHz)
#use I2C(MASTER, I2C1, FAST = 400000, STREAM = SSD1306)
#define Charg PIN_C0
#define Pulse PIN_B0
#define button PIN_B7
#define sw_welder PIN_B2
#define welder_read PIN_B1
#define SPK PIN_C2
#define DS0 PIN_B3
#define DS1 PIN_B4
#define ENC_A PIN_B5  // Chân A cua encoder
#define ENC_B PIN_B6  // Chân B cua encoder
#define AN0_TO_AN1   0b0100
#include <SSD1306.c>      // include SSD1306 driver source code
#include <GFX_Library.c>  // include graphics library source code
#DEFINE LUUTRUT1 5
#DEFINE LUUTRUT2 10
#DEFINE LUUTRUC1 15
#DEFINE LUUTRUD1 20
// define random max number
#define RAND_MAX  (display_width - 1)
// include std library source code (required by rand() function)
#include <stdlib.h>
//!void testdrawrect(void) {
//!  for (int16_t i=0; i<display_height/2; i+=2) {
//!    display_drawRect(i, i, display_width-2*i, display_height-2*i, WHITE);
//!    display();
//!    delay_ms(1);
//!  }
//!}
int1 start = 0, dem_1 = 0,chedo = 0;
unsigned int8 chrgt = 0, chon = 0, dem = 0, dem_sw = 0, set_delay = 2, i = 0, a = 0;
//unsigned int percent0=0,bef0=64,percent1=0,bef1=0;
//unsigned int16 vt=0;
unsigned int16 Vcell[2];
unsigned int8 checkblc = 240, time1 = 10, time2 = 30;
unsigned int8 percent[2] = {0,0};
unsigned int8 before[2] = {64,128};
unsigned int16 dem2 = 65500, vcellr = 0;
int1 lastState = 0;
int1 currentState;
float seconds;
void drawrect(void)
{
   
   display_drawRect(5, 1, 60, 20,WHITE);
   display_drawRect(3, 8, 3, 5,WHITE);
   display_drawRect(68, 1, 60, 20,WHITE);
   display_drawRect(66, 8, 3, 5,WHITE);  
}

void balancing()
{

      if(Vcell[0] > 2499) {chrgt = 1;}
      if(chrgt == 1)      
         {
            output_high(Charg);
            output_high(DS0);
            output_low(DS1);
           // delay_ms(500); 
            
            if(Vcell[0] < Vcell[1])
            {
            output_low(Charg);
            output_low(DS0);
           // output_low(DS1); 
           chrgt = 0;
            }
          }
      if((Vcell[1] > 2499) && (chrgt == 0 )) {chrgt = 2;}
      if(chrgt == 2)
      {
         output_high(Charg);
         output_high(DS1);
         output_low(DS0);
         delay_ms(500); 
         chrgt = 2;
         if(Vcell[1] < Vcell[0])
         {
         output_low(Charg);
         output_low(DS0);
         output_low(DS1); 
         chrgt = 0;
         }
       }
       checkblc = 0;
   //}

    
}


int8 read_rotary(int8 counter)
{
        currentState = input(ENC_A);
        if (currentState != lastState) { // Kiem tra thay doi trang thái
            if (currentState == 0) { // Kiem tra huong quay
                if (input(ENC_B) == 0) {
                    counter++; 
                } else if(chon != 3) {
                    counter--; if(counter <= 1) {counter = 1;}
                }
            }
           if(dem2 >= 7000)
           {
            if(chon == 1) 
            {             
            if(counter >= 30) counter = 30;
            display_FillRect(17,45,12,8,black);
            display();
            display_setCursor(17, 45);
            printf(display_print,"%02u",counter);           
            display();
            //delay_ms(1);
            }
            
            if(chon == 2) 
            {
            
            if(counter >= 50) counter = 50;
            display_FillRect(42,45,12,8,black); 
            display();
            display_setCursor(42, 45);
            printf(display_print,"%02u",counter);
            display();
            //delay_ms(1);
            }
            
            if(chon == 3)
            {
            
            if(counter > 1) counter = 0;
            display_FillRect(58,45,66,8,black);
            display();
            display_setCursor(70, 45);
            if(counter == 1)
            {           
            display_print("AUTO");                      
            }
            else display_print("MANUAL"); 
            display();
            }
            
            if(chon == 4)
            {
            if(counter >= 6) counter = 6;
            display_FillRect(100,45,24,8,black); 
            display();
            display_setCursor(100, 45);
            seconds = counter;
            printf(display_print,"%1.1fS",seconds*0.5);
            display();
            }
            dem2 = 0;
           }
        }       
        lastState = currentState;
        return counter;
}

void read_analog(int adc_r)
   {    
   set_adc_channel(adc_r); 
   delay_ms(1);
   vcellr = 0;
   for (int z = 0; z<20; z++)
   {  
   vcellr = vcellr + read_adc();
   delay_ms(1);
   }
   vcellr /= 20;
   Vcell[adc_r] = (float)(vcellr  * 5.0) / 1.023;  
   
  // Vcell[adc_r] = 1450; // test voltage
   //return;
   }
   
void percentages(int16 volt)
 {
 percent[a] = (-0.022*(float)volt) + (64*(a+1)-a);
 if(percent[a] < before[a])  
 { 
   
   
   for(i = 64*(a+1); i > percent[a]; i--)
   {
   display_drawLine(i,3,i,18,WHITE); 
  if(start == 0) {display();}
   }  
 }
 
  if(percent[a] > before[a])  
 {  
   for(i = before[a]; i < percent[a]; i++)
   {
   display_drawLine(i,2,i,19,BLACK);  
  // display();
   }
 }
 before[a]=percent[a];
 //volt1=100;
 }

   
void draw_monitor(void)
{   
   display_FillRect(0,26,127,64,black);
   display_setTextColor(WHITE);
   display_setTextSize(1);   
   display_setCursor(50, 32);
   display_print("mV         mV");
   display_setCursor(17, 45);
   printf(display_print,"%02u",time1);
   display_setCursor(42, 45);
   printf(display_print,"%02u",time2);
   display_setCursor(59, 56);
   display_print("mS"); 
   display_setCursor(70, 45);
   if(chedo == 0)  display_print("MANUAL");
   else {
   display_print("AUTO");
   seconds = set_delay;
   display_setCursor(100, 45);
   printf(display_print,"%1.1fS",seconds*0.5);
   }
   display_setCursor(90, 55);
   display_print("GIANGJ"); 
     //draw pulses    
   display_drawLine(1,63,20,63,WHITE);
   display_drawLine(20,63,20,55,WHITE);
   display_drawLine(20,55,23,55,WHITE);
   display_drawLine(23,55,23,63,WHITE);
   display_drawLine(23,63,43,63,WHITE);
   display_drawLine(43,63,43,55,WHITE);
   display_drawLine(43,55,50,55,WHITE);
   display_drawLine(50,63,50,55,WHITE);  
   display_drawLine(50,63,55,63,WHITE); 
   
   for(a = 0;a<2;a++)
      {  
         output_low(DS0);
         output_low(DS1);         
         read_analog(a); 
         if(chrgt == 1) output_high(DS0);        
         if(chrgt == 2) output_high(DS1); 
         Vcell[1] -= Vcell[0];         

         percentages(Vcell[a]);
         
         display_setTextSize(2);

         if(a == 0) display_setCursor(1, 26);
         if(a == 1) display_setCursor(68, 26); 
         printf(display_print,"%04lu",Vcell[a]);
         
//!         if((Vcell[0] == 0) && (Vcell[1] == 0)) 
//!         {
//!         
//!         display_FillRect(1,26,127,42,black);
//!         display_setCursor(19, 26);
//!         display_print("---  ---");
//!         }         
      }
      display();
      if((Vcell[0] > 2600) || (Vcell[1] > 2600))
      {
      Vcell[0] = Vcell[1] = 0; drawrect();
      }     
      start = 1;     

}
void spotwelder_setup(void)
{        
         
         if(input(button)){
           while(input(button)){}//restart_wdt();delay_ms(200);}
           chon+=1;dem_1=1;
           if(chedo == 0) {if(chon > 3) chon = 5;}
           output_high(SPK);delay_ms(100);
           output_low(SPK);          
           if(chon <= 4)
           {
           display_FillRect(5,45,12,8,black); 
           display_FillRect(30,45,12,8,black); 
           display_FillRect(58,45,12,8,black);
           if(chedo == 1) {display_setCursor(100, 45);printf(display_print,"%1.1fS",seconds*0.5);}
           display();
           delay_ms(300);//restart_wdt();
           }          
           
           if (chon > 4) 
           {
           write_eeprom(LUUTRUT1,time1);
           write_eeprom(LUUTRUT2,time2);
           write_eeprom(LUUTRUC1,chedo);
           write_eeprom(LUUTRUD1,set_delay);
           display_FillRect(0,26,127,64,WHITE);
           display_setTextColor(BLACK);
           display_setTextSize(2); 
           display_setCursor(40, 40);
           display_print("SAVED");
           display();delay_ms(1000);//restart_wdt();
           output_low(Charg);
           chon = 0; dem = 0; dem2 = 65500; break;  
          // reset_cpu();
           //break;//break;
            //break;
           }
         }
    if(chon == 1) { 
      time1 = read_rotary(time1);
    //  display_setTextSize(1);
    if(dem_1 == 1)
    {
      display_setCursor(5, 45);
      display_print(">>"); 
      display();
      dem_1 = 0;
    }
//!      display_setCursor(5, 45);
//!      display_print("  "); 
//!      display();
     // delay_ms(300);
    }
    if(chon == 2) {   
      time2 = read_rotary(time2); 
      //display_setTextSize(1); 
      if(dem_1 == 1)
    {
      display_setCursor(30, 45);
      display_print(">>"); 
      display();  
      dem_1 = 0;
    }
//!      display_setCursor(30, 45);
//!      display_print("  "); 
//!      display();
      //delay_ms(300);
    }
    if(chon == 3) { 
     // read_rotary();   
     chedo = read_rotary(chedo); 
      //display_setTextSize(1); 
      if(dem_1 == 1)
      {
      display_setCursor(58, 45);
      display_print(">>"); 
      display();
      dem_1 = 0;
      }
    }
    if(chon == 4) { 
     // read_rotary();   
     set_delay = read_rotary(set_delay); 
      //display_setTextSize(1); 
      if(dem_1 == 1)
      {
      display_setCursor(93, 45);
      display_print(">"); 
      display();
      dem_1 = 0;
      }
//!      display_setCursor(68, 45);
//!      display_print("  "); 
//!      display();
     // delay_ms(300);
    }
   // restart_wdt();
    dem2+=1;if(dem2 > 7000) dem2 = 7000;
    //delay_us(10);
}

void spotwelder_start(int8 pulse1, pulse2)
   {  
      //setup_wdt(WDT_ON);
      //pulse_interval = pules1; if(pulse_interval >= 10) pulse_interval = 10;
      output_high(SPK);
      output_high(Pulse);delay_ms(pulse1);
      if(pulse1 > 10) pulse1 = 10;         //interval  
      output_low(Pulse);delay_ms(pulse1); //interval
      //restart_wdt(); 
      output_high(Pulse);delay_ms(pulse2);
      output_low(Pulse);delay_ms(10);
      //restart_wdt(); 
      output_low(SPK); //delay_ms(100);
//!      for(int z = 0; z < 5; z++)
//!      {
//!      delay_ms(100); 
//!      restart_wdt(); 
//!      }
      output_low(Pulse); //for sure
     // break;
     // restart_wdt(); 
     // setup_wdt(WDT_OFF);
   }


void main(void)
{
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  // initialize with the I2C addr 0x7A (for the 128x64)
  // SSD1306 OLED display I2C address may be 0x7A or 0x78
 
  SET_TRIS_A(0B00000011);
  SET_TRIS_B(0b11100110);
  SET_TRIS_C(0b11000);
  output_low(Pulse);
  output_low(Charg);
  output_low(SPK);
  output_low(DS0);
  output_low(DS1);
  lastState = input(ENC_A);
//!  output_low(Pulseex);
//!  for(int h = 0; h<5; h++)
//!  {
//!  output_high(Pulseex);delay_ms(1000);
//!  output_low(Pulseex);delay_ms(1000);
//!  }
  setup_adc(ADC_CLOCK_DIV_8); 
  SETUP_ADC_PORTS(AN0_TO_AN1);
 // setup_wdt(WDT_2304MS);
  // setup_wdt(WDT_OFF);
 // restart_wdt();
  //setup_wdt(WDT_288MS);
  //SSD1306_begin(SSD1306_SWITCHCAPVCC, 0x7A); // test code
  SSD1306_begin(SSD1306_SWITCHCAPVCC, 0x78); // load code
  
  time1 = read_eeprom(LUUTRUT1); if(time1 >  99) {time1 = 3; write_eeprom(LUUTRUT1,time1);}
  time2 = read_eeprom(LUUTRUT2); if(time2 >  99) {time2 = 5;write_eeprom(LUUTRUT2,time2);} 
  chedo = read_eeprom(LUUTRUC1); if(chedo >  1) {chedo = 0;write_eeprom(LUUTRUC1,chedo);}
  set_delay = read_eeprom(LUUTRUD1); if(set_delay >  6) {set_delay = 2;write_eeprom(LUUTRUD1,set_delay);}
   //display_clear();
//!   display();
//!   delay_ms(1000);
   ssd1306_command(SSD1306_SETCONTRAST);
   ssd1306_command(0xB9);
//!   display_FillRect(0,0,127,63,white);
//!   display_setTextColor(Black);
//!   display_setTextSize(3); 
//!   display_setCursor(2, 25);
//!   display_print("GIANG J");
   //display_FillRect(0,0,127,63,black);
   display();
  // restart_wdt();
   output_high(SPK); delay_ms(500);
   output_low(SPK);
   delay_ms(2000);
   //restart_wdt();
   display_clear();
   drawrect();
  //output_high(Charg);
  // init done
  while(true)
  {  

  if(dem2 >= 65500)
  {
    draw_monitor();
    //display();
    checkblc+=1; if (checkblc > 10) {checkblc = 10;}
     dem2=0;
  }
  

  
if((Vcell[0] > 1000) && (Vcell[1] > 1000) && (time1 <= 30) && (time2 <= 50))
{
 if(dem == 0)
   { 
   //do spotwelder
   if(chedo == 0)
   {
      if(input(sw_welder)){ 
      while(true){spotwelder_start(time1, time2);dem2=65500;break;}
      delay_ms(500);
      }
      else {}
   }
   if(chedo == 1)
   {        
      if(input(welder_read)) {while(input(welder_read)){delay_ms(100);dem_sw+=1;if(dem_sw >= set_delay*5){break;}}}//restart_wdt();delay_ms(1000);restart_wdt();delay_ms(1000);restart_wdt();}   
      if(dem_sw < set_delay*5) {dem_sw = 0;}
      if(dem_sw >= set_delay*5)
      {
      if(input(welder_read)) {           
      while(true){spotwelder_start(time1, time2);dem2=65500;break;}      
      }
     // else dem_sw= 0; break;
      }      
   }
   }
   //restart_wdt();
}

if(checkblc >= 10) {balancing();}

 while(dem != 0)
   {
   // do setup spotwelder
   //draw_monitor();
   //display();
    chrgt = 0;
    output_high(Charg);
    output_low(DS0);
    output_low(DS1); 
    output_low(Pulse); 
   display_setTextSize(1);
   spotwelder_setup();
  // restart_wdt();
   }
  
     if(input(button))
      { 
         delay_ms(500);//restart_wdt();
       //  if(input(button)) chon =  dem = 1;      
         if(input(button)){
         dem_1 = chon =  dem = 1;
         //chrgt = 0;
         //output_low(Pulse);
        // output_highCharg);
         output_high(SPK);
         delay_ms(100);
         output_low(SPK);
         }
         while(input(button)){delay_ms(100);}//restart_wdt();
         //restart_wdt();
        // else dem = 0;
         //delay_ms(500);
         //if(input(button)) dem = 1;
         //SSD1306_ClearDisplay();
      }
      

  //dem+=1; delay_ms(100);
dem_sw = 0;
dem2++;//restart_wdt();
}
}


