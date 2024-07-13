#ifndef AUDIO_H
#define AUDIO_H

#include "../banks/A.h"
#include "../banks/B.h"
#include "../banks/C.h"
#include "../banks/D.h"
#include "../banks/E.h"
#include "../banks/F.h"
#include "../banks/G.h"
#include "../banks/H.h"
#include "../banks/I.h"
#include "../banks/J.h"
#include "../banks/K.h"
#include "../banks/L.h"
#include "../banks/M.h"
#include "../banks/N.h"
#include "../banks/O.h"
#include "../banks/P.h"
#include "../banks/Q.h"
#include "../banks/R.h"
#include "../banks/S.h"
#include "../banks/T.h"
#include "../banks/U.h"
#include "../banks/V.h"
#include "../banks/W.h"
#include "../banks/X.h"
#include "../banks/Y.h"
#include "../banks/Z.h"

#include "driver/dac.h"
#include "rom/ets_sys.h"

class Player {
public:
  static void setup(const dac_channel_t _dacChannel, const uint32_t _sampleRate);
  static void play(int index);  // char index A=0   0-255 8-bit    0-3.3v
private:
  static dac_channel_t dacChannel;
  static uint32_t sampleRate;

  static void _play(unsigned char* bytes, size_t len);
};

#endif // !AUDIO_H
