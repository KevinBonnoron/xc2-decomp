#include "gf/object/component/effect/gf_com_effect_caster.h"

#include "framework/effect/effect_caster.h"
#include "framework/effect/effect_clip.h"
#include "framework/effect/effect_manager.h"
#include "framework/effect/effect_pack.h"
#include "gf/asset/gf_asset_resource.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/component/animation/gf_com_asm.h"      // IWYU pragma: keep
#include "gf/object/component/animation/gf_com_evt_anim.h" // IWYU pragma: keep
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

const char *ASM_CB_NAME_EFFECT = "asm_effect";

namespace gf {

void GfComEffectCaster::registerAsmCallbackEffect(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm, fw::EffectResData *effectData) {
  if (resAsm != nullptr && effectData != nullptr) {
    effectData->registerAsmAnnotation(resAsm, 3, ASM_CB_NAME_EFFECT);
  }
}

void GfComEffectCaster::procMsgObjectNotifyDamage(fw::MessageObject *object, MsgObjectNotifyDamage &message) {}

void GfComEffectCaster::procMsgObjectNotifyDead(fw::MessageObject *object, MsgObjectNotifyDead &message) {}

void GfComEffectCaster::procMsgFxRimBloomEnd(fw::MessageObject *object, MsgFxRimBloomEnd &message) {
  unknown14 = false;
  if (unknown20 == -1.0f) {
    unknown20 = unknown1c;
  }
}

void GfComEffectCaster::procMsgFxRimBloomTarget(fw::MessageObject *object, MsgFxRimBloomTarget &message) {
  unknown18 = 10;
  unknown14 = false;
  unknown1c = 0.0f;
  unknown20 = -1.0f;
}

void GfComEffectCaster::procMsgFxRimBloom(fw::MessageObject *object, MsgFxRimBloom &message) {
  if (unknown1c < 0.0f || message.unknown0c) {
    unknown18 = message.unknown08;
    unknown14 = true;
    unknown1c = 0.0f;
    unknown20 = -1.0f;
    message.unknown0d = true;
  }
}

void GfComEffectCaster::openDebugWindow(ml::WinProc *window) {}

fw::EffectPack *GfComEffectCaster::getEffectPack(GF_ASSET_HANDLE *handle) {
  GfAssetResource *resource = GfObjUtil::getResourceEfb(static_cast<GfObj *>(unknown08)->unknownf8);
  if (resource != nullptr) {
    return fw::EffectPack::createFromMemory(resource->getAssetData(), resource->getAssetSize(), resource->getAssetName(), false);
  }
  return nullptr;
}

const char *GfComEffectCaster::getEfpData(const char *name, mm::Mat44 &matrix) {
  if (unknown388 == nullptr || unknown388->unknown10 == nullptr) {
    return nullptr;
  }
  const char *parentName = unknown388->unknown10->getParentName(name);
  matrix = unknown388->unknown10->getOffset(name);
  return parentName;
}

bool GfComEffectCaster::getWeaponEffectPack(mm::mtl::FixedVector<fw::EffectPack *, 8> &packs, int type, int) {
  packs.clear();
  for (const unknown001 &entry : unknown40) {
    if (entry.unknown08 == type) {
      packs.push_back(entry.unknown00);
    }
  }
  return !packs.empty();
}

fw::EffectPoint *GfComEffectCaster::getEffectPoint() { return unknown390; }

bool GfComEffectCaster::getValidEffectName(const char *name) const { return true; }

bool GfComEffectCaster::isDynamicAnnotationEffect(u8 type) const { return type != 0 && type != 0xe; }

bool GfComEffectCaster::getDynamicAnnotationEffectFileName(u8 type, const char *&fileName) const {
  fileName = nullptr;
  return GfEffectGround::getGroundEffectFileName(this, type, fileName);
}

u32 GfComEffectCaster::convertSwimEffectState(GfEffectGround::SwimEffectState state) {
  switch (state) {
  case GfEffectGround::SWIM_EFFECT_STATE_UNKNOWN_0:
    return 0;
  case GfEffectGround::SWIM_EFFECT_STATE_UNKNOWN_1:
    return 1;
  case GfEffectGround::SWIM_EFFECT_STATE_UNKNOWN_2:
    return 2;
  default:
    return 0;
  }
}

u32 GfComEffectCaster::calcWeaponID() const {
  DataParamAcc paramAcc(static_cast<GfObj *>(unknown08)->unknownf8);
  return GfDataWeapon::getEffWeaponType(paramAcc.getWeaponType(-1, false));
}

void GfComEffectCaster::setCaster(u32 effect) { fw::EffectManager::get()->setParam(effect, unknown388, 1.0f); }

bool GfComEffectCaster::setSpeed(u32 effect, f32 speed) {
  Param *param = findEffectCasterParam(effect);
  if (param == nullptr) {
    return false;
  }

  param->unknown30 = speed;
  return true;
}

f32 GfComEffectCaster::getElapsedSecond(u32 effect) {
  Param *param = findEffectCasterParam(effect);
  if (param == nullptr) {
    return -1.0f;
  }

  return param->unknown28;
}

GfComEffectCaster::Param *GfComEffectCaster::findEffectCasterParam(u32 effect) {
  for (Param *param = unknown3a0.begin(); param != unknown3a0.end(); param++) {
    if (param->unknown58 == effect) {
      return param;
    }
  }
  return nullptr;
}

bool GfComEffectCaster::startTimer(u32 effect) {
  Param *param = findEffectCasterParam(effect);
  if (param == nullptr) {
    return false;
  }

  param->unknown28 = 0.0f;
  return true;
}

bool GfComEffectCaster::stopTimer(u32 effect) {
  Param *param = findEffectCasterParam(effect);
  if (param == nullptr) {
    return false;
  }

  param->unknown28 = -1.0f;
  return true;
}

bool GfComEffectCaster::addCasterEffectEv(u32 effect) {
  setCaster(effect);
  return true;
}

void GfComEffectCaster::effectEnd(u32 effect) {
  for (Param *param = unknown3a0.begin(); param != unknown3a0.end(); param++) {
    if (param->unknown58 == effect && param->unknown58 != 0) {
      fw::EffectManager::get()->dead(effect);
      param->unknownba = true;
      return;
    }
  }
}

GF_OBJ_HANDLE *GfComEffectCaster::getWeaponHandle(u16 weapon) {
  if (weapon == 3 || weapon == 4) {
    return GfGameUtil::getDriverWeaponRight(static_cast<GfObj *>(unknown08)->unknownf8);
  }
  if (weapon == 5 || weapon == 6) {
    return GfGameUtil::getDriverWeaponLeft(static_cast<GfObj *>(unknown08)->unknownf8);
  }
  return reinterpret_cast<GF_OBJ_HANDLE *>(-1);
}

void GfComEffectCaster::getWpnMatOld1(mm::Mat44 &matrix) { matrix = unknown113d0; }

void GfComEffectCaster::getWpnMatOld2(mm::Mat44 &matrix) { matrix = unknown11410; }

} // namespace gf

template gf::GfComEffectCaster::Param *mm::mtl::FixedVector<gf::GfComEffectCaster::Param, 256>::erase(gf::GfComEffectCaster::Param *);
template gf::GfComEffectCaster::EventEfHandleTbl *mm::mtl::FixedVector<gf::GfComEffectCaster::EventEfHandleTbl, 256>::erase(gf::GfComEffectCaster::EventEfHandleTbl *);
template void mm::mtl::Delegate<void(gf::GfComAsm *, const gf::CallBackCache &)>::memberFuncInvoker<gf::GfComEffectCaster>(const mm::mtl::Delegate<void(gf::GfComAsm *, const gf::CallBackCache &)> *,
                                                                                                                           gf::GfComAsm *, const gf::CallBackCache &);
template void
mm::mtl::Delegate<void(gf::GfComEvtAnim *, const gf::CallBackCache &)>::memberFuncInvoker<gf::GfComEffectCaster>(const mm::mtl::Delegate<void(gf::GfComEvtAnim *, const gf::CallBackCache &)> *,
                                                                                                                 gf::GfComEvtAnim *, const gf::CallBackCache &);
