#include <Arduino.h>
#include "config_values.h"

// configの項目が選択式の場合の文字列表記を列挙する

const String ConfigValues::settings = "/settings.json";
const String ConfigValues::configured_file = "/config_ok.txt";

const String ConfigValues::NTP_ON = "yes"; // v47
const String ConfigValues::NTP_OFF = "no"; // v47

