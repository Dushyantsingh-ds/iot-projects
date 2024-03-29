/*
  Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
  Permission is hereby granted, free of charge, to any person obtaining a copy of this
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify,
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <pgmspace.h>

#define SECRET
#define THINGNAME "Research_esp32"

const char WIFI_SSID[] = "DevWifi";
const char WIFI_PASSWORD[] = "DevWifi123";
const char AWS_IOT_ENDPOINT[] = "asncyv8h82ukx-ats.iot.ap-south-1.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
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
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAK31h/4WVTH/Yhc2/uSjaBg7BCGnMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzA0MTkxMDEx
NDdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC4hWrXawHkLXHs+O8u
up9dz70JsxAvvO2pnc+NE/t5/GyOLqJty+6O2BALMX2gFMQpSbwfWXPjZvLaFBnW
qxfdAy0zxjvYnJqpG9Cryv6hPRUFpiliqzEDZmA89S1fMU+sT0spProxT0C24xJe
QqAAsk44uJvnQhBZKgyXwXNCcxaZ3XS/uuJY56dNZRRVbA2yTjDK+UdA+s49dZlo
v4uAefyFH+Rm058PFlKXmLh8qF8oSttwQ0zXu0WJahQpvQmCZfilPA7iXiA+p72V
cPWZELDtYyfXP7gb5HPkbE1S+cVirnBGrz/zvxIPHsDcRrD9ixsCBbDvizcWEYnM
+W7fAgMBAAGjYDBeMB8GA1UdIwQYMBaAFP17Tme1IsdAiskvhblnrm1KEGLyMB0G
A1UdDgQWBBTePRm22/JUKf6n+PYd/g4FjYQPpDAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEA4pd5wn/T2YDo+o1YuDmhv1S2
8jkyQ/2qOCnjIDwvtyV2NPlvW7TrZIyMa2lHGCvFHX8mwzKoDLCXUtXOKq6jMhem
0uhUh381xXc6xmcEY4aXzzbbBhW6jLaJ7ArpnNKa+IihFBWmd7ZlkTmtqLlylmOb
rxnCKCZqoEdkwD8WUAMuxxLE30ZqWYZdctpjWQc1NXSwKB7s6QVfy8fpTWrN8piw
M/gyT+MKigHO4h9I/6Al70DF5dsqeNy28EKeas9UC3L1cBAGEpZEY1Nwx1IRv0Wq
PZ+aO0U+m1cF4cpYNjbZTac1fdgmSQyn4F58PEiDZdrsiHFIXnXLCaK+mntzEA==
-----END CERTIFICATE-----

)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAuIVq12sB5C1x7PjvLrqfXc+9CbMQL7ztqZ3PjRP7efxsji6i
bcvujtgQCzF9oBTEKUm8H1lz42by2hQZ1qsX3QMtM8Y72JyaqRvQq8r+oT0VBaYp
YqsxA2ZgPPUtXzFPrE9LKT66MU9AtuMSXkKgALJOOLib50IQWSoMl8FzQnMWmd10
v7riWOenTWUUVWwNsk4wyvlHQPrOPXWZaL+LgHn8hR/kZtOfDxZSl5i4fKhfKErb
cENM17tFiWoUKb0JgmX4pTwO4l4gPqe9lXD1mRCw7WMn1z+4G+Rz5GxNUvnFYq5w
Rq8/878SDx7A3Eaw/YsbAgWw74s3FhGJzPlu3wIDAQABAoIBAC5vvRSbZG11Fl+p
wh/DbYnhVtSTELbC2BjAk1QQvE/Vu8gIam4xTUb7jwYSHWhk8XzmhoZpL6YB6YoC
VwJUKnw/aWfHMpZvyuhWDKy/OFeBlMHIMFAZfws4/2030oRLV56okeS+WYNBS6r6
+EtqfvPN66uQogOP96dI0sR6NbR57r9W9rGtQVZG2sMlpMNwgLvh0tw1uNk+9QFX
LWm0lXD+fLt7G23JI9KIQEuPTRS2yVDlYCPoC+Iqi/icbEuNsaBssnntkAJ/n6Dm
5HssLEcJRgCw6Qn/f1snj2kMk1Wfoe3KvIrZ1aqx+zDQTTF3FDjE43qPJCC/49s1
g2iXhhkCgYEA3uv0UH5fgQeIJdNr5qDeFgFZpER/fAUrC4NetLPmmu+JtTUZ+lyc
cD/HF8yjscsD43r7YvX4sxLUEgYedlu7vVY1rXKRWScZYQdwgn2sEQv1krROAlOB
MbRC9kzYOFyBkzeZYrghZnfsej8UvwBVkxC/gAy4FzjAneyVk3YJUW0CgYEA0+bB
e6ntfG0Tjqt/Ncpzm+PDyJwCya6VEa5uBU3MdTysFI6X/Z1OZNiXIQeXX6IbeOdN
7vNjnAQ5opGFzxIxNdm7bp/UopOlsZhPx7/z1suyUI9+U3XcBr5x+EQ2H3PO3FuH
4Kir3Ezn5/hXZgZH61eNWAGKR58K+RmxYOUKXfsCgYEAsOIFMEG2QknZrDoAajXH
Qyq7GG8JwTzQlQgeg8AkAViEqnaCMHh/4UmaDrZgRVlTspMJGdMXDfCoucyFK2FK
rMfVO9Wmo1k0+BrRGZniiHw21bugEpRz9R6V6526C67LWidJ3F1Ck24hBDc9nPkE
7fbiHRb6k+KCZE0vupx0dFkCgYAzwxWWaL8LevWhD0GG2Up+VRf5RCrmK1Bcvlg/
0W5VYRnD98Um/asttT7NobYXdVjyosYFzcySSvHtRVEDcTU2K1a+wipGAH0kMcmj
SL9+w8luJm88Yfj6aMEcXUU/T6HDcFRzy6AXs22e26o10Oj2ky+CxPWLY01h5iXP
PoPWywKBgQCoP/rZ7BC5VPIKNy3un2qq6ZmDN+q0iIDadjDYDqSTNqgx1pWCHow/
Y3CC2RMoppHo5B3H8f2f4KHxhfm+/ulAw7uodIlVQHD75XAaInbmdr6sGl9fhYka
VYCwbZH+VzBSUB+v2fjN3usX4trcZ+3J1KxTP1m9UtgpgVDZgkQxeg==
-----END RSA PRIVATE KEY-----
)KEY";
