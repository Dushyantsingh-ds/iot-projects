#include <pgmspace.h>

#define SECRET
#define THINGNAME "ESP8266"

const char WIFI_SSID[] = "Local";
const char WIFI_PASSWORD[] = "Local123";

const char AWS_IOT_ENDPOINT[] = "XXXXXX-ats.iot.ap-south-1.amazonaws.com";

int8_t TIME_ZONE = -5; //NYC(USA): -5 UTC

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
