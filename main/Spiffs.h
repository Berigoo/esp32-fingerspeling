#pragma once

#include <cstdint>
#ifndef MAIN_SPIFFS_H
#define MAIN_SPIFFS_H

#include "esp_spiffs.h"
#include "esp_log.h"
#include "esp_system.h"

class Spiffs {
public:
  ~Spiffs() = default;

  static Spiffs& getInstance();
  
  void mount(const char* mountPoint);
  void readFile(char* filename, size_t* bufferSize, uint8_t** buffer); 
private:
  bool isMounted = false;
  const char* mountPoint = "NULL";

  Spiffs() = default;
  Spiffs(const Spiffs&) = delete;
  void operator=(const Spiffs&) = delete;
};

#endif //MAIN_SPIFFS_H
