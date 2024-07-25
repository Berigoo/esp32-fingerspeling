#include "Audio.h"

dac_channel_t Player::dacChannel = DAC_CHAN_0;
uint32_t Player::sampleRate = 44100;

void Player::setup(const dac_channel_t _dacChannel, const uint32_t _sampleRate){
  ESP_LOGI("AUDIO", "Set sample rate to %" PRIu32, _sampleRate);
  dac_output_enable(_dacChannel);
  Player::dacChannel = _dacChannel;
  Player::sampleRate = _sampleRate;
}

void Player::play(int index){
  char c = (char)(65 + index);
  char filename[] = "/fs/*.wav";
  filename[4] = c;

  Spiffs& spiffs = Spiffs::getInstance();
  size_t fileSize;
  uint8_t* buffer;
  spiffs.readFile(filename, &fileSize, &buffer);
    
  ESP_LOGI("AUDIO", "file size %zu", fileSize);

  _play(buffer, fileSize);

  free(buffer);
}

void Player::_play(uint8_t* bytes, size_t len){
  ESP_LOGI("AUDIO", "Playing audio...");
  for(size_t i=0; i<len; i++){
    dac_output_voltage(Player::dacChannel, bytes[i]);

    ets_delay_us(1000000 / Player::sampleRate);
  }
  ESP_LOGI("AUDIO", "Finish playing");
}
