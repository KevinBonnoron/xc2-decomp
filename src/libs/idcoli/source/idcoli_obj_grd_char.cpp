#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "mtl/mem_manager.h"

namespace idcoli {

IDColiObjGrdChar::IDColiObjGrdChar() {
  unknown88 = 0;
  unknown78 = 0;
  unknown80 = nullptr;
  unknown70 = nullptr;
  unknown50 = mm::Vec3(1.0f, 1.0f, 1.0f);
  unknown60.x = -1.0f;
  unknown60.y = -1.0f;
  unknown60.z = -1.0f;
}

IDColiObjGrdChar::~IDColiObjGrdChar() { workClear(); }

void IDColiObjGrdChar::workClear() {
  if (unknown88 != 0) {
    for (int i = 0; i < unknown88; i++) {
      unknown80[i].unknowna0->~IDColiObj();
    }
    unknown88 = 0;
    unknown80 = nullptr;
    if (unknown70 != nullptr) {
      mtl::MemManager::deallocate(unknown70, 0, false);
      unknown70 = nullptr;
    }
  }
}

} // namespace idcoli
