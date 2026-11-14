#include "gmk/gmk_precious.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "fw/fw_param_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_field_icon.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/util/gf_item_util.h"
#include "gmk/gmk_active_list.h"
#include "gmk/gmk_bdat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"

namespace fw {
enum EF_CATEGORY : int;
} // namespace fw

namespace gmk {

template bool TGmkList<GmkPrecious, GmkPrecious::BdatInfo, 1396920912u, 2u, GmkPreciousGob>::initGmkBdatInfo(GmkPrecious::BdatInfo &, int &, const AGmkBase &);

template class TGmkActiveList<GmkPrecious>;

GmkPrecious::GmkPrecious() : IntrusiveListNode(), unknown58(gf::unknown020), unknown60(0), unknown68(nullptr), unknown70{0.0f}, unknown74(true) {}

// Inferred role: pick up area of the pc param list; original type name unknown.
struct unknown091 {
  f32 unknown00; // Inferred role: horizontal radius; original member name unknown.
  f32 unknown04; // Inferred role: height above; original member name unknown.
  f32 unknown08; // Inferred role: depth below; original member name unknown.
};

constexpr int WILDCARD_UNKNOWN_34 = 34; // Inferred role: wildcard precious pop dist row; original name unknown.

void GmkPrecious::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  dispose();
  unknown00 = bdat.getValCheck("itmID", id, BDAT_TYPE_UNKNOWN_2);
  gf::GfItemUtil::isPrecious(unknown00);
  unknown02 = bdat.getValCheck("Condition", id, BDAT_TYPE_UNKNOWN_2);
  unknown04 = bdat.getValCheck("QuestID", id, BDAT_TYPE_UNKNOWN_2);
  unknown06 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_UNKNOWN_2), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_UNKNOWN_2));
  unknown0a =
      QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_UNKNOWN_2), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_UNKNOWN_1), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_UNKNOWN_1));
  unknown10.unknown08 = bdat.getValCheck("POP_TIME", id, BDAT_TYPE_UNKNOWN_3);
  unknown20.unknown08 = bdat.getValCheck("popWeather", id, BDAT_TYPE_UNKNOWN_1);
}

void GmkPrecious::BdatInfo::dispose() { unknown00 = 0; }

bool GmkPrecious::BdatInfo::isPopCondMatched() const {
  if (unknown06.isEnable() && !unknown06.isMatch()) {
    return false;
  }
  if (unknown0a.isEnable() && !unknown0a.isMatch()) {
    return false;
  }
  if (unknown10.isEnable() && !unknown10.isMatch()) {
    return false;
  }
  if (unknown20.isEnable() && !unknown20.isMatch()) {
    return false;
  }
  if (unknown02 != 0 && !gf::GfGameCond::isGameCond(unknown02)) {
    return false;
  }
  return true;
}

GmkType GmkPrecious::getGmkType() const { return GMK_TYPE; }

int GmkPrecious::getGameFlagId() const { return unknown20.unknown18 + 0xb7ef; }

void GmkPrecious::create(const CreateInfo &info) {
  AGmkBase::create(info);
  f32 popDist = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_UNKNOWN_34, BDAT_TYPE_UNKNOWN_8).valueF32;
  unknown70.unknown00 = popDist * popDist;
}

bool GmkPrecious::isObtained() const { return gf::GfGameFlag::getLocal(1, getGameFlagId()) != 0; }

void GmkPrecious::disposeMenuIcon() {
  if (unknown68 != nullptr) {
    gf::GfMenuObjFieldIcon::close(unknown68);
    mm::mtl::safeRelease(unknown68);
  }
}

void GmkPrecious::disposeEffectIcon(bool isFadeOut) {
  if (unknown60 != 0) {
    if (isFadeOut) {
      fw::EffectManager::get()->fadeOutDead(unknown60, 5);
    } else {
      fw::EffectManager::get()->remove(unknown60);
    }
    unknown60 = 0;
  }
}

void GmkPrecious::dispose() {
  disposeMenuIcon();
  disposeEffectIcon(false);
  disposeGobInst(false);
  AGmkBase::dispose();
}

