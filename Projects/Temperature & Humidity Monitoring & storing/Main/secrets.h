/* This code is desgined by Dushyant singh
 *  You can follow me on Github for more such IoT and AI content: Github/@dushyantsingh-ds
 */
 
#include <pgmspace.h>
#define SECRET
const char WIFI_SSID[] = "DevWifi";
const char WIFI_PASSWORD[] = "DevWifi123";

#define THINGNAME "ESP8266_AWSDB"
int8_t TIME_ZONE = -5; //NYC(USA): -5 UTC
const char MQTT_HOST[] = "asncyv8h82ukx-ats.iot.us-west-1.amazonaws.com";



// Amazon Root CA 1
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVALwJh+CGlskIwSDUr9BsSao84fEjMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzA3MDIxOTA0
MzNaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDGqC16evBV1P/JYCgH
+xP1KRNbFKZMuGiOsPs4FA/i9eORPXPniQDjLz8Ey2ce6VdvQBvJTe8PUaUeSL4l
G+CzndkxTgPXmcqZlAd+khxqenqHrkEI4yKqoid2Ah7tDxZ8FfTMcQGFSMER65Hn
I+SfHxNfhUeE0yTW813rZ1TN+k2y2E4uvDLDWfgnDfFKr6OplthiwcEk82EbVVuK
u5IoxCw1B0PVkxVWTZp1ViYdr2igDsGZ+q/dWV2U9YmjctibDgE5X0RhJjZpOXts
JhsreUmLkLOx+cb88p025dGmavPVBmoP7S267Z4T6MgS6V64tZ8BABqOr9X7iv4+
RJWJAgMBAAGjYDBeMB8GA1UdIwQYMBaAFOjVsbwJkl7uflr8fZyNoqtvJavYMB0G
A1UdDgQWBBQHlG460fdDeO9osE9CY1Qzh4cmmDAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAYOpje5mq/YqfxmHOBg/Mkyym
TR67RgKxh3pmF78jjBEDW97i60DRaVbyKHD2ytN3WQz+ie/4CO7QN1AM8jKhj7Lm
ClH+9L/0ILqpEJBXqlJw6JEZz6a/mChSJv/iDLjcAVxpYbWNuY7bsnjtJxgG8teI
V/caCaQ4FDzkUuOusNGH1c5KjCgFNADo9tbycOurXf+cb0CseAxocId7ZobuDWlX
Dn/gYFqmmIirYHP3NyXwkPI18OrfHw/rlp9LuoqgD1u3h50PJxfwY9GgNou/2uvE
1OQyJUY9tbaXHOvnUV2VncK+4etNRm+VkspBMboj1w9fmEco5BSEVX1UboxjEQ==
-----END CERTIFICATE-----


)KEY";

// Device Private Key
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAxqgtenrwVdT/yWAoB/sT9SkTWxSmTLhojrD7OBQP4vXjkT1z
54kA4y8/BMtnHulXb0AbyU3vD1GlHki+JRvgs53ZMU4D15nKmZQHfpIcanp6h65B
COMiqqIndgIe7Q8WfBX0zHEBhUjBEeuR5yPknx8TX4VHhNMk1vNd62dUzfpNsthO
Lrwyw1n4Jw3xSq+jqZbYYsHBJPNhG1VbiruSKMQsNQdD1ZMVVk2adVYmHa9ooA7B
mfqv3VldlPWJo3LYmw4BOV9EYSY2aTl7bCYbK3lJi5CzsfnG/PKdNuXRpmrz1QZq
D+0tuu2eE+jIEuleuLWfAQAajq/V+4r+PkSViQIDAQABAoIBAQCV0WWi9i5kfON+
6l6mTitp+9VWHkegmn54Bm8fhrnIb6p08YSEvCUIMKx1IDUf8dh31UBfW8ALrIY7
RZ7o+5JFw6h176EkKx7JHgNc6DI39zCLPNZdLncJeosKC2VpYLSTVjetKxh7fTfm
HOOHDuGvQ09n/WrHeDlTRmyxSNeDEoo9ghE4d7PtMlV0vBM9Lvh7fUPxIRCqSRjt
a+NFyYvZL25V9vbwiSpDZs5f7xX+JrwKkQgAhqm0C7VhNajaXgqR2llEowMEkmJk
SN09biLSAEVZdK5SWEe/UfLbkpjPaNGzia9zc/Q+G00PF/x+dzFs41CSFfujUuZv
WjtyuUNVAoGBAPDdi6BC4vpbBXv8AbtsitsG+c3FKQbI/grDPlALZnXZl26s+Pgy
3Zq6pfEZlh6oDXY+8LIpxsSkbMhNQT7OnTyj2H8meg1A4fTCmsQT5R0hCXbf069s
FEEZDw4o85oAhNGn320e27Leloqoy+LRqTEOCB14fvV3Wx8JZjwWhBXfAoGBANMj
r3siBE1KxNY26/PFHWzgeBfo1b03bZhmzl3pQBVcFK8Ky/9dKDu1qpWAVLwdxzpy
PvFCXt3ZqNJk6rQMhpBxEa4wMIXXkG1k3TR19j/7KWuj7r3d+H13EVxb//ZC3MdU
g9ZFM/o3LTFqmZCKbzRH1RCscU6lK6b8f8+fVDGXAoGBAOLs1w819QJJnvEgi8E4
kdmoyNDEX9K0qiMZrytakj2VssXi0O2FfqK4Fn7/zB811PkCc2JnWY0KHDLaFg5G
On1XIDEq3vJ9nmQqtATneYPoDDKizZ0IBk0OftCoZFlDA99CeY0k9XefndUlEnGv
dedxgNPDIlnBCWhEQr15uRehAoGAUNALzllKxDql9Ee5L+h2RsHztVMM3AtnCznu
KsuoF4TS9dxwECGb0J7L18Tyqb3MD3bC2JzKqqcwkrbFjnxs1MQyPDV9nPzQ7s34
TKgJxJthUy2/pzRac8sq/erIoX0d+71BaLW8Gz0bMxrWBBi4T45e4q7d/3gAqT1j
vhgBpakCgYEA1LmK7iV3uRWd3iVIoMhV3+c+AjQToMcLTQJc7Jpm0p73iR50xpfp
AChHeledWyElnGmm/+hnvpKmo1x8nbt8yRliS+govUDSprpI6dBY3Qz6yQo5fPet
G2+OG+UthN0SDUmzCwA/7CMHvJBnl2fFVYclaUodqZ6ILdaU71iUDTM=
-----END RSA PRIVATE KEY-----

)KEY";
