#ifndef AUDIO_H
#define AUDIO_H

#include "driver/dac.h"
#include "rom/ets_sys.h"
#include "Spiffs.h"

class Player {
public:
  static void setup(const dac_channel_t _dacChannel, const uint32_t _sampleRate);
  static void play(int index);  // char index A=0   0-255 8-bit    0-3.3v
private:
  static dac_channel_t dacChannel;
  static uint32_t sampleRate;

  static void _play(uint8_t* bytes, size_t len);
};

#endif // !AUDIO_H
