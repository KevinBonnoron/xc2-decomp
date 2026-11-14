#include "dr/dr_mdo_nom_after_image.h"

#include "dr/dr_creator.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_base.h"
#include "dr/dr_mdl_obj.h"
#include "dr/dr_mdo_ctl_nom.h"
#include "mm_math/mm_mat44.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

// The game builds DrMdoNomClone in the same unit, just before this class (0x710082c200), so its empty constructor and destructor are inlined here.
#include "dr_mdo_nom_clone.cpp"

namespace ml {

u32 DrMdoNomAfterImage::isReleaseCall() const { return unknown20 & (1 << DrMan::s_nDblMemIdx); }

void DrMdoNomAfterImage::update(const DrMdoCtlNom *model, f32 delta) {
  if (unknown08 != 0) {
    for (int i = 0; i < unknown08; i++) {
      // The game never sets the fourth argument's register: updateParam does not read it, so the original expression cannot be checked.
      updateParam(&unknown00[i], model, delta, model->m_offsetPos);
    }
    unknown10 += delta;
    if (unknown10 >= unknown0c) {
      unknown10 = 0.0f;
      captureObj(model);
    }
  }
}

void DrMdoNomAfterImage::releaseCall() { unknown20 |= 1 << DrMan::s_nDblStockIdx; }

void DrMdoNomAfterImage::create(const DrMdoCtlNom *model, f32 span, f32 life, f32 fade, const mm::Col3 &headColor, f32 headPower, f32 headBlackRatio, f32 headEmissive, const mm::Col3 &tailColor,
                                f32 tailPower, f32 tailBlackRatio, f32 tailEmissive) {
  release();
  unknown0a = 0;
  unknown10 = 0.0f;
  unknown0c = span;
  unknown14 = life * fade;
  unknown18 = life;
  unknown1c = 5.0f;
  unknown24 = headColor;
  unknown38 = headEmissive;
  unknown30 = headPower;
  unknown34 = headBlackRatio;
  unknown3c = tailColor;
  unknown50 = tailEmissive;
  unknown48 = tailPower;
  unknown4c = tailBlackRatio;
  unknown08 = static_cast<int>(unknown18 / unknown0c);
  if (unknown18 / unknown0c - unknown08 > 0.0001f) {
    unknown08++;
  }
  unknown00 = static_cast<wrkObjList *>(mtl::MemManager::allocate(DrMan::getIns()->unknown14, sizeof(wrkObjList) * unknown08, 0x10, false, "no name", 0));
  const char *path = nullptr;
  if (model->unknown238 != nullptr) {
    unknown54 = model->unknown238;
    path = unknown54.c_str();
  }
  DrCreator creator;
  for (int i = 0; i < unknown08; i++) {
    unknown00[i].unknown10 = static_cast<DrMdoCtlNom *>(creator.createMdl(model->unknown50, path, model->unknown1a));
    unknown00[i].unknown18 = unknown18;
    unknown00[i].unknown10->setAlpha(0.0f);
    unknown00[i].unknown10->setDisp(false);
  }
}

DrMdoNomAfterImage::DrMdoNomAfterImage() {
  unknown00 = nullptr;
  unknown08 = 0;
  unknown0a = 0;
  unknown20 = 0;
}

DrMdoNomAfterImage::~DrMdoNomAfterImage() { release(); }

void DrMdoNomAfterImage::release() {
  if (unknown08 != 0) {
    for (int i = 0; i < unknown08; i++) {
      unknown00[i].unknown10->setDeleteCall(DrMan::s_nDblStockIdx);
    }
    unknown08 = 0;
    if (unknown00 != nullptr) {
      mtl::MemManager::deallocate(unknown00, 0, false);
      unknown00 = nullptr;
    }
  }
}

void DrMdoNomAfterImage::updateParam(wrkObjList *obj, const DrMdoCtlNom *model, f32 delta, const mm::Vec3 &) {
  obj->unknown18 += delta;
  if (obj->unknown18 >= unknown18) {
    obj->unknown18 = unknown18;
    obj->unknown10->setAlpha(0.0f);
    obj->unknown10->setDisp(false);
    return;
  }
  if (unknown14 < obj->unknown18) {
    f32 alpha = (1.0f - (obj->unknown18 - unknown14) / (unknown18 - unknown14)) * model->unknowne0;
    obj->unknown10->setAlpha(model->unknowne0 * alpha);
  } else {
    obj->unknown10->setAlpha(model->unknowne0);
  }
  obj->unknown10->setDisp((model->unknown20 & DrMdlBase::unknown038_0) != 0);
  if (obj->unknown10->getRimBloomWrk(2) != nullptr) {
    f32 rate = obj->unknown18 / unknown18;
    f32 inverse = 1.0f - rate;
    unknown091 *rimBloom = obj->unknown10->getRimBloomWrk(2);
    rimBloom->unknown00 = inverse * unknown24 + rate * unknown3c;
    rimBloom->unknown14 = inverse * unknown38 + rate * unknown50;
    rimBloom->unknown0c = inverse * unknown30 + rate * unknown48;
    rimBloom->unknown10 = inverse * unknown34 + rate * unknown4c;
  }
}

void DrMdoNomAfterImage::captureObj(const DrMdoCtlNom *model) {
  wrkObjList *obj = &unknown00[unknown0a];
  DrMdoCtlNom *clone = obj->unknown10;
  cloneMdlObj(clone, model);
  obj->unknown18 = 0.0f;
  obj->unknown00 = clone->m_matrix.unknown004();
  clone->setDisp(false);
  unknown0a++;
  if (unknown08 <= unknown0a) {
    unknown0a = 0;
  }
  if (clone->getRimBloomWrk(2) != nullptr) {
    unknown091 *rimBloom = clone->getRimBloomWrk(2);
    rimBloom->unknown00 = unknown24;
    rimBloom->unknown14 = unknown38;
    rimBloom->unknown0c = unknown30;
    rimBloom->unknown10 = unknown34;
  }
}

} // namespace ml
