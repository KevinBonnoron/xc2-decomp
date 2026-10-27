#include "gf/field/gf_fobj_manager.h"

namespace gf {

bool GfFobjManager::isExistObj() {
  GfFobjManager *manager = get();
  if (manager->unknown4830 != 0) {
    return true;
  }

  return manager->unknown9050 != 0;
}

} // namespace gf
