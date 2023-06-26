#include <Arduino.h>
#include <ArduinoJson.h>

// #include "config/config.h"

#include "log.h"
#include "global.h"

#include "network/webserver.h"
#include "network/api/v1/ping.h"
#include "network/api/api_util.h"
#include "network/http_utils.h"

extern HTTPWEBSERVER server;

void http_handle_stastics() {
  server.send(200, MimeType::JSON, statisticJSON);
}

void http_api_stastics_setup() {
  server.on ( "/stastics", HTTP_GET, http_handle_stastics );

  apilog("Stastics API initialized.");
}
