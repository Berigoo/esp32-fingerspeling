#include <stdio.h>
#include "driver/adc_types_legacy.h"
#include "NN.h"
#include "hal/adc_types.h"
#include "model.h"
#include "driver/adc.h"
#include "driver/dac.h"
#include "esp_adc_cal.h"
#include "freertos/FreeRTOS.h"
#include "Audio.h"

#define NUM_CLASSES 26
#define SAMPLE_RATE 44100

const adc1_channel_t THUMB = ADC1_CHANNEL_0;
const adc1_channel_t INDEX = ADC1_CHANNEL_1;
const adc1_channel_t MIDDLE = ADC1_CHANNEL_2;
const adc1_channel_t RING = ADC1_CHANNEL_3;
const adc1_channel_t PINKY = ADC1_CHANNEL_4;

const dac_channel_t AUDIO = DAC_CHANNEL_1;

static esp_adc_cal_characteristics_t adc1_chars;

int argmax(float* arr, size_t size){
  float temp = 0.0f;
  int index = 0;
  for(size_t i=0; i<size; i++){
    float curr = arr[i];
    if(curr > temp){
      temp = curr;
      index = i;
    }
  }

  return index;
}

extern "C" void app_main(void)
{
  // setup
  if(NN::getInstance().setup(converted_model_tflite)){
    printf("success setup model\n");
  }else{
    printf("failed setup model\n");
  }
  
  /*printf("Setup");*/
  //adc1 used
  /*esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 0, &adc1_chars);*/
  /*adc1_config_width(ADC_WIDTH_BIT_12);*/
  /**/
  /*adc1_config_channel_atten(THUMB, ADC_ATTEN_DB_11);*/
  /*adc1_config_channel_atten(INDEX, ADC_ATTEN_DB_11);*/
  /*adc1_config_channel_atten(MIDDLE, ADC_ATTEN_DB_11);*/
  /*adc1_config_channel_atten(RING, ADC_ATTEN_DB_11);*/
  /*adc1_config_channel_atten(PINKY, ADC_ATTEN_DB_11);*/
  /**/
  /*Player::setup(AUDIO, SAMPLE_RATE);*/

  // loop
  while(1){
    // 0 ~ 3.3 V
    /*float denominator = 4095.0f;*/
    /*float thumb = (adc1_get_raw(THUMB) / denominator); */
    /*float index = (adc1_get_raw(INDEX) / denominator);*/
    /*float middle = (adc1_get_raw(MIDDLE) / denominator);*/
    /*float ring = (adc1_get_raw(RING) / denominator);*/
    /*float pinky = (adc1_get_raw(PINKY) / denominator);*/
    /**/
    /*printf("%f : %f : %f : %f : %f", thumb, index, middle, ring, pinky);*/

    float thumb = 0.89;
    float index = 0.79;
    float middle = 0.6;
    float ring = 0.6;
    float pinky = 0.5;

    NN::getInstance().getInputBuff()[0] = thumb;
    NN::getInstance().getInputBuff()[1] = index;
    NN::getInstance().getInputBuff()[2] = middle;
    NN::getInstance().getInputBuff()[3] = ring;
    NN::getInstance().getInputBuff()[4] = pinky;

    float* res = NN::getInstance().predict();
    int classIndex = argmax(res, NUM_CLASSES);
    if(res[classIndex] < 0.5f) continue;

    // do text to speech
    printf("class index %d with %f\n", classIndex, res[classIndex]);

    /*Player::play(classIndex);*/

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
