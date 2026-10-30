#include "gmk/gmk_landmark.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "bdat.h"
#include "framework/debug/debug_draw.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/menu/object/gf_menu_obj_location_telop.h"
#include "gmk/gmk_bdat.h"
#include "mm_math/mm_vec2.h"

namespace gmk {

template bool TGmkList<GmkLandmark, GmkLandmark::BdatInfo, 1263354956u, 2u, GmkLandmarkGob>::initGmkBdatInfo(GmkLandmark::BdatInfo &, int &, const AGmkBase &);

void GmkLandmark::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("MSGID", id, BDAT_TYPE_U16);
  unknown02 = bdat.getValCheck("category", id, BDAT_TYPE_U8);
  unknown04 = bdat.getValCheck("cndID", id, BDAT_TYPE_U16);
  unknown06 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "noTelop") != 0;
  if (unknown00 != 0) {
    unknown08 = Bdat::getMSText(gf::GfDataBdat::getFP(gf::BDAT_FLD_LANDMARK), unknown00);
  }
}

bool GmkLandmark::BdatInfo::isCondMatched() const {
  if (unknown04 != 0 && !gf::GfGameCond::isGameCond(unknown04)) {
    return false;
  }
  return true;
}

GmkLandmark::GmkLandmark() : unknown60(nullptr), unknownf0(false), unknownf1(false) {}

GmkType GmkLandmark::getGmkType() const { return GMK_TYPE; }

void GmkLandmark::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  bool isCondMatched = getBdatInfo()->isCondMatched();
  if (unknownf0 != isCondMatched) {
    if (isCondMatched) {
      createGmkPhantom();
    } else {
      disposeGmkPhantom();
    }
    unknownf0 = isCondMatched;
  }
  if (unknown60.unknown83 && gf::GfGameManager::isLandmarkUiOK()) {
    beginEvent();
  }
}

void GmkLandmark::create(const CreateInfo &info) { AGmkBase::create(info); }

int GmkLandmark::getGameFlagId() const { return unknown20.unknown18 + 0xc7d9; }

bool GmkLandmark::isFound() const { return gf::GfGameFlag::getLocal(1, getGameFlagId()) != 0; }

void GmkLandmark::dispose() {
  disposeGmkPhantom();
  AGmkBase::dispose();
}

void GmkLandmark::debugDraw() const {
  if (!isValid()) {
    return;
  }
  static const char *unknown001[] = {"LND", "UR", "AREA", "FSKL"}; // Inferred role: debug label per category; original name unknown.
  mm::Vec2 screen;
  if (toScreenPos(screen, AGmkBase::unknown08.unknown08->unknown00)) {
    const char *label = unknown001[getBdatInfo()->unknown02];
    fw::debug::drawFont(static_cast<int>(screen.x), static_cast<int>(screen.y) + 16, label);
  }
}

void GmkLandmark::onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo &info) {}

void GmkLandmark::createGmkPhantom() {
  if (!canCreateGameEntity()) {
    return;
  }
  unknown60.create(*this, this, false);
}

void GmkLandmark::disposeGmkPhantom() {
  unknown60.dispose();
  endEvent();
}

void GmkLandmark::endEvent() {
  if (unknownf1) {
    unknownf1 = false;
    gf::GfMenuObjLocationTelop::cancel();
    GmkLandmarkManager::removeGmkLandmark(this);
  }
}

GmkLandmarkManager::GmkLandmarkManager() : unknown20(nullptr) {}

void GmkLandmarkManager::dispose() {
  unknown20 = nullptr;
  unknown08.clear();
}

void GmkLandmarkManager::addGmkLandmark(GmkLandmark *landmark) {
  u8 category = landmark->getBdatInfo()->unknown02;
  mm::mtl::IntrusiveList<GmkLandmark> &list = get()->unknown08;
  bool isInserted = false;
  for (mm::mtl::IntrusiveList<GmkLandmark>::iterator it = list.begin(); it != list.end(); ++it) {
    if (it.get()->getBdatInfo()->unknown02 >= category) {
      list.insert(it, landmark);
      isInserted = true;
      break;
    }
  }
  if (!isInserted) {
    list.push_back(landmark);
  }
  get()->unknown20 = get()->unknown08.begin().get();
}

void GmkLandmarkManager::removeGmkLandmark(GmkLandmark *landmark) {
  if (landmark == nullptr || get() == nullptr) {
    return;
  }
  get()->unknown08.erase(landmark);
  if (get()->unknown08.empty()) {
    get()->unknown20 = nullptr;
  } else {
    get()->unknown20 = get()->unknown08.begin().get();
  }
}

const GmkLandmark *GmkLandmarkManager::findFirstAddedGmkLandmarkByCategory(u8 category) const {
  for (mm::mtl::IntrusiveList<GmkLandmark>::iterator it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (it.get()->getBdatInfo()->unknown02 == category) {
      return it.get();
    }
  }
  return nullptr;
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkLandmark::BdatInfo>::expand(size_t, size_t);

template void mm::mtl::Vector<gmk::GmkLandmark::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkLandmark::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkLandmark>::expand(size_t, size_t);
