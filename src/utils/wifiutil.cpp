#include <Arduino.h>
#include <vector>
#include <numeric>

// WiFi
#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include "log.h"
#include "global.h"
#include "util/watchdog.h"

#include "config/ConfigClass.h"
// #include "config/config.h"

std::vector<long> rssiArray;

String wl_status_t_to_string(wl_status_t wl_stat) {
    if (wl_stat == WL_NO_SHIELD) {
        return F("WL_NO_SHIELD");
    } else if (wl_stat == WL_IDLE_STATUS) {
        return F("WL_IDLE_STATUS");
    } else if (wl_stat == WL_NO_SSID_AVAIL) {
        return F("WL_NO_SSID_AVAIL");
    } else if (wl_stat == WL_SCAN_COMPLETED) {
        return F("WL_SCAN_COMPLETED");
    } else if (wl_stat == WL_CONNECTED) {
        return F("WL_CONNECTED");
    } else if (wl_stat == WL_CONNECT_FAILED) {
        return F("WL_CONNECT_FAILED");
    } else if (wl_stat == WL_CONNECTION_LOST) {
        return F("WL_CONNECTION_LOST");
    } else if (wl_stat == WL_DISCONNECTED) {
        return F("WL_DISCONNECTED");
    }

    return "UNKNOWN_STATUS";

}

bool is_wifi_connected() {
  return (WiFi.status() == WL_CONNECTED);
}

/**
 * WiFi接続する
 */
void make_sure_wifi_connected(bool haltOnFail) {
  
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  watchdog_feed();

  wifilog(F("WiFi is down or not initialized. connecting"));
  WiFi.setHostname(config->get(ConfigNames::MDNS).c_str());
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.enableAP(false);

  delay(100);
  watchdog_feed();

  int retryCount = 0;
  wifilog("ssid " + config->get(ConfigNames::SSID) + " pass " + config->get(ConfigNames::PASSWORD));
  WiFi.begin(config->get(ConfigNames::SSID).c_str(), config->get(ConfigNames::PASSWORD).c_str());
  
  while (WiFi.status() != WL_CONNECTED) {

    watchdog_feed();
    delay(300);
    retryCount++;

    if (retryCount % 10 == 0) {
      wifilog("WiFI.status() = " + wl_status_t_to_string(WiFi.status()));
      wifilog(F("Still waiting for wifi connection"));
    }
    if (retryCount % 30 == 0) {
      wifilog(F("Restarting WiFi"));
      wifilog(F("WiFi disconnect."));
      WiFi.disconnect();   
      delay(100);
      WiFi.setHostname(config->get(ConfigNames::MDNS).c_str());
      WiFi.begin(config->get(ConfigNames::SSID).c_str(), config->get(ConfigNames::PASSWORD).c_str());
      wifilog(F("RETRY connecting WiFi from start"));
    }
  }

  wifilog(F("WiFi (re) connected."));
  wifilog("IP address: " + WiFi.localIP().toString());
}


/**
 * WiFi AP モードを起動する
 */
void start_wifi_access_point() {
  byte mac[6];
  WiFi.macAddress(mac);

  // SSID は macaddress をSUFFIXする。前半はespressifのIDなので後半3つだけ
  String ssid = "_SETUP_" + product_short;
  for (int i = 3; i < 6; i++) {
    ssid += String(mac[i], HEX);
  }
  
  wifilog("SSID: " + ssid);

  WiFi.softAP(ssid.c_str());
  wifilog("WiFi AP Started. SSID=" + ssid);
}

/**
 * WiFiのIPアドレスを得る
 */
String get_wifi_ip_addr() {
  return WiFi.localIP().toString();
}

int8_t get_wifi_rssi() {

  if (WiFi.status() == WL_CONNECTED) {
    rssiArray.push_back(WiFi.RSSI());
  } else {
    rssiArray.push_back(0);
  }

  if (rssiArray.size() > 5) {
    rssiArray.erase(rssiArray.begin());
  }

  int sum = std::accumulate(rssiArray.begin(), rssiArray.end(), 0);
  int avg = sum / rssiArray.size();

  return avg;
}

void wifi_store_rssi() {
  statisticValues.rssi = get_wifi_rssi();
}
 