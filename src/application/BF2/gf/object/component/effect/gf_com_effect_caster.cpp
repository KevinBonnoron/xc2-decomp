#include "gf/object/component/effect/gf_com_effect_caster.h"

#include <stdlib.h>
#include <string.h>

#include "anm/anm_asm_listener.h"
#include "eflib/effect_send_param.h"
#include "framework/effect/effect_caster.h"
#include "framework/effect/effect_clip.h"
#include "framework/effect/effect_manager.h"
#include "framework/effect/effect_pack.h"
#include "framework/effect/effect_point.h"
#include "framework/object/updatable_object.h"
#include "gf/asset/gf_asset_resource.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/component/animation/gf_com_asm.h"      // IWYU pragma: keep
#include "gf/object/component/animation/gf_com_evt_anim.h" // IWYU pragma: keep
#include "gf/object/component/effect/gf_effect_caster.h"
#include "gf/object/component/model/gf_com_model.h" // IWYU pragma: keep
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/vector.h"

// Named as the game's global symbol ASM_CB_NAME_EFFECT.
const char *ASM_CB_NAME_EFFECT = "asm_effect";

namespace gf {

// Inferred helper: component-wise difference of two matrices; original name unknown.
static mm::Mat44 unknown002(const mm::Mat44 &a, const mm::Mat44 &b) {
  mm::Mat44 result;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result.rows[i][j] = a.rows[i][j] - b.rows[i][j];
    }
  }
  return result;
}

// The game assigns the result of each erase back to the string: after the erase it computes the length again, stores it, compares it with 0x80 and asserts at
// fixstr.h line 221 (0x7100503644-0x710050366c and 0x71005036d4-0x71005036fc), without a copy (clang folds the copy of a string onto itself). The loop reads the
// annotation table again at each iteration because effectStart is an opaque call (it is declared only: it does not match yet, the blocker is recorded).
void GfComEffectCaster::procMessageAsmCallback(fw::MessageObject *object, MsgObjectNotifyAsmCallback &message) {
  const anm::AsmAnnotetion *annotation = message.unknown10;
  if (strcmp(annotation->unknown00, "weaponChange") == 0 && unknown30 != nullptr) {
    mm::mtl::FixStr<128> parameter;
    parameter = annotation->unknown10;
    f32 fade = 1.0f;
    const char *found = strstr(parameter.c_str(), "fadein_");
    if (found != nullptr) {
      parameter = parameter.erase(found - parameter.c_str(), 7);
      fade = atof(parameter.c_str());
    }
    found = strstr(parameter.c_str(), "fadeout_");
    if (found != nullptr) {
      parameter = parameter.erase(found - parameter.c_str(), 8);
      fade = atof(parameter.c_str());
    }
    for (fw::EffectAnnotationData *it = unknown30->unknown10.begin(); it != unknown30->unknown10.end(); it++) {
      if (it->unknownf0.unknown14 != 3) {
        continue;
      }
      EffectSetUp setup;
      setup.unknown28 = it->unknown54.c_str();
      setup.unknown44 = it->unknownf0.unknown18;
      setup.unknown38 = unknown114a8 * it->unknownc0.unknown04;
      setup.unknown48 = it->unknownf0.unknown05;
      setup.unknown49 = it->unknownf0.unknown04;
      setup.unknown3c = fade;
      setup.unknown00 = it->unknownd0;
      setup.unknown10 = it->unknowne0;
      setup.unknown4b = it->unknownf0.unknown09;
      setup.unknown4c = it->unknownf0.unknown0a;
      setup.unknown4d = it->unknownf0.unknown0a >> 8;
      if (setup.unknown4d != 0) {
        setup.unknown38 = it->unknownc0.unknown04;
      }
      it->unknownf0.unknown1c = effectStart(setup, it->unknown78.c_str());
    }
  }
}

void GfComEffectCaster::asmCallback(GfComAsm *, const CallBackCache &cache) { callbackImpl(cache); }

void GfComEffectCaster::evtAnimCallback(GfComEvtAnim *, const CallBackCache &cache) { callbackImpl(cache); }

