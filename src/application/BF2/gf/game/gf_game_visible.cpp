#include "gf/game/gf_game_visible.h"

namespace gf {

void GfGameVisible::destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void GfGameVisible::cleanup() {}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameVisible>::~PtrSingleton();
