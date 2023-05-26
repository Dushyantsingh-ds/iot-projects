## Cloud Dashboard
![ Circuit ](https://github.com/Dushyantsingh-ds/iot-projects/blob/main/Projects/Pressure%20Monitoring%20with%20AWS/Img/cloud.png)

## Code 
```
#include "secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "HX710B.h"

const int DOUT = 13;   //sensor data pin
const int SCLK  = 15;   //sensor clock pin

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Define pressure sensor
HX710B pressure_sensor; 

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC   "$aws/things/PressureMoni_ESP32/shadow/sentData"
#define AWS_IOT_SUBSCRIBE_TOPIC "$aws/things/PressureMoni_ESP32/shadow/update/delta"

int msgReceived = 0;
String rcvdPayload;
char sentData[512];


WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("");
  Serial.println("################ Project by -@dushyantsingh-ds ###################");
  Serial.println("");
  Serial.println("###################### Starting Execution ########################");
  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Create a message handler
  client.onMessage(messageHandler);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void messageHandler(String &topic, String &payload) {
  msgReceived = 1;
  rcvdPayload = payload;
}

void setup() {
  Serial.begin(9600);
  pinMode(22, OUTPUT);
  
  connectAWS();
  
  pressure_sensor.begin(DOUT, SCLK);
  
  Serial.println("Getting time");
// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(3600);
  
  Serial.println("##############################################");
}
int count=0;
void loop() {
    while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
if (pressure_sensor.is_ready()) {
   //Serial.println(pressure_sensor.pascal()); 
  // Serial.println(pressure_sensor.atm());
 //  Serial.println(pressure_sensor.mmHg());
//   Serial.println(pressure_sensor.psi());

   formattedDate = timeClient.getFormattedDate();
//   String sentD = "{\"TimeStamp\":\"" + formattedDate + "\",\"Pressure\":\"" + String(pressure_sensor.pascal(),1) + ""}";
  String sentD = "{\"TimeStamp\":\"" + formattedDate + "\",\"Pressure\":\"" + String(pressure_sensor.pascal(), 1) + "\",\"Unit\":\"Pa\"}";

   Serial.println(sentD);
   client.publish(AWS_IOT_PUBLISH_TOPIC, sentD);
        
   Serial.println("Sended");
   } else {
    Serial.println("Pressure sensor not found.");
  }
  delay(1000);  
  client.loop();
}

```

secret.h
```

#include <pgmspace.h>

#define SECRET
#define THINGNAME "PressureMoni_ESP32"

const char WIFI_SSID[] = "DevWifi";
const char WIFI_PASSWORD[] = "XXXXX";
const char AWS_IOT_ENDPOINT[] = "XXXXXXXXXXXX.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----

-----END RSA PRIVATE KEY-----
)KEY";

```

## Wiring
![ Circuit ](https://github.com/Dushyantsingh-ds/iot-projects/blob/main/Projects/Pressure%20Monitoring%20with%20AWS/Img/wiring.jpg)

## IDE
![ result ](https://github.com/Dushyantsingh-ds/iot-projects/blob/main/Projects/Pressure%20Monitoring%20with%20AWS/Img/Ide.png)




### Connect with me:

[<img align="left" alt="Dushyant Singh | LinkedIn" width="22px" src="https://cdn.jsdelivr.net/npm/simple-icons@v3/icons/linkedin.svg" />][linkedin]
[<img align="left" alt="Dushyant Singh | Twitter" width="22px" src="https://cdn.jsdelivr.net/npm/simple-icons@v3/icons/twitter.svg" />][twitter]
[<img align="left" alt="Dushyant Singh | GitHub" width="22px" src="https://cdn.jsdelivr.net/npm/simple-icons@v3/icons/medium.svg" />][github]
[<img align="left" alt="Dushyant Singh | Medium" width="22px" src="https://raw.githubusercontent.com/iconic/open-iconic/master/svg/globe.svg" />][medium]
[<img align="left" alt="Dushyant Singh | Instagram" width="22px" src="https://cdn.jsdelivr.net/npm/simple-icons@v3/icons/instagram.svg" />][instagram]
[<img align="left" alt="Dushyant Singh | Facebook" width="22px" src="https://cdn.jsdelivr.net/npm/simple-icons@v3/icons/facebook.svg" />][facebook]
[<img align="left" alt="Dushyant Singh | Telegram" width="22px" src="https://cdn.jsdelivr.net/npm/simple-icons@v3/icons/telegram.svg" />][telegram]

<br />

[medium]: https://dushyantsingh-ds.medium.com/
[linkedin]: https://linkedin.com/in/dushyantsingh-ds/
[instagram]: https://www.instagram.com/dushyantsingh.ds/
[twitter]: https://twitter.com/dushyantsingh_d
[facebook]: https://www.facebook.com/dushyantsingh.india
[github]: https://github.com/Dushyantsingh-ds
[telegram]: https://t.me/dushyantsingh_d
