// Author: Iain Macpherson

#include "DHT.h"

/*=============================================================================
    Defines
 *=============================================================================*/
// Pins in use
#define DHT_PIN 2
#define RELAY1_PIN 7
#define RELAY2_PIN 8

/*=============================================================================
    Helper Functions
 *=============================================================================*/
// Print data to the serial consol
void serialLogData(float h, float t) {
  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
}


// Struct to hold the useful sensor data
typedef struct {
  float humidity;
  float temperature;
} SensorData;

// Read data from the sensor and return the data in a SensorData struct
SensorData getSensorData(DHT dht) {
  SensorData result;

  float h = dht.readHumidity();  //reads humidity
  float t = dht.readTemperature(); //reads temperature

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return null;
  }
  return result;
}


int computeAdjustment(SensorData d) { return 0; }

void makeAdjustment(int adjustment) { }

/*=============================================================================
    Startup Code
 *=============================================================================*/
/* DHT Setup
    Params:
        DHT_PIN: digital pin for use with the dht sensor
        DHT11:   the sensor type (there is a DHT22 available as well)
*/
DHT dht(DHT_PIN, DHT11);

void setup() {
  Serial.begin(9600);

  // initialise the dht library
  dht.begin();

  // setup both relay pins as output
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  // start with both relays off
  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);
}

/*=============================================================================
    Main Loop
 *=============================================================================*/
/* TODO:
    Get sensor data
    Compute adjustment with error function
    Make adjustment
    (maybe) adjust update_interval
*/

void loop() {
  int update_interval = 500; // the time between updates in ms
  // read new data from the sensor
  SensorData data = getSensorData(dht);
  if (data == null) return

  int adjustment = computeAdjustment(data);
  makeAdjustment(adjustment);

  // print data to the console
  serialLogData(data.humidity, data.temperature);

  // wait for some amount of time in miliseconds
  delay(update_interval);
}
