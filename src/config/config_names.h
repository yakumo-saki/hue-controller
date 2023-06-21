#pragma once

#include <Arduino.h>

// memo
// Add new config
// config_names.h (variable names only)
// config_names.cpp (name attribute of config.html)
// config_values.h (variable names only)
// config_values.cpp (value of choice candicate)
// ConfigClass_metadata.cpp
// ConfigClass_defaultValue.cpp
/**
 * Configで使用される、名称の定数クラス。
 * 実際の値は ConfigValue クラスにある
 */
class ConfigNames {
  public:
    static const String SETTING_ID;
    static const String SSID;
    static const String PASSWORD;
    static const String MDNS;

    static const String NTP;
    static const String NTP_ADDRESS;
    static const String NTP_TIMEZONE;

    static const String HUE_BRIDGE_IP;

    // NEED Prefix or suffix
    static const String HUE_PREFIX;

    static const String HUE_RED;
    static const String HUE_GREEN;
    static const String HUE_BLUE;
    static const String HUE_BRIGHTNESS;
    static const String HUE_SATURATION;
    static const String HUE_POWER;

};
