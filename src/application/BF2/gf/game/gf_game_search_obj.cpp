#include "gf/game/gf_game_search_obj.h"

namespace gf {

void GfGameSearchObj::initialize(const GfSetupParam &) { unknown9097c = true; }

bool GfGameSearchObj::isInitialized() {
  GfGameSearchObj *search = get();
  if (search != nullptr) {
    return search->unknown9097c;
  }
  return false;
}

GfSearchInfo *GfGameSearchObj::getInfo(GF_SEARCH_OBJ *searchObj) {
  GfGameSearchObj *search = get();
  if (searchObj != INVALID_SEARCH_OBJ && search != nullptr) {
    return &search->unknown2428[reinterpret_cast<u64>(searchObj) & 0x3f];
  }
  return nullptr;
}

GF_OBJ_HANDLE *GfGameSearchObj::getObj(GF_SEARCH_OBJ *searchObj) {
  GfSearchInfo *infos = get()->unknown2428;
  return infos[reinterpret_cast<u64>(searchObj) & 0x3f].unknown78;
}

bool GfGameSearchObj::isEnable(GF_SEARCH_OBJ *searchObj) {
  GfGameSearchObj *search = get();
  if (searchObj != INVALID_SEARCH_OBJ && search != nullptr) {
    return (search->unknown2428[reinterpret_cast<u64>(searchObj) & 0x3f].unknown80 & 1) == 0;
  }
  return false;
}

u64 GfGameSearchObj::createHandle(u32 index) {
  u32 serial = unknown90978;
  unknown90978 = serial + 1;
  if (serial >= 0x3ffffff) {
    serial++;
    unknown90978 = serial + 1;
  }
  return (index & 0x3f) | (serial << 6);
}

} // namespace gf
