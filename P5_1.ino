#include <WiFi.h>
#include "ThingSpeak.h" // alwaysincludethingspeakheaderfile
// yournetworkSSID (name) 
const char* ssid=  "INFINITUM1404_2.4";   
// yournetworkpassword
const char* pass =  "9pY3j5QnMa";   
WiFiClient client;
unsigned long myChannelNumber= 2056565;  //SECRET_CH_ID;
const char* myWriteAPIKey= "CECFI730AQKX4OMT";
// Initializewithrandomvalues
int number1 = random(0,50);
int number2 = random(0,50);
String myStatus= "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  WiFi.begin(ssid, pass); 
  Serial.println(); 
  Serial.print("WaitforWiFi..."); 
  while(WiFi.status() != WL_CONNECTED) { 
  Serial.print("."); 
  delay(500); 
  }
  Serial.println(""); 
  Serial.println("WiFiConnected"); 
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP()); 
  ThingSpeak.begin(client);  // InitializeThingSpeak
}

void loop() {
  // put your main code here, to run repeatedly:
  // set thefieldswiththevalues
  ThingSpeak.setField(1, number1);
  ThingSpeak.setField(2, number2);
  // figure outthestatus messageformulti fields
  if(number1 > number2){
  myStatus= String("field1 isgreaterthanfield2"); 
  }
  else if(number1 < number2){
  myStatus= String("field1 islessthanfield2");
  }
  else{
  myStatus= String("field1 equalsfield2");
  }
  // set thestatus
  ThingSpeak.setStatus(myStatus);
  // writetotheThingSpeakchannel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
  Serial.println("ThingSpeakChannelupdatesuccessful.");
  }
  else{
  Serial.println("Problemupdatingchannel. HTTP error code" + String(x));
  }
  // changethevalues
  number1++;
  if(number1 > 99){
  number1 = 0;
  }
  number2 = random(0,100);
  delay(20000); // Wait20 secondstoupdatethechannelagain
}
