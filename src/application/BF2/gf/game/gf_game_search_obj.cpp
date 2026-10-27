#include "gf/game/gf_game_search_obj.h"

namespace gf {

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

} // namespace gf
