#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_vec3.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace idcoli {

IDColiObjGrdChar::IDColiObjGrdChar() {
  unknown88 = 0;
  unknown78 = nullptr;
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
      unknown80[i].unknowna0->~IDColiObjGrand();
    }
    unknown88 = 0;
    unknown80 = nullptr;
    if (unknown70 != nullptr) {
      mtl::MemManager::deallocate(unknown70, 0, false);
      unknown70 = nullptr;
    }
  }
}

int IDColiObjGrdChar::getWorkSize(const u8 *binary) {
  const unknown022 *info = reinterpret_cast<const unknown022 *>(binary + reinterpret_cast<const unknown002 *>(binary)->unknown0c);
  int size = info->unknown34 * sizeof(unknown019);
  if (info->unknown34 > 0) {
    const unknown025 *record = reinterpret_cast<const unknown025 *>(binary + info->unknown30 + info->unknown34 * sizeof(unknown026));
    for (int i = 0; i < info->unknown34; i++, record++) {
      size += (-size & 0xf) + IDColiObjGrand::calcGrandBufferSize(binary + record->unknown04) + sizeof(IDColiObjGrand);
    }
  }
  return size;
}

bool IDColiObjGrdChar::testLine(IDColiResult &result, const IDColiInput &input) {
  if (!unknown171(result, input)) {
    return false;
  }
  bool isHit = false;
  for (int i = 0; i < unknown88; i++) {
    const unknown019 &work = unknown80[i];
    IDColiObjGrand *grand = work.unknowna0;
    int mode = result.unknown00;
    bool hit = grand->unknown051(result, input, &work.unknown00);
    if (mode == 0) {
      if (hit) {
        return true;
      }
    } else {
      isHit |= hit;
    }
  }
  return isHit;
}

bool IDColiObjGrdChar::testRay(IDColiResult &result, const IDColiInput &input) {
  if (!unknown171(result, input)) {
    return false;
  }
  bool isHit = false;
  for (int i = 0; i < unknown88; i++) {
    const unknown019 &work = unknown80[i];
    IDColiObjGrand *grand = work.unknowna0;
    int mode = result.unknown00;
    bool hit = grand->unknown052(result, input, &work.unknown00);
    if (mode == 0) {
      if (hit) {
        return true;
      }
    } else {
      isHit |= hit;
    }
  }
  return isHit;
}

bool IDColiObjGrdChar::testSphere(IDColiResult &result, const IDColiInput &input) {
  if (!unknown171(result, input)) {
    return false;
  }
  bool isHit = false;
  for (int i = 0; i < unknown88; i++) {
    const unknown019 &work = unknown80[i];
    IDColiObjGrand *grand = work.unknowna0;
    int mode = result.unknown00;
    bool hit = grand->unknown053(result, input, false, &work.unknown00);
    if (mode == 0) {
      if (hit) {
        return true;
      }
    } else {
      isHit |= hit;
    }
  }
  return isHit;
}

bool IDColiObjGrdChar::testCapsule(IDColiResult &result, const IDColiInput &input) {
  if (!unknown171(result, input)) {
    return false;
  }
  bool isHit = false;
  for (int i = 0; i < unknown88; i++) {
    const unknown019 &work = unknown80[i];
    IDColiObjGrand *grand = work.unknowna0;
    int mode = result.unknown00;
    bool hit = grand->unknown054(result, input, false, &work.unknown00);
    if (mode == 0) {
      if (hit) {
        return true;
      }
    } else {
      isHit |= hit;
    }
  }
  return isHit;
}

bool IDColiObjGrdChar::testWallSphere(IDColiResult &result, const IDColiInput &input) {
  if (!unknown171(result, input)) {
    return false;
  }
  bool isHit = false;
  for (int i = 0; i < unknown88; i++) {
    const unknown019 &work = unknown80[i];
    IDColiObjGrand *grand = work.unknowna0;
    int mode = result.unknown00;
    bool hit = grand->unknown053(result, input, true, &work.unknown00);
    if (mode == 0) {
      if (hit) {
        return true;
      }
    } else {
      isHit |= hit;
    }
  }
  return isHit;
}

bool IDColiObjGrdChar::testWallCapsule(IDColiResult &result, const IDColiInput &input) {
  if (!unknown171(result, input)) {
    return false;
  }
  bool isHit = false;
  for (int i = 0; i < unknown88; i++) {
    const unknown019 &work = unknown80[i];
    IDColiObjGrand *grand = work.unknowna0;
    int mode = result.unknown00;
    bool hit = grand->unknown054(result, input, true, &work.unknown00);
    if (mode == 0) {
      if (hit) {
        return true;
      }
    } else {
      isHit |= hit;
    }
  }
  return isHit;
}

} // namespace idcoli
