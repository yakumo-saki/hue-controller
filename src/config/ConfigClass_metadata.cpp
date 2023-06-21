#include <Arduino.h>
#include <unordered_map>

#include "global.h"

#include "ConfigClass.h"

#include "log.h"
#include "config/config_names.h"
#include "config/config_values.h"

/** 
 * Configのメタデータをセットする 
 * ここでセットしていない項目は存在しないものとして扱われる
 * 正直なところ、メモリの無駄ではあるのでメモリがカツカツになったら
 * 素朴な実装に切り替えても良いかもしれない。
 * このデータだけでざっと4KBくらい使用している。
 */
void Config::loadMetadata() {
  {
    ConfigMeta meta;
    meta.key = ConfigNames::SETTING_ID;
    meta.type = ConfigValueType::String;
    meta.flags = RunningConfigChangeFlags::BLOCKED;
    meta.defaultValue = "";
    this->addMeta(meta);
  }
  {
    ConfigMeta meta;
    meta.key = ConfigNames::SSID;
    meta.type = ConfigValueType::String;
    meta.flags = RunningConfigChangeFlags::REBOOT_REQ; // v46 BLOCKED to REBOOT_REQ
    meta.defaultValue = "";
    this->addMeta(meta);
  }
  {
    ConfigMeta meta;
    meta.key = ConfigNames::PASSWORD;
    meta.type = ConfigValueType::String;
    meta.flags = RunningConfigChangeFlags::REBOOT_REQ; // v46 BLOCKED to REBOOT_REQ
    meta.defaultValue = "";
    this->addMeta(meta);
  }
  {
    ConfigMeta meta;
    meta.key = ConfigNames::MDNS;
    meta.type = ConfigValueType::String;
    meta.flags = RunningConfigChangeFlags::MDNS_RESTART_REQ;
    meta.defaultValue = "espmdns";
    this->addMeta(meta);
  }
  { 
    ConfigMeta meta;
    meta.key = ConfigNames::NTP;
    meta.type = ConfigValueType::Choise;
    meta.flags = RunningConfigChangeFlags::REBOOT_REQ;
    meta.validValues = std::vector<String> {ConfigValues::NTP_ON, ConfigValues::NTP_OFF};
    meta.defaultValue = ConfigValues::NTP_OFF;
    this->addMeta(meta);
  }
  { 
    ConfigMeta meta;
    meta.key = ConfigNames::NTP_ADDRESS;
    meta.type = ConfigValueType::String;
    meta.flags = RunningConfigChangeFlags::REBOOT_REQ;
    meta.defaultValue = "";
    this->addMeta(meta);
  }
  { 
    ConfigMeta meta;
    meta.key = ConfigNames::NTP_TIMEZONE;
    meta.type = ConfigValueType::String;
    meta.flags = RunningConfigChangeFlags::REBOOT_REQ;
    meta.defaultValue = "JST-9";
    this->addMeta(meta);
  }

  { 
    ConfigMeta meta;
    meta.key = ConfigNames::HUE_BRIDGE_IP;
    meta.type = ConfigValueType::String;
    meta.flags = RunningConfigChangeFlags::REBOOT_REQ;
    this->addMeta(meta);
  }


  // hue configs
  std::vector<String> hueConfigNames = std::vector {ConfigNames::HUE_RED, ConfigNames::HUE_GREEN, ConfigNames::HUE_BLUE,
                                    ConfigNames::HUE_BRIGHTNESS, ConfigNames::HUE_SATURATION, ConfigNames::HUE_POWER};

  for (int i = 0; i < BUTTON_COUNT; i++) { 
    {
    ConfigMeta meta;
    meta.key = ConfigNames::HUE_POWER;
    meta.type = ConfigValueType::Choise;
    meta.flags = RunningConfigChangeFlags::REBOOT_REQ;
    this->addMeta(meta);
    }

    // hue0ColorRed 
    for (int j = 0; j < hueConfigNames.size(); j++) {
      ConfigMeta meta;
      meta.key = ConfigNames::HUE_PREFIX + String(i) + hueConfigNames[j];
      meta.type = ConfigValueType::Integer;
      meta.flags = RunningConfigChangeFlags::REBOOT_REQ;
      this->addMeta(meta);
    }
  }

}
