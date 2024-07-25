#ifndef CONF_H
#define CONF_H

#include "driver/adc_types_legacy.h"
#include "driver//dac_types.h"

#define K_TENSOR_ARENA_SIZE 30 * 1024
#define NUM_CLASSES 26

inline const adc1_channel_t THUMB = ADC1_CHANNEL_0;
inline const adc1_channel_t INDEX = ADC1_CHANNEL_1;
inline const adc1_channel_t MIDDLE = ADC1_CHANNEL_2;
inline const adc1_channel_t RING = ADC1_CHANNEL_3;
inline const adc1_channel_t PINKY = ADC1_CHANNEL_4;

inline const dac_channel_t AUDIO = DAC_CHAN_0;

inline const uint32_t SAMPLE_RATE = 41100;

#endif // !CONF_H
