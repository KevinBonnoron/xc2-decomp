#include "gmk/gmk_dmg_gimmick.h"

#include "eflib/effect_send_param.h"
#include "framework/coli/coli_object.h"
#include "framework/effect/effect_manager.h"
#include "framework/sound/sound_manager.h"
#include "fw/fw_coli_check.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_dmg.h"
#include "gf/field/gf_field_manager.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "gmk/gmk_set.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace fw {
enum SoundCategory : int;
enum EF_CATEGORY : int;
} // namespace fw

namespace fw {
class EffectPack;
} // namespace fw

namespace gmk {

template bool TGmkList<GmkDmgEffect, GmkDmgEffect::BdatInfo, 1178946884u, 1u, GmkDmgEffectGob>::initGmkBdatInfo(GmkDmgEffect::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkDmgGimmick, GmkDmgGimmick::BdatInfo, 1296518468u, 1u, GmkDmgGimmickGobCustom>::initGmkBdatInfo(GmkDmgGimmick::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkDmgPhantom, GmkDmgPhantom::BdatInfo, 1213222212u, 2u, GmkDmgPhantomGob>::initGmkBdatInfo(GmkDmgPhantom::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkDmgSe, GmkDmgSe::BdatInfo, 1163087172u, 2u, GmkDmgSeGob>::initGmkBdatInfo(GmkDmgSe::BdatInfo &, int &, const AGmkBase &);

void GmkDmgGimmick::debugDraw() const {
  isValid();
  isValid();
}

const fw::SoundCategory SOUND_CATEGORY_UNKNOWN_7 = static_cast<fw::SoundCategory>(7); // Inferred role: dmg se category; original name unknown.

void GmkDmgGimmick::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_UNKNOWN_2);
  unknown1c = BootedGmkCond(bdat, id, "DEPOP_");
  unknown02 = bdat.getValCheck("DEPOP_Condition", id, BDAT_TYPE_UNKNOWN_2);
  unknown04 = toBdatF32(bdat.getValCheck("DMG_interval", id, BDAT_TYPE_UNKNOWN_8));
  unknown08 = bdat.getValCheck("Pc_dmg", id, BDAT_TYPE_UNKNOWN_1);
  unknown09 = bdat.getValCheck("EN_dmg", id, BDAT_TYPE_UNKNOWN_1);
  unknown10 = reinterpret_cast<const char *>(bdat.getValCheck("effect_name", id, BDAT_TYPE_UNKNOWN_7));
  unknown18 = bdat.getValCheck("SE_name", id, BDAT_TYPE_UNKNOWN_1);
  unknown19 = bdat.getValCheck("volumeMAX", id, BDAT_TYPE_UNKNOWN_1);
  unknown1a = bdat.getValCheck("volumeMIN", id, BDAT_TYPE_UNKNOWN_1);
  u16 effectDispRadius = bdat.getValCheck("effect_disp_r", id, BDAT_TYPE_UNKNOWN_2);
  unknown20.unknown00 = static_cast<f32>(effectDispRadius) * static_cast<f32>(effectDispRadius);
  u8 effectReleaseRadius = bdat.getValCheck("effect_release_r", id, BDAT_TYPE_UNKNOWN_1);
  f32 effectReleaseDistance = effectDispRadius + effectReleaseRadius;
  unknown24.unknown00 = effectReleaseDistance * effectReleaseDistance;
}

bool GmkDmgGimmick::BdatInfo::isCondMatched() const {
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  if (unknown1c.isEnable() && unknown1c.isMatch()) {
    return false;
  }
  if (unknown02 != 0 && gf::GfGameCond::isGameCond(unknown02)) {
    return false;
  }
  return true;
}

void GmkDmgSe::createGmkPhantom() const {
  if (!canCreateGameEntity()) {
    return;
  }
  switch (unknown08.unknown10->unknown0c) {
  case SHAPE_TYPE_UNKNOWN_2:
  case SHAPE_TYPE_UNKNOWN_3:
  case SHAPE_TYPE_UNKNOWN_4:
    unknown50.create(*this, nullptr, false);
    break;
  default:
    break;
  }
}

void GmkDmgSe::createSeInst(fw::SoundPack *pack, u32 id) const {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeSeInst(false);
  unknowne4 = fw::SoundManager::get()->playSe(id, pack, 1.0f, SOUND_CATEGORY_UNKNOWN_7);
  if (unknowne4 != 0) {
    const mm::Vec3 &position = unknown08.unknown08->unknown00;
    fw::SoundManager::get()->setPos(unknowne4, position);
  }
}

void GmkDmgSe::disposeSeInst(bool isFadeOut) const {
  if (unknowne4 == 0) {
    return;
  }
  fw::SoundManager::get()->stopSe(unknowne4, isFadeOut ? 1.0f : 0.0f);
  unknowne4 = 0;
}

void GmkDmgSe::setSeVolume(f32 volume, f32 time) const {
  unknowne8 = volume;
  fw::SoundManager::get()->setVolume(unknowne4, volume, time);
}

void GmkDmgSe::dispose() {
  disposeSeInst(false);
  AGmkBase::dispose();
}

void GmkDmgSe::validateMute() const {
  if (unknowne4 == 0) {
    return;
  }
  fw::SoundManager::get()->setVolume(unknowne4, unknowne0 ? 0.0f : unknowne8, 0.0f);
}

GmkType GmkDmgPhantom::getGmkType() const { return GMK_TYPE; }

bool GmkDmgPhantom::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkDmgPhantom::createGmkPhantom(fw::ColiUserData *userData) const {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeGmkPhantom();
  GmkPhantomSimple::CreateInfo info;
  info.validateByAGmkBase(*this);
  unknown50.create(info);
  unknown50.unknown50->setColiUserData(userData);
}

void GmkDmgPhantom::disposeGmkPhantom() const { unknown50.dispose(); }

void GmkDmgPhantom::dispose() {
  disposeGmkPhantom();
  AGmkBase::dispose();
}

GmkType GmkDmgEffect::getGmkType() const { return GMK_TYPE; }

bool GmkDmgEffect::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkDmgEffect::update(f32 deltaTime) { debugUpdateMmf(); }

void GmkDmgEffect::validateDisp() const {
  if (unknown4c == 0) {
    return;
  }
  bool isDisp = unknown48 && debugIsDispGmkType(getGmkType());
  fw::EffectManager::get()->setDisp(unknown4c, isDisp);
}

void GmkDmgEffect::dispose() {
  if (unknown4c != 0) {
    fw::EffectManager::get()->remove(unknown4c);
    unknown4c = 0;
  }
  AGmkBase::dispose();
}

void GmkDmgEffect::createEffectInst(void *const &data) const {
  if (!canCreateGameEntity()) {
    return;
  }
  if (unknown4c != 0) {
    fw::EffectManager::get()->remove(unknown4c);
    unknown4c = 0;
  }
  u32 handle = fw::EffectManager::get()->create(data, true);
  unknown4c = handle;
  fw::EffectManager::get()->setCategory(handle, static_cast<fw::EF_CATEGORY>(1));
  applyEffectParam();
}

void GmkDmgEffect::disposeEffectInst(bool isFadeOut) const {
  if (unknown4c != 0) {
    if (isFadeOut) {
      fw::EffectManager::get()->dead(unknown4c);
    } else {
      fw::EffectManager::get()->remove(unknown4c);
    }
    unknown4c = 0;
  }
}

void GmkDmgEffect::applyEffectParam() const {
  if (unknown4c == 0) {
    return;
  }
  effect::SendParam param;
  param.unknown00.unknown011(unknown08.unknown08->unknown10);
  mm::Vec3 position = unknown08.unknown08->unknown00;
  param.unknown00.rows[3][0] += position.x;
  param.unknown00.rows[3][1] += position.y;
  param.unknown00.rows[3][2] += position.z;
  param.unknown60 = unknown08.unknown08->unknown20;
  param.unknowna3 = unknown48 && debugIsDispGmkType(getGmkType());
  fw::EffectManager::get()->setParam(unknown4c, &param);
}

const AGmkBase *GmkDmgPhantomList::getInst(u32 index) const { return &gmkInsts[index]; }

const AGmkBase *GmkDmgEffectList::getInst(u32 index) const { return &gmkInsts[index]; }

const AGmkBase *GmkDmgSeList::getInst(u32 index) const { return &gmkInsts[index]; }

u32 GmkDmgPhantomTargetInfo::getTargetType() const {
  if (unknown00 == gf::unknown020) {
    return 0;
  }
  if (unknown08 <= 0) {
    return 0;
  }
  gf::GfObjAcc acc(unknown00);
  switch (acc.getType()) {
  case gf::OBJECT_TYPE_PC:
  case gf::OBJECT_TYPE_BLADE:
    return 1;
  case gf::OBJECT_TYPE_ENEMY:
    return 2;
  default:
    return 0;
  }
}

bool GmkDmgPhantomTargetInfo::isTargetPlayer() const {
  if (gf::GfGameManager::getControlMover() == gf::unknown020) {
    return false;
  }
  return unknown00 == gf::GfGameManager::getControlMover();
}

GmkType GmkDmgGimmick::getGmkType() const { return GMK_TYPE; }

const mm::mtl::RTTI *GmkDmgGimmick::getRTTI() const { return &m_rtti; }

void GmkDmgGimmick::create(const CreateInfo &info) {
  AGmkBase::create(info);
  if (!isValid()) {
    dispose();
    return;
  }
  fw::EffectPack *pack = gf::GfFieldManager::getEffectPack();
  if (pack != nullptr && getBdatInfo()->unknown10 != nullptr && getBdatInfo()->unknown10[0] != '\0') {
    unknown58 = fw::EffectManager::get()->search(getBdatInfo()->unknown10, pack);
    if (unknown58 == nullptr) {
      canCreateGameEntity();
    }
  }
  unknown60 = gf::GfFieldSound::get()->getMapPack();
  unknown68 = &GmkDmgGimmick::seqWaitToCreateChild;
}

GmkDmgGimmick::GmkDmgGimmick() : unknown50(false), unknown58(nullptr), unknown60(nullptr), unknown68(nullptr), unknown80(true) { unknown78 = this; }

void GmkDmgGimmick::dispose() {
  unknown58 = nullptr;
  AGmkBase::dispose();
  unknown68 = nullptr;
}

void GmkDmgGimmick::seqWaitToCreateChild(f32 deltaTime) { unknown68 = &GmkDmgGimmick::seqUpdatePopDepop; }

void GmkDmgGimmick::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  if (unknown68) {
    (this->*unknown68)(deltaTime);
  }
}

GmkDmgPhantom *GmkDmgGimmick::getGmkDmgPhantom(u32 index) const {
  IGmkList *list = unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_DMG_PHANTOM];
  const Data *data = getData();
  if (list != nullptr && list->getInstNum() > data->unknown00 + index) {
    u32 listIndex = data->unknown00 + index;
    return static_cast<GmkDmgPhantom *>(const_cast<AGmkBase *>(list->getInst(listIndex)));
  }
  return nullptr;
}

