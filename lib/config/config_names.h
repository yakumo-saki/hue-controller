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

    static const String NTP;                    // v47
    static const String NTP_ADDRESS;            // v47
    static const String NTP_TIMEZONE;           // v47
};
