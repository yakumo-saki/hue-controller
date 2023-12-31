#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include "log.h"
#include "global.h"
#include "configUtil/config.h"
#include "http_setup.h"
#include "util/wifiutil.h"
#include "i2c.h"
#include "TimerCall.h"

extern TimerCall timer;

bool led_on_off = false;
void flash_led() {
  if (led_on_off) {
    digitalWrite(LED_PIN, LED_OFF);
  } else {
    digitalWrite(LED_PIN, LED_ON);
  }
  led_on_off = !led_on_off;
}

/**
 * 初期化
 */
void setup_setupmode() {

  // configured ファイルがなければconfigを読まずにここに来るので一度configを読む。
  bool success = read_config();
  if (success) {
    mainlog("Config load successful.");
  } else {
    mainlog("Config load failed or failed partially.");
  }

  start_wifi_access_point();
  setup_http_setup();

	// Init I2C Serial
	init_i2c(I2C_SDA, I2C_SCL);

  // buttons
  for (unsigned int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }

  timer.add(flash_led, "LED_FLASH", 200);
  timer.start();
  mainlog(F("Setup complete."));
}

void loop_setupmode() {
  loop_http_setup();
  timer.loop();
  yield();
}
