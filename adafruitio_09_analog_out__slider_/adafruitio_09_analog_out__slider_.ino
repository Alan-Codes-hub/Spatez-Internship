// Adafruit IO led4 Out Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-led4-output
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// this should correspond to a pin with PWM capability
#define LED_PIN D0

// set up the 'led4' feed
AdafruitIO_Feed *led4 = io.feed("led4");

void setup() {

  // set up led pin as an led4 output
  #if defined(ARDUINO_ARCH_ESP32)
    // ESP32 pinMode()
    ledcAttachPin(LED_PIN, 1);
    ledcSetup(1, 1200, 8);
  #else
    pinMode(LED_PIN, OUTPUT);
  #endif

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'led4' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  led4->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  led4->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

}

// this function is called whenever an 'led4' message
// is received from Adafruit IO. it was attached to
// the led4 feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  // convert the data to integer
  int reading = data->toInt();

  Serial.print("received <- ");
  Serial.println(reading);

  
  // write the current 'reading' to the led
  #if defined(ARDUINO_ARCH_ESP32)
    ledcWrite(1, reading); // ESP32 led4Write()
  #else
    analogWrite(LED_PIN, reading);
  #endif

}
