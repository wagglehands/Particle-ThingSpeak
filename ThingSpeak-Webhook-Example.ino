int led = D7;  // The on-board LED

void setup() {
  // make sure you create your own integration following the example in the README
  Particle.subscribe("hook-response/temp", myHandler, MY_DEVICES);
  pinMode(led, OUTPUT);
}

void loop() {
  //turning on the LED so we know when it has published!
  digitalWrite(led, HIGH);   // Turn ON the LED

  // create some random temps
  String temp = String(random(60, 80));
  Particle.publish("temp", temp, PRIVATE);
  
  delay(30000);               // Wait for 30 seconds

  digitalWrite(led, LOW);    // Turn OFF the LED
  delay(30000);               // Wait for 30 seconds
}


void myHandler(const char *event, const char *data) {
  // Handle the webhook response
  Serial.println(event);
  Serial.println(data);
    
  Particle.publish("GotIt", String(data));
}