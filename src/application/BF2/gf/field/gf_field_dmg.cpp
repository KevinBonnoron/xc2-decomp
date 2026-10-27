#include "gf/field/gf_field_dmg.h"

namespace gf {

void GfFieldDmgManager::destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

} // namespace gf
