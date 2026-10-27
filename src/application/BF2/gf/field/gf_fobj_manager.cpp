#include "gf/field/gf_fobj_manager.h"

namespace gf {

bool GfFobjManager::isInitialized() {
  GfFobjManager *manager = get();
  if (manager != nullptr) {
    return manager->unknown9058;
  }
  return false;
}

void GfFobjManager::gevGameObjLeave(GF_OBJ_HANDLE *handle) { leaveGameField(handle); }

GfDropitemParams *GfFobjManager::getDropitemParams() {
  GfFobjManager *manager = get();
  if (manager != nullptr) {
    return manager->unknown9060;
  }
  return nullptr;
}

bool GfFobjManager::isExistObj() {
  GfFobjManager *manager = get();
  if (manager->unknown4830 != 0) {
    return true;
  }

  return manager->unknown9050 != 0;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFobjManager>::~PtrSingleton();
