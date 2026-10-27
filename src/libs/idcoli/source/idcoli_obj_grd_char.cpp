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

void IDColiObjGrdChar::update() {
  unknown50 = mm::Vec3(-1000000.0f, -1000000.0f, -1000000.0f);
  unknown60 = mm::Vec3(1000000.0f, 1000000.0f, 1000000.0f);
  for (int i = 0; i < unknown88; i++) {
    const IDCmfPosData &posData = unknown80[i].unknown00;
    if (unknown50.x < posData.unknown80.x) {
      unknown50.x = posData.unknown80.x;
    }
    if (unknown60.x > posData.unknown90.x) {
      unknown60.x = posData.unknown90.x;
    }
    if (unknown50.y < posData.unknown80.y) {
      unknown50.y = posData.unknown80.y;
    }
    if (unknown60.y > posData.unknown90.y) {
      unknown60.y = posData.unknown90.y;
    }
    if (unknown50.z < posData.unknown80.z) {
      unknown50.z = posData.unknown80.z;
    }
    if (unknown60.z > posData.unknown90.z) {
      unknown60.z = posData.unknown90.z;
    }
  }
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
