#include "dr/dr_res_mdo_morp_obj.h"

#include "dr/dr_mdo_morphing.h"

namespace ml {

DrResMdoMorpObj::DrResMdoMorpObj() : unknown00(0), unknown01(0), unknown02(0), unknown08(nullptr), unknown10(0) {}

DrResMdoMorpObj::~DrResMdoMorpObj() {}

void DrResMdoMorpObj::update(MdoWrkMatRes *matRes, DrResEtcPamObj *pamObj) {
  DrMdoMorphing morphing(matRes, this, pamObj);
  morphing.updateParms();
  int blend = morphing.isBlendCheck();
  if (blend == 0) {
    if (unknown01 != 0) {
      if (unknown02 != 0) {
        morphing.oldPosVertex();
      }
      unknown01 = 0;
    }
  } else {
    morphing.resetDefVertex();
    if (blend != 1) {
      morphing.blendVertex();
    }
    unknown01 = 1;
    morphing.parmsUpdate();
  }
}

u32 DrResMdoMorpObj::calcWorkSize(const u8 *resource) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(resource);
  const unknown002 *table = reinterpret_cast<const unknown002 *>(resource + header->unknown80);
  return table->unknown04 * 0x20 + sizeof(DrResMdoMorpObj);
}

void DrResMdoMorpObj::release(DrResMdoMorpObj *&morpObj) {
  if (morpObj != nullptr) {
    morpObj = nullptr;
  }
}

} // namespace ml
