#include "gmk/gmk_form.h"

#include "fw/fw_coli_check.h"
#include "gf/game/gf_game_party.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_form_impl.h" // IWYU pragma: keep
#include "gmk/gmk_form_pc.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_set.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

extern template bool GmkForm::create<GmkFormPc, GmkFormPcnpc>(const GmkFormPc &);
template bool GmkForm::create<GmkFormPcEv, GmkFormPcnpcEv>(const GmkFormPcEv &);

GmkForm::GmkForm(const CreateInfo *info) : unknown00(0) {
  for (u32 i = 0; i < MAX_NUM; i++) {
    unknown10[i] = mm::Vec3::zero;
    unknown70[i] = 0.0f;
  }
  if (info != nullptr) {
    create(*info);
  }
}

bool GmkForm::create(const CreateInfo &info) {
  GmkSet *set = info.unknown00;
  bool isEvent = info.unknown0c;
  u32 index = info.unknown08;
  if (!isEvent) {
    const IGmkList *list = set->unknown1b8[GMK_TYPE_FORM_PC];
    if (list != nullptr && list->getInstNum() > index) {
      const GmkFormPc *formPc = static_cast<const GmkFormPc *>(list->getInst(index));
      if (formPc != nullptr && create<GmkFormPc, GmkFormPcnpc>(*formPc)) {
        validatePosRotY();
        return true;
      }
    }
  } else {
    const IGmkList *list = set->unknown1b8[GMK_TYPE_FORM_PC_EV];
    if (list != nullptr && list->getInstNum() > index) {
      const GmkFormPcEv *formPc = static_cast<const GmkFormPcEv *>(list->getInst(index));
      if (formPc != nullptr && create<GmkFormPcEv, GmkFormPcnpcEv>(*formPc)) {
        validatePosRotY();
        return true;
      }
    }
  }
  return false;
}

bool GmkForm::create(const mm::Vec3 &position, f32 rotationY) {
  unknown00 = 1;
  unknown10[0] = position;
  unknown70[0] = rotationY;
  validatePosRotY();
  return true;
}

void GmkForm::getPosRotY(mm::Vec3 &position, f32 &rotationY, u32 index) const {
  position = unknown10[index];
  rotationY = unknown70[index];
}

void GmkForm::dispose() { unknown00 = 0; }

void GmkForm::apply(f32 snapDistance) {
  for (u32 i = 0; i < 3; i++) {
    gf::GF_OBJ_HANDLE *driver = gf::GfGameParty::getHandleDriver(i);
    if (driver != gf::INVALID_HANDLE) {
      gf::GfObjSetupDriver *setup = gf::GfObjUtil::getObjSetup<gf::GfObjSetupDriver>(driver);
      mm::Vec3 position;
      f32 rotationY;
      getPosRotY(position, rotationY, i);
      position.y += snapDistance * 0.5f;
      mm::Vec3 snapped;
      if (fw::ColiCheck::getSnapPos(snapped, position, snapDistance, 0xffffffff)) {
        setup->unknown20 = snapped;
        setup->unknown30 = mm::Vec3(0.0f, rotationY, 0.0f);
        gf::SCOM_OBJ_WARP_POS::create(driver, setup->unknown20, setup->unknown30, false);
      } else {
        setup->unknown20 = position;
        setup->unknown30 = mm::Vec3(0.0f, rotationY, 0.0f);
      }
    }
    gf::GF_OBJ_HANDLE *blade = gf::GfGameParty::getHandleBlade(i, -1);
    if (blade != gf::INVALID_HANDLE) {
      gf::GfObjSetupBlade *setup = gf::GfObjUtil::getObjSetup<gf::GfObjSetupBlade>(blade);
      mm::Vec3 position;
      f32 rotationY;
      getPosRotY(position, rotationY, i + 3);
      position.y += snapDistance * 0.5f;
      mm::Vec3 snapped;
      if (fw::ColiCheck::getSnapPos(snapped, position, snapDistance, 0xffffffff)) {
        setup->unknown20 = snapped;
        setup->unknown30 = mm::Vec3(0.0f, rotationY, 0.0f);
        gf::SCOM_OBJ_WARP_POS::create(blade, setup->unknown20, setup->unknown30, false);
      } else {
        setup->unknown20 = position;
        setup->unknown30 = mm::Vec3(0.0f, rotationY, 0.0f);
      }
    }
  }
}

} // namespace gmk
