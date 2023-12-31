#pragma once

#include <Arduino.h>

/**
 * Configで使用する値の定数クラス。
 * HTML上の name要素だったり、JSONのキー（＝APIのキー）に使われる名前は ConfigNamesにある
 */
class ConfigValues {
  public:
    static const String settings;
    static const String configured_file;

    static const String SETTING_ID;

    static const String FLAG_YES;
    static const String FLAG_NO;

    static const String FLAG_ON;
    static const String FLAG_OFF;

};