GmkDmgEffect *GmkDmgGimmick::getGmkDmgEffect(u32 index) const {
  IGmkList *list = unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_DMG_EFFECT];
  const Data *data = getData();
  if (list != nullptr && list->getInstNum() > data->unknown04 + index) {
    u32 listIndex = data->unknown04 + index;
    return static_cast<GmkDmgEffect *>(const_cast<AGmkBase *>(list->getInst(listIndex)));
  }
  return nullptr;
}

GmkDmgSe *GmkDmgGimmick::getGmkDmgSe(u32 index) const {
  IGmkList *list = unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_DMG_SE];
  const Data *data = getData();
  if (list != nullptr && list->getInstNum() > data->unknown08 + index) {
    u32 listIndex = data->unknown08 + index;
    return static_cast<GmkDmgSe *>(const_cast<AGmkBase *>(list->getInst(listIndex)));
  }
  return nullptr;
}

void GmkDmgGimmick::validateDisp() const { bool isDisp = unknown80 && debugIsDispGmkType(getGmkType()); }

void GmkDmgGimmick::seqUpdatePopDepop(f32 deltaTime) {
  const BdatInfo *info = getBdatInfo();
  bool isPop = info->isCondMatched();
  bool wasPop = unknown50;
  unknown50 = isPop;
  if (isPop != wasPop) {
    u32 phantomNum = getData()->unknown02 - getData()->unknown00;
    for (u32 i = 0; i < phantomNum; i++) {
      GmkDmgPhantom *phantom = getGmkDmgPhantom(i);
      if (phantom != nullptr) {
        if (isPop) {
          phantom->createGmkPhantom(this);
        } else {
          phantom->disposeGmkPhantom();
        }
      }
    }
  }
  u32 effectNum = getData()->unknown06 - getData()->unknown04;
  for (u32 i = 0; i < effectNum; i++) {
    GmkDmgEffect *effect = getGmkDmgEffect(i);
    if (effect != nullptr) {
      const mm::Vec3 &position = effect->unknown08.unknown08->unknown00;
      if (!isPop) {
        effect->disposeEffectInst(true);
      } else if (effect->unknown4c == 0) {
        if (unknown58 != nullptr && DistCond::isMatch(info->unknown20.unknown00, position)) {
          effect->createEffectInst(unknown58);
        }
      } else if (!DistCond::isMatch(info->unknown24.unknown00, position)) {
        effect->disposeEffectInst(true);
      }
    }
  }
  u32 seNum = getData()->unknown0a - getData()->unknown08;
  for (u32 i = 0; i < seNum; i++) {
    GmkDmgSe *se = getGmkDmgSe(i);
    if (se != nullptr) {
      if (isPop != wasPop) {
        if (isPop) {
          se->createGmkPhantom();
        } else {
          se->unknown50.dispose();
        }
      }
      if (se->unknown50.unknown001() && isPop) {
        if (se->unknowne4 == 0) {
          se->createSeInst(unknown60, info->unknown18);
        }
      } else {
        se->disposeSeInst(true);
      }
    }
  }
}

