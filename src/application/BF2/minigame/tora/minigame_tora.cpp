// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/minigame/tora/minigame_tora.cpp.
#include "minigame/tora/minigame_tora.h"

namespace minigame {
namespace tora {

void minigame::get_pc_pos(int &x, int &y) {
  x = unknown3528->unknown2c;
  y = unknown3528->unknown30 + unknown3560 / 256;
}

void minigame::get_pc_dxdy(int x, int y, int &dx, int &dy) {
  dx = x - unknown3528->unknown2c;
  dy = y - unknown3528->unknown30 - unknown3560 / 256;
}

void minigame::get_coli_xy(int &x, int &y, _sTask *task) {
  x = task->unknown2c >> 8;
  y = task->unknown30 >> 8;
  x += task->unknown36;
  y += task->unknown38;
}

void minigame::get_pc_atk_xy(int &x, int &y, _sTask *task) {
  x = task->unknown2c >> 8;
  y = task->unknown30 >> 8;
  x += task->unknown58;
  y += task->unknown5a;
  x -= task->unknown5c;
  y -= task->unknown5d;
}

} // namespace tora
} // namespace minigame

template mm::mtl::PtrSingleton<minigame::tora::minigame>::~PtrSingleton();
