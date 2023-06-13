#pragma once

#include <Arduino.h>
#include "config_values.h"

typedef struct {
  int rssi = 0;        // not sensor value. get from wifi
  uint32_t freeHeap;   // not sensor value. get from ESP
} values_t;
