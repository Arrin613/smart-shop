#include <SPI.h>
#include <MFRC522.h>
 #include <LiquidCrystal_I2C.h>
#include <Servo.h>
  Servo Serv;
  Servo Ser;

int pinIR=7;
int pinIR2=1;
  int pinServo=3;
  int pinServo2=2;
  int val=0;
  int valu=0;

LiquidCrystal_I2C lcd(0x3F,16,2); 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  
 int led=8;
  int red=6;
  int buzzer=5;
#define BUTTON_PIN 4

 int count = 0;
int count_prod = 0;
int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
double total = 0;

void setup() 
{
  Serv.attach(pinServo);
   Serv.attach(pinServo2);
  Serial.begin(9600); 
  lcd.init();
  lcd.clear();         
  lcd.backlight(); 
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Approximate your card to the reader...");
  Serial.println();
 pinMode(led, OUTPUT);
  pinMode(red, OUTPUT);
   pinMode(buzzer, OUTPUT);
 pinMode(BUTTON_PIN, INPUT_PULLUP);
 lcd.print("SMART CART"); // Start Printing
    delay(900);
  lcd.clear();
  lcd.print("PLZ SCAN ITEMS");
}


void loop() 
{
   val = digitalRead(pinIR);
    valu = digitalRead(pinIR2);

     if (val ==0){
      Serv.write(150);
      delay(1000);
    }
    else
    {
      Serv.write(10);
      delay(100);
    }
    if (valu ==0){
      Ser.write(150);
      delay(1000);
    }
    else
    {
      Ser.write(10);
      delay(100);
    }
    
  byte buttonState = digitalRead(BUTTON_PIN);
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
 
  if (content.substring(1) == "A3 3D 85 16" && buttonState == HIGH) 
  {
     lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Butter Added");
     lcd.setCursor(0, 1);
        lcd.print("Price(Rs):20.00");
          p1++;
    delay(1000);
 total = total+20.00;
 delay(100);
   lcd.clear();
  lcd.setCursor(3, 0);
  
 lcd.print(total);
 
  count_prod++;
     digitalWrite(led,HIGH);
     delay(500);
      digitalWrite(led,LOW);
  }

 else if (content.substring(1) == "A3 3D 85 16"&& buttonState == LOW) 
  {
    
   if(p1>0)
        {
          lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Butter Removed!!");
        
   
delay(1000);
     p1--;
    total = total-20.00;
     count_prod--;
     lcd.clear();
     delay(1000);
       lcd.clear();
      lcd.setCursor(3, 0);
     
    lcd.print(total);
    digitalWrite(red,HIGH);
     delay(500);
      digitalWrite(red,LOW);
    
  }
   else 
  {
      lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Not in cart!!!        ");
  digitalWrite(buzzer,HIGH);
     delay(1000);
      digitalWrite(buzzer,LOW);
      digitalWrite(red,HIGH);
     delay(1000);
      digitalWrite(red,LOW);
    
     
  }}
 if (content.substring(1) == "5A D2 3E 3F" && buttonState == HIGH) 
  {
     lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Bread Added");
     lcd.setCursor(0, 1);
        lcd.print("Price(Rs):30.00");
          p2++;
    delay(1000);
 total = total+30.00;
 delay(100);
   lcd.clear();
  lcd.setCursor(3, 0);
  
 lcd.print(total);
 
  count_prod++;
     digitalWrite(led,HIGH);
     delay(500);
      digitalWrite(led,LOW);
  }

 else if (content.substring(1) == "5A D2 3E 3F"&& buttonState == LOW)
  {
    
   if(p2>0)
        {
          lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Bread Removed!!");   
delay(1000);
     p2--;
    total = total-30.00;
     count_prod--;
     lcd.clear();
     delay(1000);
       lcd.clear();
      lcd.setCursor(3, 0);
     
    lcd.print(total);
    digitalWrite(red,HIGH);
     delay(500);
      digitalWrite(red,LOW);
    
  }
   else 
  {
      lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Not in cart!!!        ");
  digitalWrite(buzzer,HIGH);
     delay(1000);
      digitalWrite(buzzer,LOW);
      digitalWrite(red,HIGH);
     delay(1000);
      digitalWrite(red,LOW);    
  }}
  else if (content.substring(1) == "8C 13 2F 31")
      {
         lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Total Prod:");
        lcd.setCursor(11, 0);
        lcd.print(count_prod);
        lcd.setCursor(0, 1);
        lcd.print("Price:");
         digitalWrite(led,HIGH);
     delay(1000);
      digitalWrite(led,LOW);
      delay(100);
      digitalWrite(red,HIGH);
     delay(300);
      digitalWrite(red,LOW);
      delay(100);
      digitalWrite(buzzer,HIGH);
     delay(2000);
      digitalWrite(buzzer,LOW);
      digitalWrite(led,HIGH);
     delay(1000);
      digitalWrite(led,LOW);
        lcd.setCursor(6, 1);
        lcd.print(total);
        delay(1000);
        lcd.clear();        
        lcd.setCursor(0, 0);
        lcd.print("   Thank you        ");
        lcd.setCursor(0, 1);
        lcd.print("  for Shopping        ");
         
      }
      c1=p1*20.00;
    c2=p2*10.00;
    c3=p3*55.00;
    c4=p4*45.00;
      

}
 
