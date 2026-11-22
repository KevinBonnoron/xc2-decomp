#include "gmk/gmk_area_bgm.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/field/gf_field_bgm.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

template bool TGmkList<GmkAreaBgm, GmkAreaBgm::BdatInfo, 1380009794u, 2u, GmkAreaBgmGob>::initGmkBdatInfo(GmkAreaBgm::BdatInfo &, int &, const AGmkBase &);

// Inferred role: bgm id of the owner of a condition info; original name unknown.
static u32 unknown001(const GmkBgmCondInfo *info) { return info == nullptr ? 0 : info->m_gmkAreaBgm->getBdatInfo()->unknown00; }

bool GmkBgmCondInfo::isCondMatched() const { return gf::GfGameCond::isGameCond(unknown18); }

void GmkBgmCondInfo::dispose() { GmkBgmCondInfoManager::removeGmkBgmCondInfo(this); }

void GmkBgmCondInfoManager::addGmkBgmCondInfo(GmkBgmCondInfo *info) {
  get()->unknown08.push_front(info);
  get()->m_gmkBgmCondInfo = get()->unknown08.begin().get();
  u32 bgmId = unknown001(get()->m_gmkBgmCondInfo);
  gf::GfFieldBgm::get()->setGimmickBgmID(bgmId);
}

void GmkBgmCondInfoManager::removeGmkBgmCondInfo(GmkBgmCondInfo *info) {
  if (info == nullptr || !info->intoNode() || get() == nullptr) {
    return;
  }
  get()->unknown08.erase(info);
  u32 bgmId;
  if (get()->unknown08.empty()) {
    get()->m_gmkBgmCondInfo = nullptr;
    bgmId = 0;
  } else {
    get()->m_gmkBgmCondInfo = get()->unknown08.begin().get();
    bgmId = unknown001(get()->m_gmkBgmCondInfo);
  }
  gf::GfFieldBgm::get()->setGimmickBgmID(bgmId);
}

void GmkBgmCondInfoManager::dispose() {
  m_gmkBgmCondInfo = nullptr;
  mm::mtl::IntrusiveList<GmkBgmCondInfo>::iterator it = unknown08.begin();
  while (it != unknown08.end()) {
    it = unknown08.erase(it);
  }
}

void GmkBgmCondInfoManager::applyFieldBgm() const {
  u32 bgmId = 0;
  if (m_gmkBgmCondInfo != nullptr) {
    bgmId = get()->m_gmkBgmCondInfo->m_gmkAreaBgm->getBdatInfo()->unknown00;
  }
  gf::GfFieldBgm::get()->setGimmickBgmID(bgmId);
}

GmkType GmkAreaBgm::getGmkType() const { return GMK_TYPE; }

void GmkAreaBgm::createGmkPhantom() {
  if (!canCreateGameEntity()) {
    return;
  }
  m_gmkPhantom.create(*this, this, false);
}

void GmkAreaBgm::disposeBgmCondInfos() {
  for (int i = 0; i < 4; i++) {
    unknowne0[i].dispose();
  }
  unknown160 = nullptr;
}

void GmkAreaBgm::onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo &info) {
  for (int i = 0; i < 4; i++) {
    unknowne0[i].dispose();
  }
}

void GmkAreaBgm::dispose() {
  disposeBgmCondInfos();
  m_gmkPhantom.dispose();
  AGmkBase::dispose();
}

// Inferred role: fills one bgm condition info from the bgm condition bdat; original name unknown.
static void unknown002(GmkBgmCondInfo &info, GmkAreaBgm *owner, u8 *bdat, u32 id, const char *conditionName, const char *bgmIdName) {
  info.m_gmkAreaBgm = owner;
  info.unknown18 = Bdat::getValCheck(bdat, conditionName, id, BDAT_TYPE_UNKNOWN_2);
  info.unknown1a = Bdat::getValCheck(bdat, bgmIdName, id, BDAT_TYPE_UNKNOWN_2);
}

void GmkAreaBgm::createBgmCondInfos() {
  disposeBgmCondInfos();
  if (!isValid()) {
    return;
  }
  u8 *bdat = gf::GfDataBdat::getFP(gf::BDAT_RSC_BGM_CONDITION);
  u32 id = getBdatInfo()->unknown00;
  unknown002(unknowne0[0], this, bdat, id, "ConditionA", "BgmIDA");
  unknown002(unknowne0[1], this, bdat, id, "ConditionB", "BgmIDB");
  unknown002(unknowne0[2], this, bdat, id, "ConditionC", "BgmIDC");
  unknown002(unknowne0[3], this, bdat, id, "ConditionD", "BgmIDD");
}

void GmkAreaBgm::update(f32 deltaTime) {
  debugUpdateMmf();
  GmkBgmCondInfo *matched = findCondMatched();
  if (unknown160 != matched) {
    if (unknown160 == nullptr) {
      createGmkPhantom();
    } else if (matched == nullptr) {
      m_gmkPhantom.dispose();
    }
    GmkBgmCondInfoManager::removeGmkBgmCondInfo(unknown160);
    unknown160 = matched;
  }
  if (matched != nullptr && !matched->intoNode() && m_gmkPhantom.unknown83) {
    GmkBgmCondInfoManager::addGmkBgmCondInfo(matched);
  }
}

void GmkAreaBgm::create(const CreateInfo &info) {
  AGmkBase::create(info);
  createBgmCondInfos();
}

void GmkAreaBgm::debugDraw() const {}

void GmkAreaBgm::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  dispose();
  unknown00 = bdat.getValCheck("bgmCondition", id, BDAT_TYPE_UNKNOWN_2);
}

void GmkAreaBgm::onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo &info) {}

GmkBgmCondInfo *GmkAreaBgm::findCondMatched() {
  for (int i = 0; i < 4; i++) {
    if (unknowne0[i].isCondMatched()) {
      return &unknowne0[i];
    }
  }
  return nullptr;
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkAreaBgm::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkAreaBgm::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkAreaBgm::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkAreaBgm>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkAreaBgm>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkAreaBgm>::resize(size_t);
template mm::mtl::PtrSingleton<gmk::GmkBgmCondInfoManager>::~PtrSingleton();