GmkDmgPhantomManager::GmkDmgPhantomManager() : unknown38(false) {
  gf::GfObjManager::addListener(this, OBJEVT_UNKNOWN_0);
  gf::GfEvent::addEventCallback(this);
  create();
}

GmkDmgPhantomManager::~GmkDmgPhantomManager() {
  dispose();
  gf::GfEvent::removeEventCallback(this);
  gf::GfObjManager::removeListener(this);
}

void GmkDmgPhantomManager::create() {
  dispose();
  unknown10.setAllocator(gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0));
  int capacity = gf::GfObjManager::getGfObjCapacity(5);
  unknown10.reserve(capacity > 0 ? static_cast<u32>(capacity + 3) : 3);
}

void GmkDmgPhantomManager::dispose() { unknown10.destroy(); }

void GmkDmgPhantomManager::addTargetInfo(gf::GF_OBJ_HANDLE *handle) {
  GmkDmgPhantomTargetInfo *it = unknown10.begin();
  GmkDmgPhantomTargetInfo *last = unknown10.end();
  while (it != last) {
    if (it->unknown00 == handle) {
      return;
    }
    it++;
  }
  if (unknown10.size() != unknown10.capacity()) {
    GmkDmgPhantomTargetInfo info;
    info.unknown00 = handle;
    info.unknown08 = 0;
    info.unknown0c = 0.0f;
    unknown10.push_back(info);
  }
}

