#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "WiFiEsp.h"
#include "arduino_secrets.h"
#include <dht11.h>

dht11 DHT11;
int DHT11PIN = A0;
int  sensorPin  =  A1;     // select the input  pin for  the potentiometer 
int  ledPin  =  13;   // select the pin for  the LED
int  sensorValue =  0;  // variable to  store  the value  coming  from  the sensor

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
char aioServer[] = AIO_SERVER;  // your aio server name
int aioServerPort = AIO_SERVERPORT;  // your aio server port name
char aioUser[] = AIO_USERNAME;  // your aio username
char aioKey[] = AIO_KEY;  // your aio key

int status = WL_IDLE_STATUS; // the Wifi radio's status

WiFiEspClient client;
//Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
//Declare the Adafruit IO feeds
Adafruit_MQTT_Publish dht11humi = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dht11humi");
Adafruit_MQTT_Publish dht11temp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dht11temp");
Adafruit_MQTT_Publish soundsensor = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/soundsensor");

void MQTT_connect();

void setup() {
pinMode(ledPin,OUTPUT);
Serial.begin(9600);
Serial1.begin(115200);
WiFi.init(&Serial1);
if (WiFi.status() == WL_NO_SHIELD) {
Serial.println("WiFi shield not present"); 
while (true);
}
if( status != WL_CONNECTED) {
client.flush();
client.stop();
Serial.print("Attempting to connect to WPA SSID: ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
Serial.println("Connected ");
Serial.println(WiFi.localIP());
delay(1000);  
}
}

uint32_t x=0;
uint32_t y=0;
uint32_t z=0;

void loop() {
delay(100000); 
MQTT_connect();
int chk = DHT11.read(DHT11PIN);
y=DHT11.humidity;
dht11humi.publish(y);
Serial.print("Humidity = ");
Serial.println(y); // Display humidity on the serial monitor

x=DHT11.temperature;
dht11temp.publish(x);
Serial.print("Temperature = ");
Serial.println(x); // Display temperature on the serial monitor

sensorValue =  analogRead(sensorPin);
digitalWrite(ledPin,  HIGH); 
delay(sensorValue); 
digitalWrite(ledPin,  LOW);
delay(sensorValue);

z = sensorValue;
soundsensor.publish(z);
Serial.print("Noise Level = ");
// Serial.println(sensorValue,  DEC);
Serial.println(z);

}

    //Create the MQTT_connect function to connect and reconnect as necessary to the MQTT server.
void MQTT_connect() {
    int8_t ret;
    
    // Stop if already connected.
    if (mqtt.connected()) {
    return;
    }
    Serial.print("Connecting to MQTT... ");
    
    uint8_t retries = 3;
    
    while ((ret = mqtt.connect()) != 0) {   // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5);     // wait 5 seconds
    
    retries--;
    mqtt.connect();
    
        if (retries == 0) {
          
          // basically die and wait for WDT to reset me
        break;
        
        //while (1);
        
        }
    }
    Serial.println("MQTT Connected!");
 }