void GfComEffectCaster::registerAsmCallbackEffect(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm, fw::EffectResData *effectData) {
  if (resAsm != nullptr && effectData != nullptr) {
    effectData->registerAsmAnnotation(resAsm, 3, ASM_CB_NAME_EFFECT);
  }
}

void GfComEffectCaster::procMsgObjectNotifyDamage(fw::MessageObject *object, MsgObjectNotifyDamage &message) {}

void GfComEffectCaster::procMsgObjectNotifyDead(fw::MessageObject *object, MsgObjectNotifyDead &message) {}

bool GfComEffectCaster::getEfpMatrix(const char *name, mm::Mat44 &matrix) {
  if (m_effectCaster != nullptr) {
    if (m_effectCaster->unknown10 == nullptr) {
      return false;
    }
    int index = m_effectCaster->unknown10->getPointIndex(name);
    if (index != -1) {
      matrix.unknown009(m_effectCaster->unknown10->getPointTransform(index), m_effectCaster->unknown60);
      return true;
    }
  }
  return false;
}

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

void GfComEffectCaster::cleanup() {
  for (EventEfHandleTbl *tbl = unknownc3b0.begin(); tbl != unknownc3b0.end(); tbl++) {
    if (tbl->unknown28.get() != nullptr) {
      tbl->unknown28.get()->release();
      tbl->unknown28 = nullptr;
    }
  }
  unknownc3b0.clear();
  for (Param *param = unknown3a0.begin(); param != unknown3a0.end(); param++) {
    if (param->unknown58 != 0) {
      fw::EffectManager::get()->remove(param->unknown58);
    }
    if (param->unknown6e && m_effectPoint != nullptr) {
      m_effectPoint->unknown88(param->unknown34.c_str());
    }
  }
  unknown3a0.clear();
  if (unknown38 != nullptr) {
    unknown38->release();
    unknown38 = nullptr;
  }
  for (u32 i = 0; i < unknown40.size(); i++) {
    if (unknown40[i].unknown00 != nullptr) {
      unknown40[i].unknown00->release();
      unknown40[i].unknown00 = nullptr;
    }
  }
  unknown40.clear();
  fw::EffectCasterBase *caster = m_effectCaster;
  if (caster != nullptr) {
    if (caster->unknown10 != nullptr) {
      caster->unknown10->unknown002();
      caster->unknown10 = nullptr;
    }
    caster->_40 = true;
    m_effectCaster = nullptr;
  }
  if (m_effectPoint != nullptr) {
    m_effectPoint->unknown002();
    m_effectPoint = nullptr;
  }
}

fw::EffectPack *GfComEffectCaster::getEffectPack(GF_ASSET_HANDLE *handle) {
  GfAssetResource *resource = GfObjUtil::getResourceEfb(static_cast<GfObj *>(unknown08)->unknownf8);
  if (resource != nullptr) {
    return fw::EffectPack::createFromMemory(resource->getAssetData(), resource->getAssetSize(), resource->getAssetName(), false);
  }
  return nullptr;
}

