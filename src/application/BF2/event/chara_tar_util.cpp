#include "event/chara_tar_util.h"

#include "bdat.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"

namespace event {

mm::Vec3 CharaTarUtil::getCharaDefaultEyeVec(gf::GF_OBJ_HANDLE *handle) {
  if (handle != gf::INVALID_HANDLE) {
    switch (gf::GfObjUtil::getEyeRotControl(handle)) {
    case 1:
    case 4:
    case 6:
    case 7:
      return mm::Vec3(1.0f, 0.0f, 0.0f);
    }
  }
  return mm::Vec3(0.0f, 1.0f, 0.0f);
}

const char *CharaTarUtil::aimmotType2stat(int type) {
  return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_aimmottype"), "stat", type, 7));
}

const char *CharaTarUtil::aimmotType2name(int type) {
  return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_aimmottype"), "name", type, 7));
}

} // namespace event
