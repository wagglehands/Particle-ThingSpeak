#include <MQTT.h>

const long channelId = XXXX; // Change this to your ThingSpeak channel number.
String clientId = "XXXX";
String username = "XXXX";
String password = "XXXX";
char server[] = "mqtt3.thingspeak.com";

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 20L * 1000L; // Post data every 20 seconds. 

int strength = WiFi.RSSI();
int power;

MQTT client(server, 1883, callback);               // Initialize the MQTT client.


// Define a callback function to initialize the MQTT client.
void callback(char* topic, byte* payload, unsigned int length) {
    
    Serial.println(topic);
    
    char p[length + 1]; // Leave an extra space to null terminate the string.
    memcpy(p, payload, length);
    p[length] = NULL;  // Terminate the string.
    
    Serial.println(p);
    
}
void setup() {
}

void loop() {
    // If MQTT client is not connected then reconnect.
    if (!client.isConnected()) {
      reconnect();
    }
    
    // Call the loop continuously to establish connection to the server.
    client.loop();  
    
    if (millis() - lastConnectionTime > postingInterval) {
        mqttpublish();
    }
}

void mqttpublish() {
    
    //Get SSID signal strength
    strength = WiFi.RSSI();
    
    //Power in milliwatts
    //power = 10^(strength/10);
    //power = 10;
    
    // Create a data string to send data to ThingSpeak.
    // Use these lines to publish to a channel feed, which allows multiple fields to be updated simultaneously.
    // String data = String("field1=" + String(strength) + "&field2=" + String(power) );
    // String topic = String("channels/"+String(channelId)+ "/publish");
    
    // Use the next two to publish to a single channel field directly.
    String data = String(strength);
    String topic = String("channels/"+String(channelId)+ "/publish/fields/field1");
    
    Serial.println("PUBLSHED!!!: " + data);
    client.publish(topic,data);
    
    lastConnectionTime = millis();
}


void reconnect(){
    
    Particle.publish("Attempting MQTT connection");
        
    // Connect to the ThingSpeak MQTT broker.
    if (client.connect(clientId,username,password))  {
        // You could also subscribe to a channel here too so you could received messages back from the MQTT broker
        // client.subscribe("channels/" + String( channelId ) + "/subscribe/fields/field1");
        
        // Track the connection with particle console.
        Particle.publish("Conn:"+ String(server) + " cl: " + String(clientId)+ " Uname:" + String(username));
    } else {
        Particle.publish("Failed to connect. Trying to reconnect in 2 seconds");
        delay(2000);
    } 
}