const char *GfComEffectCaster::getEfpData(const char *name, mm::Mat44 &matrix) {
  if (m_effectCaster == nullptr || m_effectCaster->unknown10 == nullptr) {
    return nullptr;
  }
  const char *parentName = m_effectCaster->unknown10->getParentName(name);
  matrix = m_effectCaster->unknown10->getOffset(name);
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

fw::EffectPack *GfComEffectCaster::getWeaponEffectPack(const char *name) {
  if (strncmp(name, "cmn", 3) == 0) {
    return nullptr;
  }

  u32 weapon = calcWeaponID();
  for (u32 i = 0; i < unknown40.size(); i++) {
    if (unknown40[i].unknown08 == weapon && unknown40[i].unknown00 != nullptr && unknown40[i].unknown00->searchEfb(name) != nullptr) {
      fw::EffectPack *pack = unknown40[i].unknown00;
      if (pack != nullptr) {
        return pack;
      }
      break;
    }
  }

  fw::EffectPack *pack = unknown38;
  if (unknown1149c == 3 || unknown1149c == 4) {
    GF_OBJ_HANDLE *parent = GfObjUtil::getParentHandle(static_cast<GfObj *>(unknown08)->unknownf8);
    if (parent != unknown020) {
      pack = getEffectPack(GfObjUtil::getAssetHandle(parent));
    }
  }
  return pack;
}

void GfComEffectCaster::updateParam(GfComEffectCaster *caster, Param *param, f32 time, bool unknown) {
  effect::SendParam sendParam;
  calcMtxAndScale(caster, param, time, false, sendParam);
  u32 tag = calcFollowAnnotetionTag(param, sendParam);
  if (tag == 0) {
    fw::EffectManager::get()->setParam(param->unknown58, &sendParam);
  } else if (tag == 1) {
    sendParam.unknowna3 = 0;
    fw::EffectManager::get()->setParam(param->unknown58, &sendParam);
  } else if (tag == 2) {
    if (!param->unknownba) {
      effectEnd(param->unknown58);
    }
  }
}

void GfComEffectCaster::getWpnMat(mm::Mat44 &matrix) { matrix = unknown002(unknown113d0, unknown11410); }

fw::EffectPoint *GfComEffectCaster::getEffectPoint() { return m_effectPoint; }

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

void GfComEffectCaster::setCaster(u32 effect) { fw::EffectManager::get()->setParam(effect, m_effectCaster, 1.0f); }

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

void GfComEffectCaster::addMountEffectEv(const EffectMountSetupEv &setup) {
  if (setup.unknown0 == 0) {
    return;
  }
  EventEfHandleTbl tbl;
  tbl.unknown00 = setup.unknown8;
  tbl.unknown24 = setup.unknown0;
  tbl.unknown28 = nullptr;
  tbl.unknown30 = setup.unknown30;
  tbl.unknown41 = setup.unknown41;
  tbl.unknown40 = setup.unknown40;
  tbl.unknown42 = setup.unknown42;
  if (tbl.unknown41) {
    if (m_effectPoint != nullptr) {
      tbl.unknown28 = m_effectPoint->unknown68(tbl.unknown00.c_str());
    } else {
      GfComModel *model = unknown08->getComponent<GfComModel>();
      if (model != nullptr) {
        tbl.unknown28 = model->createBoneReferenceFrame(tbl.unknown00.c_str());
      }
    }
  }
  unknownc3b0.push_back(tbl);
}

bool GfComEffectCaster::removeMountEffectEv(u32 effect) {
  for (EventEfHandleTbl *tbl = unknownc3b0.begin(); tbl != unknownc3b0.end(); tbl++) {
    if (tbl->unknown24 == effect) {
      if (tbl->unknown41) {
        if (m_effectPoint == nullptr) {
          GfComModel *model = unknown08->getComponent<GfComModel>();
          if (model != nullptr) {
            model->destroyBoneReferenceFrame(tbl->unknown00.c_str());
          }
        } else {
          m_effectPoint->unknown88(tbl->unknown00.c_str());
        }
      }
      unknownc3b0.erase(tbl);
      return true;
    }
  }
  return false;
}

GF_OBJ_HANDLE *GfComEffectCaster::getWeaponHandle(u16 weapon) {
  if (weapon == 3 || weapon == 4) {
    return GfGameUtil::getDriverWeaponRight(static_cast<GfObj *>(unknown08)->unknownf8);
  }
  if (weapon == 5 || weapon == 6) {
    return GfGameUtil::getDriverWeaponLeft(static_cast<GfObj *>(unknown08)->unknownf8);
  }
  return unknown020;
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
template mm::mtl::IntrusivePtr<fw::ReferenceFrame>
mm::mtl::Delegate<mm::mtl::IntrusivePtr<fw::ReferenceFrame>(const char *)>::memberFuncInvoker<gf::GfComModel>(const mm::mtl::Delegate<mm::mtl::IntrusivePtr<fw::ReferenceFrame>(const char *)> *,
                                                                                                              const char *);
template void mm::mtl::Delegate<void(const char *)>::memberFuncInvoker<gf::GfComModel>(const mm::mtl::Delegate<void(const char *)> *, const char *);
