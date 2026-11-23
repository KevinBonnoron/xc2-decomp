#include "dr/dr_shd_fetch_man.h"

#include "dr/dr_shd_fetch_obj.h"

namespace ml {

DrShdFetchMan::DrShdFetchMan(DrMan *drMan) : unknown00(nullptr), unknown08(nullptr), m_drMan(drMan), unknown18(0) {}

DrShdFetchMan::~DrShdFetchMan() {
  DrShdFetchObj *obj = unknown00;
  while (obj != nullptr) {
    DrShdFetchObj *next = obj->unknown08;
    delete obj;
    obj = next;
  }
  unknown00 = nullptr;
  unknown08 = nullptr;
}

void DrShdFetchMan::releaseFetchObj(DrShdFetchObj *obj) {
  obj->unknown1c--;
  if (obj->unknown1c < 0) {
    obj->unknown1c = 0;
  }
  if (obj->unknown1c <= 0) {
    if (obj->unknown00 != nullptr) {
      if (obj->unknown08 != nullptr) {
        obj->unknown00->unknown08 = obj->unknown08;
        obj->unknown08->unknown00 = obj->unknown00;
      } else {
        unknown08 = obj->unknown00;
        unknown08->unknown08 = nullptr;
      }
    } else if (obj->unknown08 != nullptr) {
      unknown00 = obj->unknown08;
      unknown00->unknown00 = nullptr;
    } else {
      unknown00 = nullptr;
      unknown08 = nullptr;
    }
    obj->unknown00 = nullptr;
    obj->unknown08 = nullptr;
    delete obj;
    unknown18--;
  }
}

} // namespace ml
