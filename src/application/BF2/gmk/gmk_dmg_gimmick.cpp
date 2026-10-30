#include "gmk/gmk_dmg_gimmick.h"

#include "framework/effect/effect_manager.h"
#include "framework/sound/sound_manager.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_manager.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "gmk/gmk_set.h"
#include "mm_mtl/vector.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace fw {
enum SoundCategory : int;
enum EF_CATEGORY : int;
} // namespace fw
namespace mm {
struct Vec3;
} // namespace mm

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

const fw::SoundCategory DMG_SE_CATEGORY = static_cast<fw::SoundCategory>(7);

void GmkDmgGimmick::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown1c = BootedGmkCond(bdat, id, "DEPOP_");
  unknown02 = bdat.getValCheck("DEPOP_Condition", id, BDAT_TYPE_U16);
  unknown04 = toBdatF32(bdat.getValCheck("DMG_interval", id, BDAT_TYPE_F32));
  unknown08 = bdat.getValCheck("Pc_dmg", id, BDAT_TYPE_U8);
  unknown09 = bdat.getValCheck("EN_dmg", id, BDAT_TYPE_U8);
  unknown10 = reinterpret_cast<const char *>(bdat.getValCheck("effect_name", id, BDAT_TYPE_STRING));
  unknown18 = bdat.getValCheck("SE_name", id, BDAT_TYPE_U8);
  unknown19 = bdat.getValCheck("volumeMAX", id, BDAT_TYPE_U8);
  unknown1a = bdat.getValCheck("volumeMIN", id, BDAT_TYPE_U8);
  u16 effectDispRadius = bdat.getValCheck("effect_disp_r", id, BDAT_TYPE_U16);
  unknown20.unknown00 = static_cast<f32>(effectDispRadius) * static_cast<f32>(effectDispRadius);
  u8 effectReleaseRadius = bdat.getValCheck("effect_release_r", id, BDAT_TYPE_U8);
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
  case SHAPE_TYPE_SPHERE:
  case SHAPE_TYPE_BOX:
  case SHAPE_TYPE_CAPSULE:
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
  unknowne4 = fw::SoundManager::get()->playSe(id, pack, 1.0f, DMG_SE_CATEGORY);
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

const AGmkBase *GmkDmgPhantomList::getInst(u32 index) const { return &gmkInsts[index]; }

const AGmkBase *GmkDmgEffectList::getInst(u32 index) const { return &gmkInsts[index]; }

const AGmkBase *GmkDmgSeList::getInst(u32 index) const { return &gmkInsts[index]; }

u32 GmkDmgPhantomTargetInfo::getTargetType() const {
  if (unknown00 == gf::INVALID_HANDLE) {
    return 0;
  }
  if (unknown08 <= 0) {
    return 0;
  }
  gf::GfObjAcc acc(unknown00);
  switch (acc.getType()) {
  case gf::OBJECT_TYPE_DRIVER:
  case gf::OBJECT_TYPE_BLADE:
    return 1;
  case gf::OBJECT_TYPE_ENEMY:
    return 2;
  default:
    return 0;
  }
}

bool GmkDmgPhantomTargetInfo::isTargetPlayer() const {
  if (gf::GfGameManager::getControlMover() == gf::INVALID_HANDLE) {
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

GmkDmgGimmick::GmkDmgGimmick() : unknown50(false), unknown58(nullptr), unknown60(nullptr), unknown68(nullptr), unknown78(this), unknown80(true) {}

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

GmkDmgPhantomManager::GmkDmgPhantomManager() : unknown38(false) {
  gf::GfObjManager::addListener(this, OBJEVT_ALL);
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
  unknown10.setAllocator(gf::getAllocator(gf::ALLOCATOR_DEFAULT));
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
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  for (GmkDmgPhantomTargetInfo *it = unknown10.begin(); it != unknown10.end(); it++) {
    if (it->unknown00 == handle) {
      unknown10.erase(it);
      return;
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
template void mm::mtl::Vector<gmk::GmkDmgSe::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgSe::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgSe::BdatInfo>::resize(size_t);

template void mm::mtl::Vector<gmk::GmkDmgGimmick::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkDmgGimmick::BdatInfo>::resize(size_t);
