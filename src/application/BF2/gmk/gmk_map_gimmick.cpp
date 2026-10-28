#include "gmk/gmk_map_gimmick.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "mm_mtl/vector.h"

namespace gmk {

template bool TGmkList<GmkMapGimmick, GmkMapGimmick::BdatInfo, 1196441933u, 2u, GmkMapGimmickGob>::initGmkBdatInfo(GmkMapGimmick::BdatInfo &, int &, const AGmkBase &);

void GmkMapGimmick::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  u16 popTime = bdat.getValCheck("popTime", id, BDAT_TYPE_U32);
  unknown08.unknown08 = popTime;
  unknown18.unknown08 = bdat.getValCheck("popWeather", id, BDAT_TYPE_U8);
  unknown28 = BootedGmkCond(bdat, id, nullptr);
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown02 = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("mapobjID", id, BDAT_TYPE_U16);
  unknown06 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "MSG_ray") != 0;
}

bool GmkMapGimmick::BdatInfo::isPopCondMatched() const {
  if (unknown08.isEnable() && !unknown08.isMatch()) {
    return false;
  }
  if (unknown18.isEnable() && !unknown18.isMatch()) {
    return false;
  }
  if (unknown28.isEnable() && !unknown28.isMatch()) {
    return false;
  }
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

void GmkMapGimmick::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

void GmkMapGimmick::update(f32 deltaTime) {
  AGmkBase::update(deltaTime);
  if (isValid() && unknown50) {
    (this->*unknown50)(deltaTime);
  }
}

void GmkMapGimmick::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) {}

GmkType GmkMapGimmick::getGmkType() const { return GMK_TYPE; }

void GmkMapGimmick::dispose() {
  unknown50 = nullptr;
  disposeGobInst();
  AGmkBase::dispose();
}

void GmkMapGimmick::createGobInst() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeGobInst();
  CBdatWrapper bdat = {getBindedBdatFp()};
  unknown60 = gf::GfObjFactory::createGmkMapGimmick(bdat, unknown20.unknown18);
  gf::GfObjSetupGimmick *setup = gf::GfObjUtil::getObjSetup<gf::GfObjSetupGimmick>(unknown60);
  unknown003(setup, unknown08.unknown08);
  unknown002(unknown60, !unknownA8);
  if (getBdatInfo()->unknown06) {
    setup->unknown6c |= 8;
  }
  bindToGameObj(unknown60);
  if (unknownA8) {
    gf::GfPlayFactory::createMapGimmick(unknown60);
  }
}

void GmkMapGimmick::disposeGobInst() {
  if (unknown60 != gf::INVALID_HANDLE) {
    unbindToGameObj(unknown60);
    gf::GfObjUtil::destroy(unknown60);
    unknown60 = gf::INVALID_HANDLE;
  }
}
void GmkMapGimmick::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_DESTROY) {
    unknown60 = gf::INVALID_HANDLE;
  }
}

void GmkMapGimmick::debugDraw() const {
  if (!isValid()) {
    return;
  }
  GameFlagCond cond(1, getGameFlagId());
  cond.isMatch(0);
}

int GmkMapGimmick::getGameFlagId() const { return unknown20.unknown18 + 0xab66; }
bool GmkMapGimmick::isNotSolved() const {
  GameFlagCond cond(1, getGameFlagId());
  return cond.isMatch(0);
}

void GmkMapGimmick::setSolved() const { gf::GfGameFlag::setLocal(1, getGameFlagId(), 1); }

void GmkMapGimmick::create(const CreateInfo &info) {
  AGmkBase::create(info);
  if (isValid()) {
    f32 radius = static_cast<f32>(getBdatInfo()->unknown02);
    unknown48 = (radius + 10.0f) * (radius + 10.0f);
    unknown50 = &GmkMapGimmick::seqInit;
  }
}

bool GmkMapGimmick::canPopGobInst() const {
  if (unknown60 != gf::INVALID_HANDLE) {
    return false;
  }
  if (!isNotSolved()) {
    return false;
  }
  if (!getBdatInfo()->isPopCondMatched()) {
    return false;
  }
  if (unknownA8 && !unknownA9) {
    return false;
  }
  if (unknown48 > 0.0f) {
    if (!DistCond::isMatch(unknown48, unknown08.unknown08->unknown00)) {
      return false;
    }
  }
  return true;
}

bool GmkMapGimmick::canDepopGobInst() const {
  if (unknown60 == gf::INVALID_HANDLE) {
    return false;
  }
  if (!isNotSolved()) {
    return true;
  }
  if (!getBdatInfo()->isPopCondMatched()) {
    return true;
  }
  if (unknown48 > 0.0f && !DistCond::isMatch(unknown48, unknown08.unknown08->unknown00)) {
    return true;
  }
  return false;
}

bool GmkMapGimmickList::updateImmediate() {
  bool isValidList = isValid();
  u32 savedUpdateGmkNumPerFrame = updateGmkNumPerFrame;
  u32 savedUpdateGmkIndex = updateGmkIndex;
  if (seq) {
    updateGmkNumPerFrame = getInstNum();
    updateGmkIndex = 0;
    (this->*seq)(0.0f);
  }
  updateGmkNumPerFrame = savedUpdateGmkNumPerFrame;
  updateGmkIndex = savedUpdateGmkIndex;
  if (!isValidList) {
    return false;
  }
  return unknown230.updateImmediate();
}

const AGmkBase *GmkMapGimmickList::getInst(u32 index) const { return &gmkInsts[index]; }

void GmkMapGimmickList::createGmk(void *data) {
  TGmkList::createGmk(data);
  unknown001(unknown230, getCreateInfo());
}

void GmkMapGimmickList::dispose() {
  unknown230.dispose();
  TGmkList::dispose();
}

void GmkMapGimmickList::update(f32 deltaTime) {
  unknown230.update(deltaTime);
  TGmkList::update(deltaTime);
}

void GmkMapGimmickList::setUpdateGmkNumPerFrame(u32 num) {
  TGmkList::setUpdateGmkNumPerFrame(num);
  unknown230.setUpdateGmkNumPerFrame(num);
}

void GmkMapGimmickList::debugDraw() const {
  TGmkList::debugDraw();
  unknown230.debugDraw();
}

void GmkMapGimmickList::debugUpdateMmf() {
  TGmkList::debugUpdateMmf();
  unknown230.debugUpdateMmf();
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkMapGimmick::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkMapGimmick>::expand(size_t, size_t);

template void mm::mtl::Vector<gmk::GmkMapGimmick::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkMapGimmick::BdatInfo>::resize(size_t);
