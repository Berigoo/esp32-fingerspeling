#ifndef NN_H
#define NN_H

#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "conf.h"



class NN {
public:
  ~NN() = default;

  static NN& getInstance();

  bool setup(const void* buf);
  float* getInputBuff();
  float* predict();
private:
  NN() = default;
  NN(const NN&) = delete;
  void operator=(const NN&) = delete;

  tflite::MicroMutableOpResolver<3> resolver;
  tflite::MicroInterpreter* interpreter;
  TfLiteTensor* input;
  TfLiteTensor* output;
  const tflite::Model* model;
  uint8_t tensorArenaBuff[K_TENSOR_ARENA_SIZE];


  bool resolverCheck(TfLiteStatus in);
};


#endif // !NN_H