void GmkDmgPhantomManager::removeTargetInfo(gf::GF_OBJ_HANDLE *handle) {
  if (handle == gf::unknown020) {
    return;
  }
  for (GmkDmgPhantomTargetInfo *it = unknown10.begin(); it != unknown10.end(); it++) {
    if (it->unknown00 == handle) {
      unknown10.erase(it);
      return;
    }
  }
}

void GmkDmgPhantomManager::listenerGfObj(OBJEVT event, gf::GF_OBJ_HANDLE *handle, u32 objectType) {
  gf::GfObjAcc acc(handle);
  if (objectType == gf::OBJECT_TYPE_PC || objectType == gf::OBJECT_TYPE_BLADE) {
    u32 playerId = gf::GfGamePlayerFormation::get()->findPlayer(handle);
    if (playerId == gf::PLAYER_ID_UNKNOWN_4294967295) {
      return;
    }
    if (!gf::GfGamePlayerFormation::get()->unknown1a0[playerId].unknown10) {
      return;
    }
  } else {
    if (objectType != gf::OBJECT_TYPE_ENEMY) {
      return;
    }
    gf::DataParamAcc dataParam(handle);
    const gf::SDataEnemy *data = dataParam.getSDataEnemy();
    if (data == nullptr) {
      return;
    }
    if ((data->unknown04 & gf::ENEMY_FLAG_UNKNOWN_9) == 0) {
      return;
    }
  }
  if (event == OBJEVT_UNKNOWN_2) {
    addTargetInfo(handle);
  } else if (event == OBJEVT_UNKNOWN_3) {
    removeTargetInfo(handle);
  }
}

