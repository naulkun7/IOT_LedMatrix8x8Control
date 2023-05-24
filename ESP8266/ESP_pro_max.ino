#include <ESP8266WiFi.h>
#include <Arduino.h>

const char* ssid = "Hana";
const char* password = "hana32142135##";

WiFiServer server(80);
 
void setup() {
  Serial.begin(9600);
  delay(10);
 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!!!");

  server.begin();

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("-------------------------------------------------");
  Serial.println();
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  // Serial.println(request);
  client.flush();


  //Take back Image Value
  String arr;
  if (request.indexOf("/favicon.ico") == -1)  {
    arr = request; 
    arr.remove(0,5);
    arr.remove(32);

    const char* value = arr.c_str();
    Serial.printf(value);
  }
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE html>\n<html lang=\"en\">\n  <head>\n    <meta charset=\"UTF-8\" />\n    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\" />\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />\n    <title>Document</title>\n\n    <style>\n      .container {\n        width: 80%;\n        margin: 0 auto;\n        background-color: #f2f2f2;\n        padding: 20px;\n        box-sizing: border-box;\n        border-radius: 5px;\n        box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);\n      }\n      header #title {\n        text-align: center;\n      }\n\n      header .create-link {\n        display: flex;\n        flex-wrap: wrap;\n        flex-direction: column;\n        align-items: center;\n        justify-content: center;\n      }\n\n      header .create-link #inputText {\n        width: 80%;\n        text-align: center;\n      }\n\n      .main .box {\n        display: flex;\n        flex-wrap: wrap;\n      }\n\n      .main .box .small-box {\n        display: flex;\n        flex-wrap: wrap;\n        flex-direction: column;\n        align-items: center;\n        width: 50%;\n      }\n\n      .main .box .small-box .image {\n        object-fit: cover;\n        aspect-ratio: 3/3;\n        width: 200px;\n        height: auto;\n      }\n    </style>\n  </head>\n  <body>\n    <header>\n      <div class=\"container\">\n        <h1 id=\"title\">IOT PROJECT</h1>\n        <div class=\"create-link\">\n          <input type=\"text\" id=\"inputText\" placeholder=\"Enter a URL\" />\n          <hr />\n          <button onclick=\"createLink()\">Create image</button>\n          <div id=\"output\" style=\"margin-top: 20px\"></div>\n        </div>\n      </div>\n    </header>\n    <div class=\"main\">\n      <div class=\"container\">\n        <div class=\"box\">\n          <div class=\"small-box\">\n            <h2 class=\"box-title\">Cat</h2>\n            <img\n              class=\"image\"\n              src=\"https://res.cloudinary.com/dpmcy6bbr/image/upload/w_1000,ar_1:1,c_fill,g_auto,e_art:hokusai/v1684940329/cat_whwbg9.jpg\"\n              alt=\"Cat\"\n            />\n            <a href=\"/136,248,168,113,033,121,125,190,\" class=\"button\">Cat</a>\n          </div>\n          <div class=\"small-box\">\n            <h2 class=\"box-title\">Heart</h2>\n            <img\n              class=\"image\"\n              src=\"https://hackster.imgix.net/uploads/attachments/1523703/q4_GIrF3d5Gzo.jpeg?auto=compress%2Cformat&w=1280&h=960&fit=max\"\n              alt=\"Heart\"\n            />\n            <a href=\"/000,102,255,255,126,060,024,000,\" class=\"button\">Heart</a>\n          </div>\n          <div class=\"small-box\">\n            <h2 class=\"box-title\">Apple</h2>\n            <img\n              class=\"image\"\n              src=\"https://res.cloudinary.com/dpmcy6bbr/image/upload/w_1000,ar_1:1,c_fill,g_auto,e_art:hokusai/v1684940331/apple_iukhvz.jpg\"\n              alt=\"Apple\"\n            />\n            <a href=\"/024,008,118,255,255,255,122,052,\" class=\"button\">Apple</a>\n          </div>\n        </div>\n      </div>\n    </div>\n    <script>\n      function createLink() {\n        var input = document.getElementById(\"inputText\").value;\n        var outputDiv = document.getElementById(\"output\");\n\n        var newSmallBox = document.createElement(\"div\");\n        newSmallBox.className = \"small-box\";\n\n        var title = document.createElement(\"h2\");\n        title.className = \"box-title\";\n        title.textContent = \"New Image\";\n\n        var image = document.createElement(\"img\");\n        image.className = \"image\";\n        image.src = input;\n        image.alt = \"New Image\";\n\n        var link = document.createElement(\"a\");\n        link.className = \"button\";\n        link.href = input;\n        link.textContent = \"New Image\";\n\n        newSmallBox.appendChild(title);\n        newSmallBox.appendChild(image);\n        newSmallBox.appendChild(link);\n\n        var box = document.querySelector(\".box\");\n        box.appendChild(newSmallBox);\n\n        document.getElementById(\"inputText\").value = \"\";\n      }\n    </script>\n  </body>\n</html>");
  
 
  delay(1);
}