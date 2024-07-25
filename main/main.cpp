#include <stdio.h>
#include "driver/adc_types_legacy.h"
#include "NN.h"
#include "hal/adc_types.h"
#include "model.h"
#include "driver/adc.h"
#include "driver/dac.h"
#include "esp_adc_cal.h"
#include "freertos/FreeRTOS.h"
#include "conf.h"
#include "Audio.h"
#include "esp_log.h"
#include "Spiffs.h"
#include "rom/ets_sys.h"

#define TAG "MAIN"

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
  ESP_LOGI("MAIN", "\nSetup...");
  // setup
  if(NN::getInstance().setup(converted_model_tflite)){
    ESP_LOGI(TAG, "Success setup model");
  }else{
    ESP_LOGE(TAG, "Failed setup model");
  }
  
  Player::setup(AUDIO, SAMPLE_RATE);
  Spiffs::getInstance().mount("/fs");

  //adc1 used
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 0, &adc1_chars);
  adc1_config_width(ADC_WIDTH_BIT_12);

  adc1_config_channel_atten(THUMB, ADC_ATTEN_DB_11);
  adc1_config_channel_atten(INDEX, ADC_ATTEN_DB_11);
  adc1_config_channel_atten(MIDDLE, ADC_ATTEN_DB_11);
  adc1_config_channel_atten(RING, ADC_ATTEN_DB_11);
  adc1_config_channel_atten(PINKY, ADC_ATTEN_DB_11);


  NN& nn = NN::getInstance();
  // loop
  while(1){
    // 0 ~ 3.3 V
    float denominator = 4095.0f;
    float thumb = (adc1_get_raw(THUMB) / denominator); 
    float index = (adc1_get_raw(INDEX) / denominator);
    float middle = (adc1_get_raw(MIDDLE) / denominator);
    float ring = (adc1_get_raw(RING) / denominator);
    float pinky = (adc1_get_raw(PINKY) / denominator);

    nn.getInputBuff()[0] = thumb;
    nn.getInputBuff()[1] = index;
    nn.getInputBuff()[2] = middle;
    nn.getInputBuff()[3] = ring;
    nn.getInputBuff()[4] = pinky;

    float* res = NN::getInstance().predict();
    int classIndex = argmax(res, NUM_CLASSES);

    ESP_LOGI("MAIN", "Class index: %d; with probability %f", classIndex, res[classIndex]);

    if(res[classIndex] < 0.5f) continue;

    Player::play(classIndex);

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
