#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "CCCC";
const char* password = "CCCC123456";

ESP8266WebServer server(80);

String html = "<!DOCTYPE html><html lang=\"en\"><head> <meta charset=\"UTF-8\">  <title>灯</title>  <style type=\"text/css\">   .float{     width:500px;      display:table;      position: absolute;     top:0;      left:0;     right:0;      bottom:0;     margin:auto;    }   a{      text-decoration:none;     text-align:center;      width:500px;      height:500px;     float:left;     display:table;      margin-top:50px;    }   input{      width:100%;     height:100%;      font-size:10em;     font-family:\"微软雅黑\";     display:table;    } </style></head><body> <div class=\"float\">   <a href=\"#\">    <a href=\"./pin?light=on\">     <input type=\"button\" value=\"OPEN\">    </a>    <a href=\"#\">    <a href=\"./pin?light=off\">      <input type=\"button\" value=\"OFF\">   </a>  </div></body></html>      ";

void pin(){
  if(server.arg("light")=="on"){
    digitalWrite(D4, LOW);
    server.send(200, "text/html", html);
  }else if(server.arg("light")=="off"){
    digitalWrite(D4, HIGH);
    server.send(200, "text/html", html);
  }
}

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/html", html);
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
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
  digitalWrite(led, 0);
}

void setup(void){
  pinMode(D4, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

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

  server.on("/", handleRoot);
  server.on("/pin", HTTP_GET, pin);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
