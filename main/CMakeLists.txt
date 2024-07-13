file(GLOB AUDIOS "banks/*.h" "banks/*.cpp")
idf_component_register(SRCS "main.cpp" "NN.cpp" "NN.h" "conf.h" "model.cc" "model.h" "Audio.cpp" "Audio.h" ${AUDIOS}
                    INCLUDE_DIRS ".") 
