# Temp-and-Humidity-Controlled-Actuator

## Description
Using an arduino, control a linear actuator based on the temperature and humidity detected by a connected sensor.

### Components:
* 12VDC Power Supply
* Arduino Uno
* 2 Channel Relay
* Temperature and Humidity Sensor. ([Product page](https://www.progressiveautomations.com/products/lc-226))
* Actuator (12VDC with max. 10A current draw). ([Product page](https://www.progressiveautomations.com/products/linear-actuator-with-potentiometer?variant=18277322293315))

### Wiring diagram
![Wiring diagram](https://cdn.shopify.com/s/files/1/0061/7735/7891/files/programming-arduino.jpg?v=1626174435)
_Image from the project by Progressive Automations detailed_ [here](https://www.progressiveautomations.com/blogs/how-to/how-to-control-your-actuator-using-an-arduino-with-a-digital-temperature-and-humidity-sensor).

### Required Libraries:
* [DHT sensor library](https://www.arduino.cc/reference/en/libraries/dht-sensor-library/)

## Project Files
* `binary_actuation.ino` is the example provided by Progressive Automations. It extends or contracts the
actuator between fully open and fully closed in response to a comparison with a heat index threshold.

## Functionality
The actuator is controlled with a negative feedback loop and make it settle in some intermediate
state between open and closed that keeps the temperature and humidity near the target values.
The state will be continuously controlled by the loop to react to changes in temperature and humidity that
may occur.

