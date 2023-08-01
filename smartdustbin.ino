#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Adafruit_Sensor.h>
#include <Servo.h>
int val = 0 ; 
Servo s1;
long duration;
int distance;
FirebaseData karthik;
int status;

const char* ssid     = "santhosh"; // Change this to your WiFi SSID
const char* password = "kannan26"; // Change this to your WiFi password
const char* url   = "https://karthik-d9bdc-default-rtdb.firebaseio.com/"; 
const char* key = "VnjV8gxqtwyDA0NMrASjkgmNVkL1DZraZn0lv2jn"; 
const int trigPin = D6; 
const int echoPin = D7; 


void setup()  
{   
  
    Serial.begin(115200);
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.println("******************************************************");
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Firebase.begin(url,key);
    Firebase.reconnectWiFi(true);
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);
    Firebase.begin(url,key);
    Firebase.reconnectWiFi(true);
    Serial.begin(9600); // sensor buart rate  
    pinMode(14,HIGH);// Led Pin Connected To D5 Pin
    s1.attach(0); // servo attach D3 pin of arduino    
}  
void loop()   
{  

  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance=duration*0.034/2;
  Serial.println(distance);
  Firebase.setFloat(karthik,"/distance",distance);
  Serial.println(distance);
  val = digitalRead(5); // IR Sensor output pin connected to D1  
  Serial.println(val);  // see the value in serial m0nitor in Arduino IDE  
  //delay(100); // for timer

  if(distance<10)
  {
   status=0;
   Firebase.setFloat(karthik,"/status",status);
   Serial.println(status);
  }
  else
  {
   status=1;
   Firebase.setFloat(karthik,"/status",status);
   Serial.println(status);
  }
  if(val == 1 )  
  {  
   digitalWrite(14,HIGH); // LED ON 
   s1.write(0);  
   //delay(10);  
  }  
  else  
  {
   digitalWrite(14,LOW); // LED OFF   
   s1.write(180);  
   //delay(1000);
  
  }  
}  
