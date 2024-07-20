#include "Audio.h"

#include "../banks/A.h"

dac_channel_t Player::dacChannel = DAC_CHAN_0;
uint32_t Player::sampleRate = 44100;

void Player::setup(const dac_channel_t _dacChannel, const uint32_t _sampleRate){
  dac_output_enable(_dacChannel);
  Player::dacChannel = _dacChannel;
  Player::sampleRate = _sampleRate;
}

void Player::play(int index){
  switch (index) {
    case 0:
      Player::_play(A_mp3, A_mp3_len);
      break;
    case 1:
      Player::_play(B_mp3, B_mp3_len);
      break;
    case 2:
      Player::_play(C_mp3, C_mp3_len);
      break;
    case 3:
      Player::_play(D_mp3, D_mp3_len);
      break;
    case 4:
      Player::_play(E_mp3, E_mp3_len);
      break;
    case 5:
      Player::_play(F_mp3, F_mp3_len);
      break;
    case 6:
      Player::_play(G_mp3, G_mp3_len);
      break;
    case 7:
      Player::_play(H_mp3, H_mp3_len);
      break;
    case 8:
      Player::_play(I_mp3, I_mp3_len);
      break;
    case 9:
      Player::_play(J_mp3, J_mp3_len);
      break;
    case 10:
      Player::_play(K_mp3, K_mp3_len);
      break;
    case 11:
      Player::_play(L_mp3, L_mp3_len);
      break;
    case 12:
      Player::_play(M_mp3, M_mp3_len);
      break;
    case 13:
      Player::_play(N_mp3, N_mp3_len);
      break;
    case 14:
      Player::_play(O_mp3, O_mp3_len);
      break;
    case 15:
      Player::_play(P_mp3, P_mp3_len);
      break;
    case 16:
      Player::_play(Q_mp3, Q_mp3_len);
      break;
    case 17:
      Player::_play(R_mp3, R_mp3_len);
      break;
    case 18:
      Player::_play(S_mp3, S_mp3_len);
      break;
    case 19:
      Player::_play(T_mp3, T_mp3_len);
      break;
    case 20:
      Player::_play(U_mp3, U_mp3_len);
      break;
    case 21:
      Player::_play(V_mp3, V_mp3_len);
      break;
    case 22:
      Player::_play(W_mp3, W_mp3_len);
      break;
    case 23:
      Player::_play(X_mp3, X_mp3_len);
      break;
    case 24:
      Player::_play(Y_mp3, Y_mp3_len);
      break;
    case 25:
      Player::_play(Z_mp3, Z_mp3_len);
      break;
    default:
      break;
  }
}

void Player::_play(unsigned char* bytes, size_t len){
  for(size_t i=0; i<len; i++){
    dac_output_voltage(Player::dacChannel, bytes[i]);

    ets_delay_us(1000000 / Player::sampleRate);
  }
}
