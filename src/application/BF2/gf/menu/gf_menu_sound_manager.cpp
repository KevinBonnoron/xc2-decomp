#include "gf/menu/gf_menu_sound_manager.h"

namespace gf {

bool GfMenuSoundManager::isSpecInJingle(u32 id) {
  switch (id) {
  case 0xc:
  case 0xd:
  case 0x12:
    return true;
  default:
    return false;
  }
}

bool GfMenuSoundManager::isSpecOutJingle(u32 id) {
  switch (id) {
  case 0xc:
  case 0xd:
  case 0x12:
    return true;
  default:
    return false;
  }
}

} // namespace gf
