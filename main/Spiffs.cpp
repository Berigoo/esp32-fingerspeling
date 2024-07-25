#include "Spiffs.h"

Spiffs& Spiffs::getInstance(){
  static Spiffs instance;
  return instance;
}

void Spiffs::mount(const char* mountPoint){
  if(!isMounted){
    esp_vfs_spiffs_conf_t conf = {
      .base_path = mountPoint,
      .partition_label = NULL,
      .max_files = 26,
      .format_if_mount_failed = true,
    };
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if(ret != ESP_OK){
      ESP_LOGE("SPIFFS", "Failed to mount SPIFFS");
    }else{
      ESP_LOGI("SPIFFS", "Success to mount SPIFFS");
      isMounted = true;
    }
  }else{
    ESP_LOGE("SPIFFS", "SPIFFS has been mount");
  }
}

void Spiffs::readFile(char* filename, size_t* bufferSize, uint8_t** buffer){
  FILE* fp = fopen(filename, "r");
  if(!fp){
    ESP_LOGE("SPIFFS", "Failed to open file %s", filename);
    return;
  }else{
    ESP_LOGI("SPIFFS", "opening file %s", filename);
  }
  fseek(fp, 0, SEEK_END);
  *bufferSize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  ESP_LOGI("SPIFFS", "file size %zu", *bufferSize);
  *buffer = (uint8_t*)malloc(sizeof(uint8_t) * (*bufferSize));
  if(!buffer){
    ESP_LOGE("SPIFFS", "Failed to allocate buffer");
  }
  ESP_LOGI("SPIFFS", "heap memory left %" PRIu32, esp_get_free_heap_size());

  size_t n = fread(*buffer, sizeof(uint8_t), *bufferSize, fp);
  if(n != sizeof(uint8_t) * (*bufferSize)){
    ESP_LOGW("SPIFFS", "Read byte %zu of %zu", n, *bufferSize);
  }

  ESP_LOGI("SPIFFS", "closing file");
  fclose(fp);
}
