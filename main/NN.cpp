#include "NN.h"

NN& NN::getInstance(){
  static NN instance;
  return instance;
}

bool NN::setup(const void* buf){
  // map model
  model = tflite::GetModel(buf);
  if(model->version() != TFLITE_SCHEMA_VERSION){
    MicroPrintf("Model provided is schema version %d not equal to supported version %d", model->version(), TFLITE_SCHEMA_VERSION);
    return false;
  }

  // retrieve ops
  if(resolverCheck(resolver.AddSoftmax())) return false;
  if(resolverCheck(resolver.AddRelu())) return false;
  if(resolverCheck(resolver.AddFullyConnected())) return false;

  // create interpreter
  interpreter = new tflite::MicroInterpreter(model, resolver, tensorArenaBuff, K_TENSOR_ARENA_SIZE);
  if(interpreter->AllocateTensors() != kTfLiteOk){
    MicroPrintf("failed to allocate tensors");
    return false;
  }

  // retrieve pointer 1 sample input and 1 sample output
  input = interpreter->input(0);      
  output = interpreter->output(0);    

  // info
  MicroPrintf("used mems %d bytes\n", interpreter->arena_used_bytes());

  return true;
}

bool NN::resolverCheck(TfLiteStatus in){
  return (in != kTfLiteOk);
}

float* NN::getInputBuff(){
  return input->data.f;
}

float* NN::predict(){
  interpreter->Invoke();
  return output->data.f;
}