void GmkDmgPhantomManager::gevPartyMover(gf::GF_OBJ_HANDLE *handle, bool isJoin) {
  u32 objectType = gf::GfObjUtil::getObjType(handle);
  if (objectType != gf::OBJECT_TYPE_PC && objectType != gf::OBJECT_TYPE_BLADE) {
    return;
  }
  if (isJoin) {
    if (gf::GfGameManager::isPartyMover(handle)) {
      addTargetInfo(handle);
    }
  } else {
    removeTargetInfo(handle);
  }
}

void GmkDmgPhantomManager::update(f32 deltaTime) {
  unknown38 = false;
  if (unknown10.capacity() == 0) {
    return;
  }
  fw::ColiCheckConfig config;
  config.unknown14 = true;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown15 = false;
  config.unknown00 = fw::ColiCheckConfig::FLAG_UNKNOWN_2;
  config.unknown04 = 0x100000;
  config.unknown10 = 0;
  fw::TColiCheckResult<256> result;
  for (GmkDmgPhantomTargetInfo &info : unknown10) {
    gf::GfObjAcc acc(info.unknown00);
    gf::GfObj *obj = acc.getObj();
    if (obj == nullptr) {
      continue;
    }
    const gf::GfComCollider *collider = obj->getComponent<gf::GfComCollider>();
    if (collider == nullptr) {
      continue;
    }
    fw::ColiObject *coli = collider->unknown18[0];
    if (coli == nullptr || !coli->isActivate()) {
      continue;
    }
    result.clear();
    if (!fw::ColiCheck::testObjectPhantom(result, coli, config)) {
      info.unknown08 = 0;
      info.unknown0c = 0.0f;
      continue;
    }
    bool isInside = false;
    u32 hitNum = result.getCount();
    for (u32 i = 0; i < hitNum; i++) {
      fw::ColiUserData *userData = result.unknown002(i);
      GmkDmgGimmick *gimmick = nullptr;
      if (userData != nullptr) {
        gimmick = mm::mtl::dynamicCast<GmkDmgGimmick>(userData);
      }
      if (gimmick != nullptr) {
        if (gimmick->isValid()) {
          isInside = true;
          if (info.isTargetPlayer()) {
            unknown38 = true;
          }
          f32 interval = gimmick->getBdatInfo()->unknown04;
          int bdatIndex = gimmick->unknown20.unknown18;
          if (info.unknown08 != bdatIndex) {
            info.unknown08 = bdatIndex;
            info.unknown0c = interval;
          }
          info.unknown0c += deltaTime;
          if (info.unknown0c < interval) {
            break;
          }
          info.unknown0c = 0.0f;
          if (!gf::GfGameManager::isEnableGimmickPhantomDamage()) {
            break;
          }
          switch (info.getTargetType()) {
          case 1: {
            gf::GfObj *target = gf::GfObjUtil::getObj(info.unknown00);
            if (target != nullptr) {
              gf::MsgPcApplyFieldDamage message(gimmick->getBdatInfo()->unknown08);
              target->sendMessage(target, message);
            }
            break;
          }
          case 2:
            gf::GfFieldDmg::applyDamage(info.unknown00, gimmick->getBdatInfo()->unknown09);
            break;
          default:
            break;
          }
        }
        break;
      }
    }
    if (!isInside) {
      info.unknown08 = 0;
      info.unknown0c = 0.0f;
    }
  }
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkDmgEffect::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgEffect::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgEffect::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkDmgEffect>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgGimmick::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgPhantom::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgPhantom::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgPhantom::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkDmgPhantom>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgPhantom>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgPhantom>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkDmgSe::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgSe::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgSe::BdatInfo>::resize(size_t);

template void mm::mtl::Vector<gmk::GmkDmgGimmick::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgGimmick::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkDmgEffect>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgEffect>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkDmgSe>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgSe>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgSe>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkDmgGimmick>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgGimmick>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgGimmick>::resize(size_t);