void GmkPrecious::disposeGobInst(bool isFadeOut) {
  if (unknown58 == gf::unknown020) {
    return;
  }
  if (intoNode() && TGmkActiveList<GmkPrecious>::get() != nullptr) {
    TGmkActiveList<GmkPrecious>::get()->unknown08.erase(this);
  }
  if (isFadeOut) {
    gmk::disposeGobInst(unknown58, 1.0f);
  } else {
    unbindToGameObj(unknown58);
    gf::GfObjUtil::destroy(unknown58);
    unknown58 = gf::unknown020;
  }
}

void GmkPrecious::createEffectIcon() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeEffectIcon(false);
  void *data = fw::EffectManager::get()->search("cmn_202_000", nullptr);
  if (data == nullptr) {
    return;
  }
  unknown60 = fw::EffectManager::get()->create(data, true);
  if (unknown60 != 0) {
    fw::EffectManager::get()->setCategory(unknown60, static_cast<fw::EF_CATEGORY>(1));
  }
}

bool GmkPrecious::isPopCondMatched() const {
  const BdatInfo *info = getBdatInfo();
  if (isObtained() || !info->isPopCondMatched()) {
    return false;
  }
  return DistCond::isMatch(unknown70.unknown00, AGmkBase::unknown08.unknown08->unknown00);
}

void GmkPrecious::validateDisp() const {
  bool isDisp = unknown74 && debugIsDispGmkType(getGmkType());
  if (unknown58 != gf::unknown020) {
    setEventDisp(unknown58, isDisp);
  }
  if (unknown60 != 0) {
    fw::EffectManager::get()->setDisp(unknown60, isDisp);
  }
}

void GmkPrecious::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid() || !gf::GfGameManager::isControlFree()) {
    return;
  }
  u32 effect = unknown60;
  bool isPopCondMatched = this->isPopCondMatched();
  if (effect == 0) {
    if (isPopCondMatched) {
      createGobInst();
      createEffectIcon();
      validateXform();
    }
  } else if (!isPopCondMatched) {
    disposeGobInst(true);
    disposeEffectIcon(true);
    disposeMenuIcon();
  }
  if (unknown58 != gf::unknown020 && unknown68 == nullptr) {
    createMenuIcon();
  }
  updateMenuIcon();
  if (unknown60 != 0 && isObtained()) {
    disposeGobInst(true);
    disposeEffectIcon(true);
    disposeMenuIcon();
  }
}

void GmkPrecious::updateInActiveList(f32 deltaTime) {
  if (gf::GfGameManager::getControlMover() == gf::unknown020 || isObtained() || gf::GfGameManager::isBattle() || !gf::GfGameManager::isEnableGetFieldPrecious()) {
    return;
  }
  const mm::Vec3 &moverPosition = gf::GfObjUtil::getObj(gf::GfGameManager::getControlMover())->getComponent<gf::GfComTransform>()->getPosition();
  mm::Vec3 diff = AGmkBase::unknown08.unknown08->unknown00 - moverPosition;
  const unknown091 *param = static_cast<const unknown091 *>(fw::ParamManager::get()->unknown408[5]->unknown10[5].param);
  if (-param->unknown08 <= diff.y && diff.y <= param->unknown04) {
    diff.y = 0.0f;
    if (diff.x * diff.x + diff.y * diff.y + diff.z * diff.z <= param->unknown00 * param->unknown00) {
      gf::GfGameFlag::setLocal(1, getGameFlagId(), 1);
      const BdatInfo *info = getBdatInfo();
      gf::SCOM_ADD_ITEM::create(info->unknown00, 1);
      gf::GfPlayFactory::createMenuPrecious(info->unknown00, true);
    }
  }
}

void GmkPrecious::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event != gf::IGfObjListener::OBJEVT_UNKNOWN_3) {
    return;
  }
  disposeGobInst(false);
}

void GmkPrecious::debugDraw() const {
  if (!isValid()) {
    return;
  }
  const BdatInfo *info = getBdatInfo();
  if (isObtained() || !info->isPopCondMatched()) {
    return;
  }
  DistCond::isMatch(unknown70.unknown00, AGmkBase::unknown08.unknown08->unknown00);
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkPrecious::BdatInfo>::expand(size_t, size_t);

template void mm::mtl::Vector<gmk::GmkPrecious::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkPrecious::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkPrecious>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkPrecious>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkPrecious>::resize(size_t);
