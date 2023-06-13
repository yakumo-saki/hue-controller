#include <Arduino.h>
#include <unordered_map>

#include "ConfigClass.h"

#include "log.h"
#include "config_names.h"
#include "config_values.h"

/** 
 * 初期値をセットする 
 */
void Config::loadDefaultValue() {
  this->addConfig(ConfigNames::SETTING_ID, "");
  this->addConfig(ConfigNames::SSID, "");
  this->addConfig(ConfigNames::PASSWORD, "");

  this->addConfig(ConfigNames::MDNS, "espmdns");

  this->addConfig(ConfigNames::NTP, ConfigValues::NTP_OFF);
  this->addConfig(ConfigNames::NTP_ADDRESS, "");
  this->addConfig(ConfigNames::NTP_TIMEZONE, "JST-9");
}
