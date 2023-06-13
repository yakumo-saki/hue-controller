#include <Arduino.h>
#include <ArduinoJson.h>
#include <TimerCall.h>

#include "halt.h"
#include "config/config.h"
#include "ConfigClass.h"
#include "global.h"
#include "http_normal.h"
#include "i2c.h"
#include "log.h"
#include "main_normal_mqtt.h"
#include "mdns_client.h"
#include "sensors/freeHeap.h"
#include "sensors/statistic.h"
#include "util/watchdog.h"
#include "util/wifiutil.h"
#include "network/time_client.h"

WiFiClient net;

extern TimerCall timer;
extern String statisticJSON;

void init_sensors() {
  sectionlog(F("Initializing sensors start."));

  sectionlog(F("Initializing sensors done."));
}

// センサー読み込み以外のタスクをタイマーに追加する
void add_timer_tasks() {
  timer.add(wifi_store_rssi, "WIFI_RSSI", 1000);

  timer.add(store_free_heap, "FREE_HEAP", 15000);
  if (DEBUG_BUILD) {
    timer.addStasticsFunction(updateStastics, "STAT", 15000);
  } else {
    timer.addStasticsFunction(updateStastics, "STAT", 60000);
  }
}

/**
 * 通常起動モードのSETUP
 */
void setup_normal() {
  // Init I2C Serial
  init_i2c(I2C_SDA, I2C_SCL);

  bool config_ok = read_config();

  sectionlog(F("Setup display"));

  if (!config_ok) {
    mainlog("[MAYBE BUG] Config read failed dropping to setup mode");
    remove_configure_flag_file();
    halt("config err", "setup again", "Reset now");
  }

  sectionlog(F("Start watchdog"));
  setup_watchdog();

  // setupモードに入りやすくするための処理(deprecated)
  if (config->get(ConfigNames::DISPLAY_RECONFIG) == ConfigValues::DISPLAY_RECONFIG_ON) {
    sectionlog(F("Reset to reconfig start."));
    remove_configure_flag_file();

    // 設定済みフラグファイルを再作成
    create_configure_flag_file();

    sectionlog(F("Reconfigure timeout. continue."));
  } else {
    sectionlog(F("Wait for reconfigure skipped by config."));
  }

  // start WiFi
  sectionlog(F("Connecting WiFi."));
  make_sure_wifi_connected(true);

  mdns_setup();

  sectionlog(F("Starting HTTP server."));
  http_setup_normal();

  mainlog("TimerCall version: " + String(timer.VERSION, 2));
  init_sensors();
  
  if (config->getAsBoolean(ConfigNames::NTP)) {
    ntp_setup();

    cfglog("NTP is Enabled.");
  } else {
    cfglog("NTP is disabled.");
  }

  // TimerCall
  add_timer_tasks();
  timer.forceRunStasticsOnce();

}

/**
 * LOOP
 */
void loop_normal() {
  // sectionlog("loop start");
  watchdog_feed();

  // WiFiが繋がってなければ意味がないので接続チェック
  make_sure_wifi_connected(false);

  // mainlog("WiFi connected. IP=" + get_wifi_ip_addr());

  timer.start();
  timer.loop();

  http_loop_normal();

  // mainlog("Wait for Next tick.");
  yield();
  watchdog_feed();
}
