/**
 * EnvBoy X main
 */
#include <Arduino.h>

#include "log.h"
#include "global.h"
#include "configUtil/config.h"
#include "main_setup.h"
#include "main_normal.h"

bool isNormal = false;

void setup()
{
  #ifdef ESP32
  Serial.begin(115200);
  #else
  Serial.begin(74880);
  #endif

  // LED光らせないと何もI/Fがないのでここで初期化する  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_ON);
  
  while (!Serial); // Serial起動待ち
  
  Serial.println(""); // 1行目にゴミが出るので改行しないと読めない
  Serial.println("");
  Serial.println("Starting " + product_long);
  Serial.println(""); 
  Serial.println("");

  sectionlog(F("Initializing Config."));
  config = &Config::getInstance();

  sectionlog(F("Initializing FS."));
  mainlog(F("Starting config"));
  config_setup();

  mainlog(F("Checking config files"));
  isNormal = has_configured_file();

  // configが正常に読み込めて、フラグファイルがあれば通常モードで起動
  CFG_VALIDATE_RESULT validateResult = has_valid_config_file();
  if (validateResult == CFG_VALIDATE_RESULT::VALID) {
    mainlog(F("Config file is valid."));
  } else if (validateResult == CFG_VALIDATE_RESULT::NEED_UPGRADE) {
    sectionlog(F("Config file needs upgrade. upgrading..."));
    read_config();
    save_config();  // upgrade means json + default, so only saving is needed.
    sectionlog(F("Config file upgrade done!"));
  } else {
    mainlog(F("Config file validation error. dropping to setup mode."));
    isNormal = false;
  }

  // どれかボタンを押していれば強制的にセットアップモードにする
  // ここで接続されていないピンを指定するとdigitalReadの値が不定になるのでReadmeに書いておく
  for (unsigned int i = 0; i < BUTTON_COUNT; i++) {
    int buttonState = digitalRead(BUTTON_PINS[i]);
    if (buttonState == BUTTON_ON) {     // ボタンが押されていたら、ピンの値はLOW
      mainlog(F("Button is pressed. dropping to setup mode."));
      mainlog("Pressed button is GPIO " + String(BUTTON_PINS[i]));
      isNormal = false;
    }
  }


  if (!isNormal) {
    OPERATING_MODE = OPERATING_MODE_SETUP;
    sectionlog(F("Entering setup mode."));

    setup_setupmode(); 
  } else {
    OPERATING_MODE = OPERATING_MODE_NORMAL;
    sectionlog(F("Entering normal mode."));

    setup_normal();
  }

  sectionlog(F("setup done. Starting main loop"));
}
 
void loop() {
  if (!isNormal) {
    loop_setupmode(); 
  } else {
    loop_normal(); 
  }
}
