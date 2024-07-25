#include "NN.h"

NN& NN::getInstance(){
  static NN instance;
  return instance;
}

bool NN::setup(const void* buf){
  // map model
  model = tflite::GetModel(buf);
  if(model->version() != TFLITE_SCHEMA_VERSION){
    ESP_LOGE("TF", "Model provided is schema version %" PRIu32 "not equal to supported version %d", model->version(), TFLITE_SCHEMA_VERSION);
    return false;
  }

  // retrieve ops
  if(resolverCheck(resolver.AddSoftmax())) return false;
  if(resolverCheck(resolver.AddRelu())) return false;
  if(resolverCheck(resolver.AddFullyConnected())) return false;

  // create interpreter
  interpreter = new tflite::MicroInterpreter(model, resolver, tensorArenaBuff, K_TENSOR_ARENA_SIZE);
  if(interpreter->AllocateTensors() != kTfLiteOk){
    ESP_LOGE("TF", "Failed to allocate tensors");
    return false;
  }

  // retrieve pointer 1 sample input and 1 sample output
  input = interpreter->input(0);      
  output = interpreter->output(0);    

  // info
  ESP_LOGI("TF", "Memory allocated %zu bytes, heap memory left %" PRIu32, interpreter->arena_used_bytes(), esp_get_free_heap_size());

  return true;
}

bool NN::resolverCheck(TfLiteStatus in){
  return (in != kTfLiteOk);
}

float* NN::getInputBuff(){
  return input->data.f;
}

float* NN::predict(){
  ESP_LOGI("TF", "Predicting features (%f, %f, %f, %f, %f)", getInputBuff()[0], getInputBuff()[1], getInputBuff()[2], getInputBuff()[3], getInputBuff()[4]);
  interpreter->Invoke();
  return output->data.f;
}
