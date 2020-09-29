#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "";
char pass[] = "";
int keyIndex = 0;

int status = WL_IDLE_STATUS;
char philipsHueHub[] = "192.168.1.71";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed");
    while (true);
  }

  String fv = WiFi.firmwareVersion();

  if(fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
    Serial.print("Current version: ");
    Serial.print(fv);
  }

  while (status != WL_CONNECTED) {
    Serial.print("\nAttempting to connect to SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.println("Connected to wifi");

  printWifiStatus();

  Serial.println("\nStarting connection to Philips Hue Hub...");

  if (client.connect(philipsHueHub, 80)) {
    Serial.println("Connected to Philips Hue Hub");
  }

}

void loop() {
  
}

void turnOnBedroom() {
  toggleLight("on", "35");
  toggleLight("on", "36");
  toggleLight("on", "17");
  toggleLight("on", "21");
  toggleLight("on", "25");
  toggleLight("on", "26");
  toggleLight("on", "27");
  toggleLight("on", "37");
  toggleLight("on", "32");
}

void toggleLight(String status, String light) {

    String command = "{\"on\": " + status + "}";
    Serial.println("connected to server");
    Serial.print("PUT /api/");
    Serial.print("<username>");
    Serial.print("/lights/");
    Serial.print(light);
    Serial.println("/state HTTP/1.1");
    Serial.println("keep-alive");
    Serial.print("Host:");
    Serial.println(philipsHueHub);
    Serial.print("Content-Length: ");
    Serial.println(command.length());
    Serial.println("Content-Type: text/plain;charset=UTF-8");
    Serial.println();
    Serial.println(command);
    
    client.print("PUT /api/");
    client.print("<username>");
    client.print("/light/");
    client.print(light);
    client.println("/state HTTP/1.1");
    client.println("keep-alive");
    client.print("Host:");
    client.println(philipsHueHub);
    client.print("Content-Length: ");
    client.println(command.length());
    client.println("Content-Type: text/plain;charset=UTF-8");
    client.println();
    client.println(command);
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();

  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
