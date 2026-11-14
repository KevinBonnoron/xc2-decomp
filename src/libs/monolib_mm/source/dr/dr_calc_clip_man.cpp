#include "dr/dr_calc_clip_man.h"

#include <string.h>

#include "dr/dr_calc_clip_obj.h"
#include "dr/dr_calc_cp_plane_obj.h"
#include "dr/dr_man.h"
#include "ml/critical_section.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

DrCalcClipMan::DrCalcClipMan(DrMan *man, DrCalcViewWork *viewWork)
    : unknown00(man), unknown08(viewWork), unknown10(), unknown20(), unknown40(), unknown50(), unknown70(nullptr), unknown78(0), unknown7c(0) {}

DrCalcClipMan::~DrCalcClipMan() { release(); }

void DrCalcClipMan::release() {
  unknown10.unknown012();
  for (int i = 0; i < 2; i++) {
    unknown20[i].unknown012();
  }
  unknown40.unknown012();
  for (int i = 0; i < 2; i++) {
    unknown50[i].unknown012();
  }
  if (unknown70 != nullptr) {
    mtl::MemManager::deallocate(unknown70, 0, false);
    unknown70 = nullptr;
  }
}

void DrCalcClipMan::update() {
  int index = DrMan::s_nDblIdx;
  unknown7c &= ~6;
  DrCalcClipObj *pendingObject = unknown20[index].unknown00;
  while (pendingObject != nullptr) {
    DrCalcClipObj *next = pendingObject->unknown08;
    unknown10.unknown010(pendingObject);
    unknown7c |= 1;
    pendingObject = next;
  }
  unknown20[index].unknown00 = nullptr;
  unknown20[index].unknown08 = nullptr;
  if (unknown7c & 1) {
    calcBitTbl();
  }
  if (unknown78 != 0) {
    memset(unknown70, 0, unknown78);
    DrCalcClipObj *object = unknown10.unknown00;
    while (object != nullptr) {
      if (!(object->unknown3c & (1 << index))) {
        object->update(unknown08, unknown70);
        if (object->unknown3c & 4) {
          unknown7c |= 2;
        }
        if (object->unknown3c & 8) {
          unknown7c |= 4;
        }
        object = object->unknown08;
      } else {
        DrCalcClipObj *next = object->unknown08;
        unknown10.unknown011(object);
        delete object;
        unknown7c |= 1;
        object = next;
      }
    }
  }
  DrCalcCpPlaneObj *pendingPlane = unknown50[index].unknown00;
  while (pendingPlane != nullptr) {
    DrCalcCpPlaneObj *next = pendingPlane->unknown08;
    unknown40.unknown010(pendingPlane);
    pendingPlane = next;
  }
  unknown50[index].unknown00 = nullptr;
  unknown50[index].unknown08 = nullptr;
  DrCalcCpPlaneObj *plane = unknown40.unknown00;
  while (plane != nullptr) {
    DrCalcCpPlaneObj *next;
    if (!(plane->unknown40 & (1 << index))) {
      plane->update(unknown08);
      next = plane->unknown08;
    } else {
      next = plane->unknown08;
      unknown40.unknown011(plane);
      delete plane;
    }
    plane = next;
  }
}

void DrCalcClipMan::calcBitTbl() {
  unknown7c &= ~1;
  int count = 0;
  for (DrCalcClipObj *object = unknown10.unknown00; object != nullptr; object = object->unknown08) {
    if (count < object->unknown38) {
      count = object->unknown38;
    }
  }
  if (count != 0) {
    int size = (count / 32 + 1) * 4;
    size += (32 - size % 32) % 32;
    if (unknown78 == size) {
      return;
    }
    if (unknown70 != nullptr) {
      mtl::MemManager::deallocate(unknown70, 0, false);
      unknown70 = nullptr;
    }
    unknown78 = size;
    unknown70 = static_cast<u32 *>(mtl::MemManager::allocate(unknown00->unknown14, size, 0x20, false, "no name", 0));
    return;
  }
  if (unknown70 != nullptr) {
    mtl::MemManager::deallocate(unknown70, 0, false);
    unknown70 = nullptr;
  }
  unknown78 = 0;
}

bool DrCalcClipMan::testObjectClip(const mm::Vec3 &position, f32 radius) {
  for (DrCalcClipObj *object = unknown10.unknown00; object != nullptr; object = object->unknown08) {
    if (object->testObjectClip(position, radius, unknown70)) {
      return true;
    }
  }
  return false;
}

bool DrCalcClipMan::testPlaneClip(const mm::Vec3 &position, f32 radius) {
  for (DrCalcCpPlaneObj *plane = unknown40.unknown00; plane != nullptr; plane = plane->unknown08) {
    if (!plane->testClip(position, radius)) {
      return false;
    }
  }
  return true;
}

DrCalcClipObj *DrCalcClipMan::createClipObj(const void *data) {
  CS lock(DrMan::getCriticalSection());
  DrCalcClipObj *object = new (unknown00->unknown0c) DrCalcClipObj(data, unknown00);
  unknown20[DrMan::s_nDblStockIdx].unknown010(object);
  return object;
}

DrCalcCpPlaneObj *DrCalcClipMan::createCpPlaneObj(const void *data) {
  CS lock(DrMan::getCriticalSection());
  DrCalcCpPlaneObj *plane = new (unknown00->unknown0c) DrCalcCpPlaneObj(data);
  unknown50[DrMan::s_nDblStockIdx].unknown010(plane);
  return plane;
}

} // namespace ml

// The game builds the clip objects in the same unit: DrCalcClipMan::update inlines DrCalcClipObj::update and the constructors are inlined into the create functions.
#include "dr_calc_clip_obj.cpp"
#include "dr_calc_cp_plane_obj.cpp"
