#include <Arduino.h>
#include "config_names.h"

// config.html上の name （input要素の) を列挙する

const String ConfigNames::SETTING_ID = "settingId";
const String ConfigNames::SSID = "ssid";
const String ConfigNames::PASSWORD = "password";
const String ConfigNames::MDNS = "mDNS";

/** NTP */
const String ConfigNames::NTP = "ntp";
const String ConfigNames::NTP_ADDRESS = "ntpAddress";
const String ConfigNames::NTP_TIMEZONE = "ntpTimezone";

const String ConfigNames::HUE_BRIDGE_IP = "hueBridgeIp";

