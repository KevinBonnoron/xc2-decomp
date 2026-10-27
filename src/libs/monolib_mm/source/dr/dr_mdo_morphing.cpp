#include "dr/dr_mdo_morphing.h"

#include "dr/dr_res_etc_params.h"
#include "dr/dr_res_mdo_morp_obj.h"

namespace ml {

DrMdoMorphing::DrMdoMorphing(MdoWrkMatRes *matRes, DrResMdoMorpObj *morpObj, DrResEtcPamObj *pamObj) : unknown00(matRes), unknown08(morpObj), unknown10(pamObj) {}

DrMdoMorphing::~DrMdoMorphing() {}

void DrMdoMorphing::updateParms() {
  if (unknown08->unknown00 != 0) {
    return;
  }
  unknown1c = -1;
  for (u32 i = 0; i < unknown08->unknown10; i++) {
    DrResMdoMorpObj::unknown004 &entry = unknown08->unknown08[i];
    u32 description = entry.unknown18->unknown08;
    if ((description & 0xffff) == 7) {
      entry.unknown00 = unknown10->unknown10[description >> 16].getParams();
    }
  }
}

int DrMdoMorphing::isBlendCheck() const {
  int result = 0;
  int state = 0;
  for (u32 i = 0; i < unknown08->unknown10; i++) {
    const DrResMdoMorpObj::unknown004 &entry = unknown08->unknown08[i];
    if (entry.unknown04 == entry.unknown00) {
      if (entry.unknown00 != 0.0f) {
        state = 2;
        if (result == 1) {
          return 2;
        }
      }
    } else {
      if (state == 2) {
        return 2;
      }
      if (entry.unknown00 != 0.0f) {
        return 2;
      }
      result = 1;
    }
  }
  return result;
}

void DrMdoMorphing::parmsUpdate() {
  for (u32 i = 0; i < unknown08->unknown10; i++) {
    unknown08->unknown08[i].unknown04 = unknown08->unknown08[i].unknown00;
  }
}

} // namespace ml
