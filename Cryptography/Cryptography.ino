@Author: SIDDHANT ANGOLKAR
#include <LiquidCrystal.h>
#include<SoftwareSerial.h>
#include<String.h>
LiquidCrystal lcd(3, 6, 8, 9, 10, 11); /// REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN
int inPin = 7;   // pushbutton
int val = 0;    //variable for reading the pin status
int RX_pin=4;
int TX_pin=2;
SoftwareSerial BTserial(RX_pin,TX_pin);
String BT_data;
String Arduino_data;
char ch;
int i,key=3;
void setup()
{
  Serial.begin(9600);
  BTserial.begin(9600); 
  pinMode(inPin, INPUT);
  lcd.begin(16, 2);
}
void loop()
{
  if(BTserial.available())
  {
    BT_data=BTserial.readString();
    for(i = 0; BT_data[i] != '\0'; ++i)
    {
      ch = BT_data[i];
      if(ch >= 'a' && ch <= 'z')
      {
      ch = ch + key;
      if(ch > 'z')
      {
        ch = ch - 'z' + 'a' - 1;
      }
        BT_data[i] = ch;
        }
    else if(ch >= 'A' && ch <= 'Z'){
    ch = ch + key;
    if(ch > 'Z'){
    ch = ch - 'Z' + 'A' - 1;
    }
    BT_data[i] = ch;
    }
    }
    Serial.println(BT_data);
    
    }
  val = digitalRead(inPin);  // read input value
  if (val == LOW) { 
    for(i = 0; BT_data[i] != '\0'; ++i){
    ch = BT_data[i];
    if(ch >= 'a' && ch <= 'z'){
    ch = ch - key;
    if(ch < 'a'){
    ch = ch + 'z' - 'a' + 1;
    }
    BT_data[i] = ch;
    }
    else if(ch >= 'A' && ch <= 'Z'){
    ch = ch - key;
    if(ch < 'A'){
    ch = ch + 'Z' - 'A' + 1;
    }
    BT_data[i] = ch;
    }
    }
    Serial.println(BT_data);
}
lcd.print(BT_data);
lcd.setCursor(0, 1); 
lcd.print(BT_data);
delay(170);
lcd.scrollDisplayLeft();
lcd.setCursor(0, 0);
}
