#include <ESP8266WiFi.h>


const char* ssid = "xxxxxxxxx";
const char* password = "xxxxxxxxx";

int colour;

int gpio13Led = 13;
int gpio12Relay = 12;



WiFiServer server(80);

void setup() {
Serial.begin(115200);
delay(10);

  pinMode(gpio13Led, OUTPUT);
  digitalWrite(gpio13Led, HIGH);
  
  pinMode(gpio12Relay, OUTPUT);
  digitalWrite(gpio12Relay, HIGH);



// Connect to WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

// Start the server
server.begin();
Serial.println("Server started");

// Print the IP address
Serial.print("Use this URL to connect: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");

}

void loop() {
// Check if a client has connected
WiFiClient client = server.available();
if (!client) {
return;
}

// Wait until the client sends some data
Serial.println("new client");
while(!client.available()){
delay(1);
}

// Read the first line of the request

//String request = client.readStringUntil(‘\r’);

//Serial.println(request);


String req = client.readStringUntil('\r');
Serial.println(req);
client.flush();

// Match the request

int value = LOW;
if (req.indexOf("/LED=ON") != -1) {
 digitalWrite(gpio13Led, LOW);
 digitalWrite(gpio12Relay, HIGH);
 Serial.println("on");
    delay(1000);

value = HIGH;



}
if (req.indexOf("/LED=OFF") != -1) {
    digitalWrite(gpio13Led, HIGH);
    digitalWrite(gpio12Relay, LOW);
    Serial.println("off");
    delay(1000);
value = LOW;
}

// Set ledPin according to the request
//digitalWrite(ledPin, value);

// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");

client.print("Led and light pin are now: ");

if(value == HIGH) {
client.print("On");
} else {
client.print("Off");
}


client.println("<br><br>");

client.println("<br><br>");
client.println("Click <a href=\"/LED=ON\">here</a> turn the LightON<br>");
client.println("Click <a href=\"/LED=OFF\">here</a> turn the Light OFF<br>");

client.println("</html>");

delay(1);
Serial.println("Client disonnected");
Serial.println("");

}
