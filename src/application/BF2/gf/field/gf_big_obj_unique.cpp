#include "gf/field/gf_big_obj_unique.h"

#include "gf/object/gf_obj_handle.h"

namespace gf {

GfBigObjUnique::GfBigObjUnique(const CreateInfo *info) : unknown00(INVALID_HANDLE), unknown08(0) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfBigObjUnique::create(const CreateInfo &info) {
  dispose();
  unknown00 = info.unknown00;
  unknown08 = 0;
}

void GfBigObjUnique::dispose() { unknown00 = INVALID_HANDLE; }

} // namespace gf
