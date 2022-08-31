// Author: Iain Macpherson

#include "DHT.h"

/*=============================================================================
    Defines
 *=============================================================================*/
// Pins in use
#define DHT_PIN 2
#define RELAY1_PIN 7
#define RELAY2_PIN 8

// measured time to go from fully retracted to fully extended.
#define FULL_TRANSITION 21800

// Struct to hold the useful sensor data
typedef struct {
  float humidity;
  float temperature;
} SensorData;

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

inline void actuator_retract() {
    digitalWrite(RELAY1_PIN, LOW);
    digitalWrite(RELAY2_PIN, HIGH);
}

inline void actuator_extend() {
    digitalWrite(RELAY1_PIN, HIGH);
    digitalWrite(RELAY2_PIN, LOW);
}

inline void actuator_off() {
    digitalWrite(RELAY1_PIN, LOW);
    digitalWrite(RELAY2_PIN, LOW);
}

inline int computeAdjustment(SensorData d) {
  // TODO: actually implement this
  // testing code
  // alternate between fully open and fully closed
  static int adjustment = -FULL_TRANSITION;
  adjustment = -adjustment;
  return adjustment;
}

void makeAdjustment(int adjustment) {
  if (adjustment < 0) {
    // retract the actuator for that number of miliseconds
    actuator_retract();
    delay(adjustment);
    actuator_off();
  } else if (adjustment > 0) {
    // extend the actuator for that number of miliseconds
    actuator_extend();
    delay(adjustment);
    actuator_off();
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
  actuator_off();
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
    step_resolution - how many steps between open and closed
    update_interval - how frequently is the sensor checked and updated.
*/
int step_resolution = 100;
int step_time = FULL_TRANSITION/step_resolution;

int update_interval = 500;
void loop() {
  // read and check sensor data
  SensorData data;
  data.humidity = dht.readHumidity();  //reads humidity
  data.temperature = dht.readTemperature(); //reads temperature

  if (isnan(data.humidity) || isnan(data.temperature)) {
    Serial.println(F("[SENSOR]: Failed to read from DHT sensor!"));
    return;
  }

  // print data to the console
  serialLogData(data.humidity, data.temperature);

  int adjustment = computeAdjustment(data);
  makeAdjustment(adjustment);

  // wait for some amount of time in miliseconds
  delay(update_interval);
}

