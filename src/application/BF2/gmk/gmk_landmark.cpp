#include "gmk/gmk_landmark.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "bdat.h"
#include "framework/debug/debug_draw.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/field/gf_field_manager.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/menu/object/gf_menu_obj_location_telop.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_bdat.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec2.h"
#include <math.h>

namespace mm {
struct Vec3;
} // namespace mm

namespace gmk {

template bool TGmkList<GmkLandmark, GmkLandmark::BdatInfo, 1263354956u, 2u, GmkLandmarkGob>::initGmkBdatInfo(GmkLandmark::BdatInfo &, int &, const AGmkBase &);

void GmkLandmark::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("MSGID", id, BDAT_TYPE_UNKNOWN_2);
  unknown02 = bdat.getValCheck("category", id, BDAT_TYPE_UNKNOWN_1);
  unknown04 = bdat.getValCheck("cndID", id, BDAT_TYPE_UNKNOWN_2);
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

// Inferred role: achievement stats of the landmark categories; original names unknown.
enum {
  STATS_UNKNOWN_51 = 0x33,
  STATS_UNKNOWN_52 = 0x34,
  STATS_UNKNOWN_53 = 0x35,
};

void GmkLandmark::beginEvent() {
  if (unknownf1) {
    return;
  }
  unknownf1 = true;
  const BdatInfo *info = getBdatInfo();
  // A bool through isFound() keeps the game's separate compare for the telop flag (0x710060583c): an int flag compared with 0 is hoisted before the telop calls.
  bool found = isFound();
  if (found) {
    gf::SCOM_QUEST_REACH::createArriveLandmark(unknown20.unknown18);
  } else {
    CBdatWrapper bdat = unknown004();
    int id = unknown20.unknown18;
    gf::SCOM_ADD_EXP::createInnExp(static_cast<u16>(bdat.getValCheck("getEXP", id, BDAT_TYPE_UNKNOWN_2)));
    gf::SCOM_ADD_SP::create(gf::unknown020, static_cast<u16>(bdat.getValCheck("getSP", id, BDAT_TYPE_UNKNOWN_2)));
    u8 developZone = bdat.getValCheck("developZone", id, BDAT_TYPE_UNKNOWN_1);
    u16 developPoint = bdat.getValCheck("get_DPT", id, BDAT_TYPE_UNKNOWN_2);
    gf::SCOM_ADD_DEVELOP::createGmk(developZone, developPoint);
    gf::SCOM_QUEST_REACH::createDiscoverLandmark(unknown20.unknown18);
  }
  if (!info->unknown06) {
    gf::GfMenuObjLocationTelop::OpenParam param;
    param.unknown00 = gf::GfDataBdat::getFP(gf::BDAT_FLD_LANDMARK);
    param.unknown08 = info->unknown00;
    param.unknown0c = info->unknown02;
    param.unknown0e = gf::GfGameManager::getMapID();
    param.unknown10 = !found;
    gf::GfMenuObjLocationTelop::open(param);
  }
  if (!found) {
    const BdatInfo *current = getBdatInfo();
    // The cases in ascending order give the game's compare order 2, 1, 0 (the descending order and an if chain give 0, 1, 2).
    switch (current->unknown02) {
    case 0:
      if (!current->unknown06) {
        gf::SCOM_FIELD_VOICE::createLandmark();
      }
      gf::SCOM_ACHIEV_INC::addTotalCount(STATS_UNKNOWN_51, 1);
      gf::SCOM_ACHIEV_INC::create(STATS_UNKNOWN_51, 1, 0);
      break;
    case 1:
      if (!current->unknown06) {
        gf::SCOM_FIELD_VOICE::createUnexplored();
      }
      gf::SCOM_ACHIEV_INC::addTotalCount(STATS_UNKNOWN_53, 1);
      gf::SCOM_ACHIEV_INC::create(STATS_UNKNOWN_53, 1, 0);
      break;
    case 2:
      gf::SCOM_ACHIEV_INC::addTotalCount(STATS_UNKNOWN_52, 1);
      gf::SCOM_ACHIEV_INC::create(STATS_UNKNOWN_52, 1, 0);
      break;
    }
  }
  if (getBdatInfo()->unknown02 < 2) {
    CBdatWrapper bdat = unknown004();
    u16 mapJumpId = bdat.getValCheck("MAPJUMPID", unknown20.unknown18, BDAT_TYPE_UNKNOWN_2);
    if (mapJumpId) {
      // The game widens the id and loads the position before the matrix call (0x710060583c): the local declared first gives the registers x20 (id) and x21 (position).
      u32 landmark = mapJumpId;
      const mm::Vec3 &position = AGmkBase::unknown08.unknown08->unknown00;
      mm::Mat44 matrix;
      getMatrix(matrix, true);
      gf::GfFieldManager::setLandmarkPoint(landmark, position, atan2f(matrix.rows[2][0], matrix.rows[2][2]));
    }
  }
  GmkLandmarkManager::addGmkLandmark(this);
  gf::GfGameFlag::setLocal(1, getGameFlagId(), 1);
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
template void mm::mtl::Vector<gmk::GmkLandmark>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkLandmark>::resize(size_t);
