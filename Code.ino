#include <DS3231.h>
#include <EEPROM.h>
int addr = 0;
#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

DS3231  rtc(SDA, SCL);

Time  t;


#define buz 10

int Hor;

int Min;

int Sec;
#include <SoftwareSerial.h> 
//SoftwareSerial MyBlue(2, 3); // RX | TX 
String flag; 
String mp1,mp2,ep1,ep2,d1,r;
int mahr,mamin,evahr,evamin,d;
int omahr,omamin,oevahr,oevamin,od;


void setup()

{
  
  pinMode(12,OUTPUT);
  
  Wire.begin();

  rtc.begin();

  Serial.begin(9600);

  pinMode(buz, OUTPUT);
  digitalWrite(buz, HIGH);

  lcd.begin();

  lcd.setCursor(0, 0);

  lcd.print("Technicalhub.io");

  lcd.setCursor(0, 1);

  lcd.print(" College bell ");

  // The following lines can be uncommented to set the date and time

  //rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY

  //rtc.setTime(10, 31, 59);     // Set the time to 12:00:00 (24hr format)

// rtc.setDate(23, 12, 2019);   // Set the date to January 1st, 2014

  delay(2000);
   lcd.clear();

}

int i=0;

void loop()

{
  digitalWrite(buz, HIGH);

  t = rtc.getTime();

  Hor = t.hour;

  Min = t.min;

  Sec = t.sec;

  if (Serial.available() > 0) 
 {
  lcd.clear();
      flag = Serial.readString();      
    mp1 = flag.substring(0,2);
    mp2 = flag.substring(2,4);
    ep1 = flag.substring(4,6);
    ep2 = flag.substring(6,8);
    d1 = flag.substring(8,10);
    r=flag.substring(10,12);
 //Serial.println(flag);
  mahr=mp1.toInt();
 
 mamin=mp2.toInt();
 evahr=ep1.toInt();
 evamin=ep2.toInt();
 d=d1.toInt();
 if(mahr || mamin >0)
 {
 EEPROM.write(addr, mahr);
 EEPROM.write(addr+2, mamin);
 EEPROM.write(addr+4, evahr);
 EEPROM.write(addr+6, evamin);
 EEPROM.write(addr+8, d);
 }

 }

 
/*
  Serial.print(mahr);
  Serial.print(":");
 Serial.print(mamin);
   Serial.print(" ");
 Serial.print(evahr);
   Serial.print(":");
 Serial.println(evamin);
 */
 flag="";
 

  lcd.setCursor(0, 0);

  lcd.print("Time:   ");

  lcd.print(rtc.getTimeStr());

  lcd.setCursor(0, 1);



  lcd.print(EEPROM.read(0));
  lcd.print(":");
  lcd.print(EEPROM.read(2));
  lcd.print("      ");
  lcd.print(EEPROM.read(4));
  lcd.print(":");
  lcd.print(EEPROM.read(6));




  if ( (Hor == EEPROM.read(0) &&  Min == EEPROM.read(2) && Sec==0)) //Comparing the current time with the Alarm time

  {
    while (i <= EEPROM.read(8))
    {
    Buzzer();

    lcd.clear();

    lcd.print("Alarm ON  ");
    lcd.print(i);

    lcd.setCursor(0, 1);

    lcd.print("Alarming");
    i++;
    lcd.setBacklight(HIGH);
    delay(200);
    lcd.setBacklight(LOW);
    delay(200);
    }
  i=0;
  lcd.setBacklight(HIGH);
  digitalWrite(buz, HIGH);
  }
  if ( Hor == EEPROM.read(4) &&  Min == EEPROM.read(6)&& Sec==0) //Comparing the current time with the Alarm time

  {
    Buzzer();

    lcd.clear();

    lcd.print("Alarm ON");

    lcd.setCursor(0, 1);

    lcd.print("Alarming");

while (i <= EEPROM.read(8))
    {
    Buzzer();

    lcd.clear();

    lcd.print("Alarm ON  ");
    lcd.print(i);

    lcd.setCursor(0, 1);

    lcd.print("Alarming");
    i++;
    lcd.setBacklight(HIGH);
    delay(200);
    lcd.setBacklight(LOW);
    delay(200);
    }
   
  i=0;
  lcd.setBacklight(HIGH);
  digitalWrite(buz, HIGH);

  delay(1000);

}
}




void Buzzer()

{

  digitalWrite(buz, LOW);
   delay(1000);
 

}  
