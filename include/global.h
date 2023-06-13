#include <Arduino.h>
#include <WiFiClient.h>

#include "global_MimeType.h"

#include "config_values.h"
#include "config_names.h"
#include "ConfigClass.h"

#include "structs.h"

// --------------------------------------------------------------------
// プロダクト名定数
// --------------------------------------------------------------------
extern const String product_short;
extern const String product;
extern const String ver;
extern const String minorVer;
extern const String product_long;

extern const String SETTING_ID;

extern const bool DEBUG_BUILD;

// SETUPモード OR NORMALモード
extern const int OPERATING_MODE_NORMAL;
extern const int OPERATING_MODE_SETUP;
extern int OPERATING_MODE;

// --------------------------------------------------------------------
// デバイス周りの定数
// --------------------------------------------------------------------
extern const int I2C_SDA;
extern const int I2C_SCL;

extern const byte SSD1306_I2C_ADDR;

extern int BUTTON_PINS[];
extern const int BUTTON_COUNT;
extern const int LED_PIN;

extern int BUTTON_ON;
extern int BUTTON_OFF;
extern int LED_ON;
extern int LED_OFF;


// --------------------------------------------------------------------
// 設定値保存
// --------------------------------------------------------------------
extern Config *config;

// --------------------------------------------------------------------
// センサー値関連
// --------------------------------------------------------------------

// 
extern values_t statisticValues;

// --------------------------------------------------------------------
// 統計情報
// --------------------------------------------------------------------
extern String statisticJSON;
