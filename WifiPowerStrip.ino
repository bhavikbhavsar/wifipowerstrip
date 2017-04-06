#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "Tech_D0007305";
const char* password = "HGRPXUXX";

ESP8266WebServer server(80);

const int rly_bt1 = 5;
const int rly_bt2 = 4;

void rly_bt1_on() {
  Serial.println("rly_bt1_on");
  digitalWrite(rly_bt1, 0);
  server.send(200, "text/plain", "bt1_on");
}


void rly_bt1_off() {
  Serial.println("rly_bt1_off");
  digitalWrite(rly_bt1, 1);
  server.send(200, "text/plain", "bt1_off");
}


void rly_bt2_on() {
  Serial.println("rly_bt2_on");
  digitalWrite(rly_bt2, 0);
  server.send(200, "text/plain", "bt2_on");
}


void rly_bt2_off() {
  Serial.println("rly_bt2_off");
  digitalWrite(rly_bt2, 1);
  server.send(200, "text/plain", "bt2_off");
}


void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void){
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  pinMode(rly_bt1, OUTPUT);
  pinMode(rly_bt2, OUTPUT);
  digitalWrite(rly_bt1, 1);
  digitalWrite(rly_bt2, 1);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/btn1on", rly_bt1_on);

  server.on("/btn1off", rly_bt1_off);

  server.on("/btn2on", rly_bt2_on);

  server.on("/btn2off", rly_bt2_off);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
