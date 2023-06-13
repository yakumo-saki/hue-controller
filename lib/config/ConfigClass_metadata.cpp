#include <Arduino.h>
#include <unordered_map>

#include "ConfigClass.h"

#include "log.h"
#include "config_names.h"
#include "config_values.h"

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
    this->addMeta(meta);
  }
  {
    ConfigMeta meta;
    meta.key = ConfigNames::SSID;
    meta.type = ConfigValueType::String;
    meta.flags = RunningConfigChangeFlags::REBOOT_REQ; // v46 BLOCKED to REBOOT_REQ
    this->addMeta(meta);
  }
  {
    ConfigMeta meta;
    meta.key = ConfigNames::PASSWORD;
    meta.type = ConfigValueType::String;
    meta.flags = RunningConfigChangeFlags::REBOOT_REQ; // v46 BLOCKED to REBOOT_REQ
    this->addMeta(meta);
  }
  {
    ConfigMeta meta;
    meta.key = ConfigNames::MDNS;
    meta.type = ConfigValueType::String;
    meta.flags = RunningConfigChangeFlags::MDNS_RESTART_REQ;
    this->addMeta(meta);
  }
  { // v47
    ConfigMeta meta;
    meta.key = ConfigNames::NTP;
    meta.type = ConfigValueType::Choise;
    meta.flags = RunningConfigChangeFlags::REBOOT_REQ;
    meta.validValues = std::vector<String> {ConfigValues::NTP_ON, ConfigValues::NTP_OFF};
    this->addMeta(meta);
  }
  { // v47
    ConfigMeta meta;
    meta.key = ConfigNames::NTP_ADDRESS;
    meta.type = ConfigValueType::String;
    meta.flags = RunningConfigChangeFlags::REBOOT_REQ;
    this->addMeta(meta);
  }
  { // v47
    ConfigMeta meta;
    meta.key = ConfigNames::NTP_TIMEZONE;
    meta.type = ConfigValueType::String;
    meta.flags = RunningConfigChangeFlags::REBOOT_REQ;
    this->addMeta(meta);
  }
}
