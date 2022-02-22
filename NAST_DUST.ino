// SDS011 dust sensor example
// -----------------------------
//
// By R. Zschiegner (rz@madavi.de).
// April 2016

#include <SDS011.h>

#include <ESP8266WiFi.h>
float p10,p25;
int error;
SDS011 my_sds;
const char* ssid = "Bik";  // your SSID
const char* password = "bik12345"; // your wIFi password

String apiKey = "EASM24MQT22HOKSD"; // API key
const char* server = "api.thingspeak.com";
WiFiClient client;



void setup() {
	my_sds.begin(2,6);
	Serial.begin(9600);

 delay(10);

Serial.println("Connecting to ");

Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED)

{

delay(10);

Serial.print(".");

}

Serial.println("");

Serial.println("WiFi connected");

}

void loop() {
	error = my_sds.read(&p25,&p10);
	
	delay(100);


if (client.connect(server, 80)) // "184.106.153.149" or api.thingspeak.com

{

    String postStr = apiKey;

    postStr +="&field1=";
    postStr += String(p25);
    
    postStr +="&field2=";
    postStr += String(p10);

    postStr += "\r\n\r\n";

 

    client.print("POST /update HTTP/1.1\n");

    client.print("Host: api.thingspeak.com\n");

    client.print("Connection: close\n");

    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");

    client.print("Content-Type: application/x-www-form-urlencoded\n");

    client.print("Content-Length: ");

    client.print(postStr.length());

    client.print("\n\n");

    client.print(postStr);

Serial.println("air quality level P2.5: "+String(p25));
Serial.println("air quality level P10: "+String(p10));

Serial.println("Data Send to Thingspeak");

}

delay(100);

client.stop();

Serial.println("Waiting...");

 

// thingspeak needs minimum 15 sec delay between updates.

delay(1500);

}
