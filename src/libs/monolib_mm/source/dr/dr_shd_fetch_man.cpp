#include "dr/dr_shd_fetch_man.h"

#include "dr/dr_shd_fetch_obj.h"

namespace ml {

DrShdFetchMan::DrShdFetchMan(DrMan *drMan) : unknown00(nullptr), unknown08(nullptr), unknown10(drMan), unknown18(0) {}

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
