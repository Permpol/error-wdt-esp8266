//#include <SimpleTimer.h>
#include <TridentTD_LineNotify.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
int sensorValue = 0;  //ตัวแปรค่า Analog
int outputValue = 0;   // ตัวแปรสำหรับ Map เพื่อคิด %
const int analogInPin = A0;
char auth[] = " 5P9n_RZO42xfyhVN58c9mPlogQyRRSEc";
char ssid[] = "iPhone";
char pass[] = "12345678";
int led = 4;
int t_slider = 0;
int buton = 0;
int one = 5;
int manul = 0;
char sever[] = "oasiskit.com";
int port = 8080;
bool lock1 = false; // ล็อกคําสั่งปั๊มนํ้าทํางาน
bool lock2 = false;// ล็อกคําสั่งปั๊มนํ้าหยุดทํางาน
bool lock3 = false;// ล็อกคําสั่งtimer
bool lock4 = false;// ล็อกคําสั่งtimer
#define LINE_TOKEN  "y348hPh9EzC3A5SF71V0hgxAYj2uQjb1Tfg7y8ARe1u"

BLYNK_WRITE(V4)
{
 manul = param.asInt();
 digitalWrite(led,0);
 }


BLYNK_WRITE(V1) 
{
  t_slider = param.asInt();
  Blynk.virtualWrite(V7, t_slider);
  delay(100);
}


BLYNK_WRITE(V2)
{
 buton = param.asInt();
 digitalWrite(led,0);
 }

BLYNK_WRITE(V3)
{
    if (param.asInt() == 1){ // ถ้ามีการกดปุ่ม 

      digitalWrite(led, 1);

      if (lock3 == false){
        
        LINE.notify("ครบเวลากําหนดปั๊มนํ้าทํางาน");
          lock3 = true;

          }

        }else {

        lock3 = false;
        digitalWrite(led, 0);
        
      }   
  
}
    
    BLYNK_CONNECTED() {
  Blynk.syncAll();
  digitalWrite(one,HIGH);
    }

void setup() 
{
Blynk.begin(auth, ssid, pass,"oasiskit.com", 8080);
pinMode(led, OUTPUT);
Serial.begin(9600);
pinMode(one,OUTPUT);
 LINE.setToken(LINE_TOKEN);
}



void loop() 
{
 sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 0, 1023, 100, 0);
   Blynk.virtualWrite(V0, outputValue);
  
  if (buton == 1) {
      if (outputValue < t_slider)
            {digitalWrite(led, 1);
            if(lock1 == false){
             LINE.notify("ความชื้นตํ่ากว่ากําหนดปั๊มนํ้าจึงทํางาน");
            lock1 = true; }}
            else
    {
      lock1 = false;
    }

      if (outputValue > t_slider)
         {digitalWrite(led,0);
          if(lock2 == false){
          LINE.notify("ความชื้นเกินกําหนดปั๊มนํ้าหยุดทํางาน");
         lock2 = true;}}
     else{
    lock2 = false;
  }}


   if (manul == 1){
       digitalWrite(led, 1);}
   
 
   Blynk.run();
}
