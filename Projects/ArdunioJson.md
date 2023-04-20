https://arduinojson.org/

```#include <ArduinoJson.h>

const char* json = "{\"CompressedData\":\"110110100011111001100010110101110111111101000111111100100111110010111000100010110001110111100100010000001101101001110110111101101010101110010101101000110110100010000000101100011101101010011100101110100110010000001011001000011011001100000001100010001111010010111100010000101000100000001010011001100010100100001100101000010\",\"CompressesDataBits\":324,\"NonCompressedDataBits\":576,\"Symbols_with_codes\":{\"0\":\"111\",\"1\":\"11000\",\"2\":\"0011\",\"3\":\"00010\",\"4\":\"011111\",\"5\":\"000110\",\"6\":\"10010\",\"7\":\"010100\",\"8\":\"10011\",\"9\":\"011010\",\"{\":\"11011\",\"a\":\"000111\",\"e\":\"00001\",\"p\":\"011000\",\",\":\"011001\",\":\":\"0010\",\"\\\"\":\"010\",\"y\":\"011011\",\"d\":\"011100\",\"H\":\"011101\",\"Z\":\"011110\",\"}\":\"10000\",\"r\":\"10001\",\".\":\"10010\",\"t\":\"10100\",\"i\":\"10101\",\"m\":\"10110\",\"u\":\"10111\",\"T\":\"11001\",\"-\":\"11010\",\" \":\"00000\"},\"Symbols\":[\"{\",\"\\\"\",\"2\",\"0\",\"3\",\"-\",\"4\",\"T\",\":\",\"1\",\"Z\",\" \",\"H\",\"u\",\"m\",\"i\",\"d\",\"t\",\"y\",\"9\",\"8\",\".\",\",\",\"e\",\"p\",\"r\",\"a\",\"5\",\"}\"],\"Probabilities\":[2,10,5,8,3,2,1,2,5,2,1,4,1,2,2,2,1,2,1,1,2,2,1,3,1,2,1,1,2]}";

void setup() {
  Serial.begin(9600);

  StaticJsonDocument<1024> doc;

  deserializeJson(doc, json);

  const char* CompressedData = doc["CompressedData"];
  int CompressedDataBits = doc["CompressesDataBits"];
  int NonCompressedDataBits = doc["NonCompressedDataBits"];

  Serial.println(CompressedData);
  Serial.println(CompressedDataBits);
  Serial.println(NonCompressedDataBits);

  JsonObject Symbols_with_codes = doc["Symbols_with_codes"];
  JsonArray Symbols = doc["Symbols"];
  JsonArray Probabilities = doc["Probabilities"];

  for (JsonPair kv : Symbols_with_codes) {
    const char* symbol = kv.key().c_str();
    const char* code = kv.value().as<const char*>();
    Serial.print(symbol);
    Serial.print(": ");
    Serial.println(code);
  }

  for (JsonVariant v : Symbols) {
    const char* symbol = v.as<const char*>();
    Serial.println(symbol);
  }

  for (JsonVariant v : Probabilities) {
    int prob = v.as<int>();
    Serial.println(prob);
  }
}

void loop() {
  // Do nothing
}
```
