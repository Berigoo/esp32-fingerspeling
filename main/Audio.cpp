#include "Audio.h"

#include "../banks/A.h"

dac_channel_t Player::dacChannel = DAC_CHAN_0;
uint32_t Player::sampleRate = 44100;

void Player::setup(const dac_channel_t _dacChannel, const uint32_t _sampleRate){
  dac_output_enable(_dacChannel);
  Player::dacChannel = _dacChannel;
  Player::sampleRate = _sampleRate;
}

void Player::play(int index){
  switch (index) {
    case 0:
      Player::_play(A_mp3, A_mp3_len);
      break;
    default:

      break;
  }
}

void Player::_play(unsigned char* bytes, size_t len){
  for(size_t i=0; i<len; i++){
    dac_output_voltage(Player::dacChannel, bytes[i]);

    ets_delay_us(1000000 / Player::sampleRate);
  }
}
