/*
    ContentFromWebPage.ino

    Part of Sendit

    Description:
    This sketch fetches the content of a webpage,
    stores it in an array, and disconnects.

    Materials:
    Arduino
    Adafruit CC3000 Wi-Fi Shield
*/

#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>

// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER);
// Connection Details
#define WLAN_SSID       "PrettyFlyForAWifi"           
#define WLAN_PASS       "arduinotest"
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  3000

#define WEBSITE      "www.stud.hosted.hr.nl/0878531"
#define WEBPAGE      "/ov-wekker/index.html"

uint32_t ip;

void setup() {
    Serial.begin(9600);
    Serial.println("Hello, CC3000!"); 

    Serial.println("Initializing...");
    if (!cc3000.begin())
    {
      Serial.println("Couldn't begin()! Check your wiring?");
      while(1);
    }
      
    Serial.print("Attempting to connect to "); Serial.println(WLAN_SSID);
    if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
      Serial.println("Failed!");
      while(1);
    }
       
      Serial.println("Connected!");
      
      /* Wait for DHCP to complete */
      Serial.println("Request DHCP");
      while (!cc3000.checkDHCP())
      {
        delay(100); // ToDo: Insert a DHCP timeout!
      } 

      ip = 0;
      // Try looking up the website's IP address
      Serial.print(WEBSITE); Serial.print(F(" -> "));
      while (ip == 0) {
        if (! cc3000.getHostByName(WEBSITE, &ip)) {
          Serial.println("Couldn't resolve!");
        }
        delay(500);
      }
      
      Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 80);
      if (www.connected()) {
        www.fastrprint(F("GET "));
        www.fastrprint(WEBPAGE);
        www.fastrprint(F(" HTTP/1.1\r\n"));
        www.fastrprint(F("Host: ")); www.fastrprint(WEBSITE); www.fastrprint(F("\r\n"));
        www.fastrprint(F("\r\n"));
        www.println();
      } else {
        Serial.println("Connection failed");    
        return;
      }

      Serial.println("-------------------------------------");
      
      /* Read data until either the connection is closed, or the idle timeout is reached. */ 
      unsigned long lastRead = millis();
      while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
        while (www.available()) {
          char c = www.read();
          Serial.print(c);
          lastRead = millis();
        }
      }
      www.close();
      Serial.println("-------------------------------------");

      Serial.println("Disconnecting");
      cc3000.disconnect();
}

void loop() {

}

