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
  Serial.print(F("[SENSOR]: Humidity: "));
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
    Serial.println(F("[SENSOR]: Failed to read from DHT sensor!"));
    return null;
  }
  return result;
}


int computeAdjustment(SensorData d) {
  // TODO: actually implement this
  // testing code
  static int adjustment = -1000;
  adjustment = -adjustment;
  return adjustment;
}

void makeAdjustment(int adjustment) {
  if (adjustment < 0) {
    // retract the actuator for that number of miliseconds
    digitalWrite(relay_1, LOW);
    digitalWrite(relay_2, HIGH);
    delay(adjustment);
    digitalWrite(relay_1, LOW);
    digitalWrite(relay_2, LOW);
  } else if (adjustment > 0) {
    // extend the actuator for that number of miliseconds
    digitalWrite(relay_1, HIGH);
    digitalWrite(relay_2, LOW);
    delay(adjustment);
    digitalWrite(relay_1, LOW);
    digitalWrite(relay_2, LOW);
  } else {
    // do nothing
    return;
  }
}

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

/* Tuning Parameters:
    step magnitude - how much to move per step?
    update_interval - how frequently is the sensor checked and updated.
*/
void loop() {
  int update_interval = 500; // the time between updates in ms
  // read new data from the sensor
  SensorData data = getSensorData(dht);
  if (data == null) return
  // print data to the console
  serialLogData(data.humidity, data.temperature);

  int adjustment = computeAdjustment(data);
  makeAdjustment(adjustment);

  // wait for some amount of time in miliseconds
  delay(update_interval);
}

