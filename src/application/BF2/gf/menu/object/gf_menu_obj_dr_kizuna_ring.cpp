#include "gf/menu/object/gf_menu_obj_dr_kizuna_ring.h"

#include "gf/data/gf_data_driver_skill.h"
#include "gf/game/gf_game_util.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_skill_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjDrKizunaRing::GfMenuObjDrKizunaRing(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(false), unknown3c(0), unknown40(-1), unknown48(nullptr), unknown50(nullptr), unknown60(0), unknown68(this), unknown2f8(0),
      unknown300(nullptr), unknown308(nullptr), unknown310(0) {}

GfMenuObjDrKizunaRing::~GfMenuObjDrKizunaRing() {
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown300);
  mm::mtl::safeRelease(unknown308);
}

void GfMenuObjDrKizunaRing::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrKizunaRing::update() {
  unknown68.unknown003();
  GfMenuObject::update();
}

u32 GfMenuObjDrKizunaRing::getSkillUnlockLevel(u32 driver) {
  bool isHidden = GfMenuReference::getReferenceNumber(2) != 0;
  u32 level = 0;
  if (GfDataDriverSkill::isSkillLevelUnlock(driver, 1, isHidden)) {
    if (!GfDataDriverSkill::isSkillLevelUnlock(driver, 2, isHidden)) {
      level = 1;
    } else if (!GfDataDriverSkill::isSkillLevelUnlock(driver, 3, isHidden)) {
      level = 2;
    } else {
      level = 3;
    }
  }
  return level;
}

void GfMenuObjDrKizunaRing::movePointer(u32 handle, int index, ui::UISelectObjList *list) {
  setupInputSelection(handle, index, list->getSize());
  mm::Pnt<s16> pos;
  {
    ui::UIObjectAcc acc(list->getContents(index));
    acc.getPosCenter(pos);
  }
  changePointerPos(handle, pos);
}

void GfMenuObjDrKizunaRing::setupMain(ui::UIObjectAcc &acc) { GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_drst_spnum_S24_L1H10"), 26, 0, true); }

void GfMenuObjDrKizunaRing::setupDriverSkillInfo(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  name.format("TXT_dr_spnum_S20_L1H2@%02d", 1);
  GfMenuSkillAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 8, 0, 0, 1, 2, true);
  name.format("TXT_dr_spnummax_S20_L1H2@%02d", 1);
  GfMenuSkillAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 9, 0, 0, 1, 2, false);
}

void GfMenuObjDrKizunaRing::setupSkillDetail(ui::UIObjectAcc &acc) {
  GfMenuAdapterManager::beginAddAfter();
  GfMenuSkillAdapter::createFromReferenceDriverLineLevel(acc.searchChild("TXT_skif_skillname_S24_L1C12"), 0, 0, 0, 1, 2, true);
  GfMenuSkillAdapter::createFromReferenceDriverLineLevel(acc.searchChild("TXT_skif_infotxt_S24_L3C20"), 1, 0, 0, 1, 2, true);
  GfMenuSkillAdapter::createFromReferenceDriverLineLevel(acc.searchChild("TXT_skif_spnum_S20_L1C10"), 2, 0, 0, 1, 2, true);
  mm::mtl::FixStr<32> name;
  name.format("IMG_skif_icon@%02d", 1);
  GfMenuSkillAdapter::createFromReferenceDriverLineLevel(acc.searchChild(name.c_str()), 3, 0, 0, 1, 2, true);
  name.format("IMG_skif_icon_base@%02d", 1);
  GfMenuSkillAdapter::createFromReferenceDriverLineLevel(acc.searchChild(name.c_str()), 5, 0, 0, 1, 2, true);
  GfMenuSkillAdapter *lock = GfMenuSkillAdapter::createFromReferenceDriverLineLevel(acc.searchChild("TXT_skif_skillname_lock"), 10, 0, 0, 1, 2, true);
  lock->unknown24 = acc.searchChild("LAY_skif_lock");
  GfMenuAdapterManager::endAddAfter();
}

bool GfMenuObjDrKizunaRing::isLockPos(int index) { return index % 6 == 0; }

bool GfMenuObjDrKizunaRing::isScreenLR(u32 screen) { return screen < 3; }

void GfMenuObjDrKizunaRing::setupCircle(ui::UIObjectAcc &, u32) {}

void GfMenuObjDrKizunaRing::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjDrKizunaRing::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::unknown002(handle);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjDrKizunaRing::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::unknown003(handle);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjDrKizunaRing::seqWait() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc scale(acc.searchChild("LAY_scale"));
  enableInput(scale.unknown10);
  return true;
}

bool GfMenuObjDrKizunaRing::seqExecSkill() {
  u32 driver = GfMenuReference::getReferenceDriverID(0);
  GfGameUtil::execDriverSkillLevelUp(driver, GfMenuReference::getReferenceNumber(0), GfMenuReference::getReferenceNumber(1), GfMenuReference::getReferenceNumber(2) != 0);
  return true;
}

bool GfMenuObjDrKizunaRing::seqCircleAnime() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc main(acc.searchChild("LAY_dr_main"));
  u32 driver = GfMenuReference::getReferenceDriverID(0);
  u32 level = getSkillUnlockLevel(driver);
  ui::UIObjectAcc effect(main.searchChild("IMG_ring_eff"));
  bool isEnd;
  if (unknown2f8 == 0) {
    effect.startAnimation(level == 1 ? "lineb" : "linec", false);
    GfMenuObjUtil::playSE(16);
    isEnd = false;
    unknown2f8++;
  } else if (!effect.isPlayingAnimation()) {
    isEnd = true;
    unknown2f8 = 0;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjDrKizunaRing::seqUnlockAnime() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc main(acc.searchChild("LAY_dr_main"));
  ui::UIObjectAcc lock(main.searchChild("IMG_lock_open"));
  bool isEnd;
  if (unknown2f8 == 0) {
    u32 driver = GfMenuReference::getReferenceDriverID(0);
    const char *name = getSkillUnlockLevel(driver) == 1 ? "lock2" : "lock3";
    lock.startAnimation("skill_open", false);
    lock.setDisp(true);
    mm::Rect<s16> rect;
    main.getLayoutRect(name, rect);
    mm::Pnt<s16> center;
    center.x = rect.x + rect.width / 2;
    center.y = rect.y + rect.height / 2;
    lock.setPosCenter(center);
    GfMenuObjUtil::playSE(15);
    isEnd = false;
    unknown2f8++;
  } else if (!lock.isPlayingAnimation()) {
    isEnd = true;
    unknown2f8 = 0;
  } else {
    isEnd = false;
  }
  return isEnd;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjDrKizunaRing, 8>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjDrKizunaRing>(const mm::mtl::Delegate<bool()> *);
