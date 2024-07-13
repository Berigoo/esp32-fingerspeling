#include <stdio.h>
#include "driver/adc_types_legacy.h"
#include "NN.h"
#include "hal/adc_types.h"
#include "model.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "freertos/FreeRTOS.h"

#define NUM_CLASSES 26

const adc1_channel_t THUMB = ADC1_CHANNEL_0;
const adc1_channel_t INDEX = ADC1_CHANNEL_1;
const adc1_channel_t MIDDLE = ADC1_CHANNEL_2;
const adc1_channel_t RING = ADC1_CHANNEL_3;
const adc1_channel_t PINKY = ADC1_CHANNEL_4;

static esp_adc_cal_characteristics_t adc1_chars;

int argmax(float** arr, size_t size){
  float temp = 0.0f;
  int index = 0;
  for(size_t i=0; i<size; i++){
    float curr = *arr[i];
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
  NN model;
  if(model.setup(converted_model_tflite)){
    printf("success setup model\n");
  }else{
    printf("failed setup model");
  }

  //adc1 used
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 0, &adc1_chars);
  adc1_config_width(ADC_WIDTH_BIT_12);

  adc1_config_channel_atten(THUMB, ADC_ATTEN_DB_11);
  adc1_config_channel_atten(INDEX, ADC_ATTEN_DB_11);
  adc1_config_channel_atten(MIDDLE, ADC_ATTEN_DB_11);
  adc1_config_channel_atten(RING, ADC_ATTEN_DB_11);
  adc1_config_channel_atten(PINKY, ADC_ATTEN_DB_11);

  // loop
  while(1){
    // 0 ~ 3.3 V
    float denominator = 4095.0f;
    float thumb = (adc1_get_raw(THUMB) / denominator); 
    float index = (adc1_get_raw(INDEX) / denominator);
    float middle = (adc1_get_raw(MIDDLE) / denominator);
    float ring = (adc1_get_raw(RING) / denominator);
    float pinky = (adc1_get_raw(PINKY) / denominator);

    printf("%f : %f : %f : %f : %f", thumb, index, middle, ring, pinky);

    model.getInputBuff()[0] = thumb;
    model.getInputBuff()[1] = thumb;
    model.getInputBuff()[2] = thumb;
    model.getInputBuff()[3] = thumb;
    model.getInputBuff()[4] = thumb;

    float* res = model.predict();
    int classIndex = argmax(&res, NUM_CLASSES);
    if(res[classIndex] < 50.0f) continue;

    // do text to speech

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
