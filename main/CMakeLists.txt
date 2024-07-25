file(GLOB AUDIOS "../banks/*.h" "../banks/*.cpp")
idf_component_register(SRCS "main.cpp" "NN.cpp" "NN.h" "conf.h" "model.cc" "model.h"  "Spiffs.cpp" "Spiffs.h" "Audio.cpp" "Audio.h"
                    INCLUDE_DIRS ".") 
spiffs_create_partition_image(storage ../data FLASH_IN_PROJECT)
