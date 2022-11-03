// Adafruit IO Digital Output Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-output
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

// digital pin 5
#define LED_PIN1 D0

#define LED_PIN2 D1

// set up the 'digital' feed
#define MOTOR_PIN D2

// set up the 'motor' feed
AdafruitIO_Feed *motor = io.feed("motor");
AdafruitIO_Feed *led1 = io.feed("led1");
AdafruitIO_Feed *led2 = io.feed("led2");
AdafruitIO_Feed *ldr = io.feed("ldr");

void setup() {
  
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
    #if defined(ARDUINO_ARCH_ESP32)
    // ESP32 pinMode()
    ledcAttachPin(MOTOR_PIN, 1);
    ledcSetup(1, 1200, 8);
  #else
    pinMode(MOTOR_PIN, OUTPUT);
  #endif
  
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'digital' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  motor->onMessage(handleMessage3);
  led1->onMessage(handleMessage1);
  led2->onMessage(handleMessage2);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  led1->get();
  led2->get();
  motor->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  Serial.print("sending -> ");
  int count=analogRead(A0);
  Serial.println(count);
  ldr->save(count);

  


  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);

}

// this function is called whenever an 'digital' feed message
// is received from Adafruit IO. it was attached to
// the 'digital' feed in the setup() function above.
void handleMessage1(AdafruitIO_Data *data) {

  Serial.print("received <- ");

  if(data->toPinLevel() == HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");


  digitalWrite(LED_PIN1, data->toPinLevel());
}
void handleMessage2(AdafruitIO_Data *data) {

  Serial.print("received <- ");

  if(data->toPinLevel() == HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");


  digitalWrite(LED_PIN2, data->toPinLevel());
}
void handleMessage3(AdafruitIO_Data *data) {

  // convert the data to integer
  int reading = data->toInt();

  Serial.print("received <- ");
  Serial.println(reading);

  
  // write the current 'reading' to the led
  #if defined(ARDUINO_ARCH_ESP32)
    ledcWrite(1, reading); // ESP32 motorWrite()
  #else
    analogWrite(MOTOR_PIN, reading);
  #endif

}
