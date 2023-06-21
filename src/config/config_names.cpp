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

// prefixをつけるので最初が大文字になっている。
// ex hue1
const String ConfigNames::HUE_PREFIX = "hue";

const String ConfigNames::HUE_RED = "ColorRed";
const String ConfigNames::HUE_GREEN = "ColorGreen";
const String ConfigNames::HUE_BLUE = "ColorBlue";
const String ConfigNames::HUE_BRIGHTNESS = "Brightness";
const String ConfigNames::HUE_SATURATION= "Saturation";
const String ConfigNames::HUE_POWER= "Power";
