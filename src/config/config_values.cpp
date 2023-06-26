#include <Arduino.h>
#include "config_values.h"

// configの項目が選択式の場合の文字列表記を列挙する

const String ConfigValues::settings = "/settings.json";
const String ConfigValues::configured_file = "/config_ok.txt";

const String ConfigValues::FLAG_YES = "yes";
const String ConfigValues::FLAG_NO = "no";

const String ConfigValues::FLAG_ON = "on";
const String ConfigValues::FLAG_OFF = "off";
