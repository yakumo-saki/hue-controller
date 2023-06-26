
#include <Arduino.h>

#include "log.h"
#include "global.h"
// #include "config/config.h"

#include "http_normal.h"

#include "network/webserver.h"
#include "network/http_not_found.h"
#include "network/stastics_api.h"
#include "network/goto_setup_api.h"
#include "network/api/v1/ping.h"
#include "network/api/v1/config.h"
#include "network/api/v1/getdata.h"

#include "network/web/http_web_config.h"
#include "network/web/http_web_updater.h"

extern HTTPWEBSERVER server;

void http_setup_normal() {
  httplog("HTTP web server initializing");
  
  http_not_found_setup();
  http_api_gotosetup_setup();
  http_api_stastics_setup();

  http_api_ping_setup();
  // http_api_getdata_setup();
  http_api_config_setup();

  http_web_config_setup();
  http_web_updater_setup();
  
  server.begin(); 
  httplog("HTTP web server initialized");
}

void http_loop_normal() {
  server.handleClient();
}
