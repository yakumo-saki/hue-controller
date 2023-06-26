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
    meta.validValues = std::vector<String> {ConfigValues::FLAG_YES, ConfigValues::FLAG_NO};
    meta.defaultValue = ConfigValues::FLAG_NO;
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
    meta.defaultValue = "";
    this->addMeta(meta);
  }


  // hue configs
  std::vector<String> hueConfigNames = std::vector {ConfigNames::HUE_RED, ConfigNames::HUE_GREEN, ConfigNames::HUE_BLUE,
                                    ConfigNames::HUE_BRIGHTNESS, ConfigNames::HUE_SATURATION};

  for (unsigned int i = 0; i < BUTTON_COUNT; i++) { 
    {
      ConfigMeta me;
      me.key = ConfigNames::HUE_PREFIX + String(i) + ConfigNames::HUE_POWER;
      me.type = ConfigValueType::Choise;
      me.flags = RunningConfigChangeFlags::REBOOT_REQ;
      me.validValues = std::vector<String> {ConfigValues::FLAG_ON, ConfigValues::FLAG_OFF};
      me.defaultValue = ConfigValues::FLAG_ON;
      this->addMeta(me);
    }

    // hue0ColorRed 
    for (unsigned int j = 0; j < hueConfigNames.size(); j++) {
      ConfigMeta met;
      met.key = ConfigNames::HUE_PREFIX + String(i) + hueConfigNames[j];
      met.type = ConfigValueType::Integer;
      met.flags = RunningConfigChangeFlags::REBOOT_REQ;

      if (hueConfigNames[j].indexOf("Color") > 0) {
        // button1 255,0,0 button2 0,255,0 button3 0,0,255
        if (i == j) {
          met.defaultValue = "255";
        } else {
          met.defaultValue = "0";
        }
      } else {
        // saturation, brightness are always default 255
        met.defaultValue = "255";
      }
      this->addMeta(met);
    }
  }

}
