//
// Air Pressure delta
//
#include <Arduino.h>

#include "global.h"
#include "log.h"

void store_free_heap() {
#ifdef ESP32
    statisticValues.freeHeap = ESP.getFreeHeap();
#endif
#ifdef ESP8266
    statisticValues.freeHeap = ESP.getFreeHeap();
#endif
}
