#include <Arduino.h>
#include <ArduinoJson.h>
#include "structs.h"
#include "TimerCall.h"
#include "config/ConfigClass.h"


// --------------------------------------------------------------------
// プロダクト名定数
// --------------------------------------------------------------------

// ebx
extern const String product_short = "HUECTRL";

// Enable debug function
extern const bool DEBUG_BUILD = false;

// EnvBoyX
// note: Also referenced by create_release.sh
extern const String product = "Hue Contoller";
extern const String ver = "0";      // Major
extern const String minorVer = "0";  // Bugfix
extern const String ver_long = " Ver." + ver + "." + minorVer;

// Setting version (version number when settings changed)
extern const String SETTING_ID = "HUE-CTRL-CFG.v1";

// EnvBoyX Ver.53.0
extern const String product_long = product + " " + (DEBUG_BUILD ? " Dev." + ver + "." + minorVer : ver_long);

// --------------------------------------------------------------------
// デバイス周りの定数
// --------------------------------------------------------------------
#ifdef ESP32
// ESP32 SDA
extern const int I2C_SDA = 21;
// ESP32 SCLu8g2Flip
extern const int I2C_SCL = 22;
#elif defined(ESP8266)
// ESP8266 SDA
extern const int I2C_SDA = 5;
// ESP8266 SCL
extern const int I2C_SCL = 4;

// ここらへんで警告がでるが無視でよい。 initialized and declared 'extern'
extern int BUTTON_PINS[] = {13, 12, 14};
extern const int BUTTON_COUNT = sizeof(BUTTON_PINS) / sizeof(int);
extern const int LED_PIN = 2;

extern int BUTTON_ON = LOW;
extern int BUTTON_OFF = HIGH;
extern int LED_ON = LOW;
extern int LED_OFF = HIGH;

#endif

// --------------------------------------------------------------------
// センサー値グローバル
// --------------------------------------------------------------------
// センサー値（グローバル）
values_t statisticValues;

// --------------------------------------------------------------------
// 統計情報
// --------------------------------------------------------------------
String statisticJSON;

// --------------------------------------------------------------------
// Config
// --------------------------------------------------------------------
Config *config;

// --------------------------------------------------------------------
// タイマー
// --------------------------------------------------------------------
TimerCall timer = TimerCall();

// --------------------------------------------------------------------
// 動作モード
// --------------------------------------------------------------------
extern const int OPERATING_MODE_NORMAL = 2;
extern const int OPERATING_MODE_SETUP = 1;
int OPERATING_MODE = 0;
