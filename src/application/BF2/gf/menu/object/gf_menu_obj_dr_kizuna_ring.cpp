#include "gf/menu/object/gf_menu_obj_dr_kizuna_ring.h"

#include "gf/data/gf_data_driver_skill.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_skill_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gmo_dr_kizuna_ring {

f32 rateTbl[2] = {1.0f, 0.5f};

} // namespace gmo_dr_kizuna_ring

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

void GfMenuObjDrKizunaRing::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 153 as in the original file: it is the line argument of operator new.
#line 153
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(0x66, main);
  u32 ring = acc.searchChild("LAY_dr_main");
// __LINE__ must be 159 as in the original file: it is the line argument of operator new.
#line 159
  RingListener *ringListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) RingListener(this);
  ringListener->addRef();
  ui::UIEventManager::get()->registObjectListener(ring, ringListener);
  if (ringListener != nullptr) {
    ringListener->release();
  }
  u32 scale = acc.searchChild("LAY_scale");
// __LINE__ must be 163 as in the original file: it is the line argument of operator new.
#line 163
  RingPadListener *ringPadListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) RingPadListener(this);
  ringPadListener->addRef();
  ui::UIEventManager::get()->registObjectListener(scale, ringPadListener);
  if (ringPadListener != nullptr) {
    ringPadListener->release();
  }
  u32 skillInfo = acc.searchChild("LAY_skill_info");
// __LINE__ must be 167 as in the original file: it is the line argument of operator new.
#line 167
  SkillDetailListener *skillDetailListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SkillDetailListener(this);
  skillDetailListener->addRef();
  ui::UIEventManager::get()->registObjectListener(skillInfo, skillDetailListener);
  if (skillDetailListener != nullptr) {
    skillDetailListener->release();
  }
  u32 stockSP = acc.searchChild("LAY_dr_stocksp");
// __LINE__ must be 175 as in the original file: it is the line argument of operator new.
#line 175
  DriverStockSPListener *stockSPListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DriverStockSPListener(this);
  stockSPListener->addRef();
  ui::UIEventManager::get()->registObjectListener(stockSP, stockSPListener);
  if (stockSPListener != nullptr) {
    stockSPListener->release();
  }
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown28 = ui::UISelectObjList::create(param);
  unknown48 = GfMenuCallContext::create();
  unknown50 = GfMenuCallContext::create();
  unknown300 = GfMenuCallContext::create();
  unknown308 = GfMenuItemList::create();
  ui::UIListInfoBase::SetupParam itemParam;
  unknown308->setup(getAllocator(ALLOCATOR_UNKNOWN_0), itemParam);
  disableInput(acc.searchChild("LAY_dr_main"));
  disableInput(acc.searchChild("LAY_scale"));
  GfMenuObject::initialize();
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

void GfMenuObjDrKizunaRing::setupRing(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  GfMenuAdapterManager::beginAddAfter();
  for (u16 level = 1; level <= 3; level++) {
    u16 line = 0;
    for (int node = level; node != level + 15; node += 3) {
      name.format("IMG_node_icon@%02d", node);
      u32 icon = acc.searchChild(name.c_str());
      if (icon != 0) {
        GfMenuSkillAdapter::createFromReferenceDriver(icon, 3, 0, line, level, 2, true);
        name.format("IMG_node_base@%02d", node);
        u32 base = acc.searchChild(name.c_str());
        if (base != 0) {
          GfMenuSkillAdapter::createFromReferenceDriver(base, 5, 0, line, level, 2, true);
        }
      }
      line++;
    }
  }
  {
    ui::UIObjectAcc image(acc.unknown10, "IMG_dr_image");
    GfMenuCharDataAdapter::createFromReferenceDriver(image.unknown10, 3, 0, false);
  }
  for (u16 level = 1; level <= 3; level++) {
    mm::mtl::FixStr<32> lockName;
    lockName.format("IMG_lock_icon@%02d", level);
    GfMenuSkillAdapter::createFromReferenceDriver(acc.searchChild(lockName.c_str()), 7, 0, 0, level, 2, true);
  }
  GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjDrKizunaRing::setupRingList(ui::UIObjectAcc &acc, ui::UISelectObjList *list) {
  mm::mtl::FixStr<32> name;
  list->clear();
  for (int level = 1; level <= 3; level++) {
    name.format("LAY_lock@%02d", level);
    u32 lock = acc.searchChild(name.c_str());
    if (lock != 0) {
      list->addObject(lock);
      for (int row = 0; row < 5; row++) {
        name.format("LAY_skillspot_RL@%02d", level + row * 3);
        u32 spot = acc.searchChild(name.c_str());
        if (spot != 0) {
          list->addObject(spot);
        }
      }
    }
  }
}

void GfMenuObjDrKizunaRing::refreshRing(ui::UIObjectAcc &acc) {
  u32 driver = GfMenuReference::getReferenceDriverID(0);
  bool isHidden = GfMenuReference::getReferenceNumber(2) != 0;
  mm::mtl::FixStr<32> name;
  for (u32 level = 0; level < 3; level++) {
    for (u32 row = 0; row < 5; row++) {
      int node = level + 1 + row * 3;
      name.format("IMG_node_icon@%02d", node);
      ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
      if (icon.isValid()) {
        name.format("IMG_node_base@%02d", node);
        ui::UIObjectAcc base(acc.searchChild(name.c_str()));
        if (base.isValid()) {
          if (!GfDataDriverSkill::isSkillUnlock(driver, row, level + 1, isHidden)) {
            icon.setMulColor("white");
            base.setMulColor("gray");
          } else if (GfDataDriverSkill::getSkill(driver, row, level + 1, isHidden) == 0) {
            icon.setMulColor("black");
            base.setMulColor("gray");
          } else {
            icon.setMulColor("white");
            base.setMulColor("white");
          }
        }
      }
    }
  }
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

bool GfMenuObjDrKizunaRing::seqSkillAnime() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc main(acc.searchChild("LAY_dr_main"));
  ui::UIObjectAcc open(main.searchChild("IMG_skill_open"));
  int index = GfMenuReference::getReferenceNumber(0);
  u32 level = GfMenuReference::getReferenceNumber(1);
  bool isEnd;
  if (unknown2f8 == 0) {
    mm::mtl::FixStr<32> name;
    name.format("skillspot2_R%1dL%1d", index + 1, level);
    mm::Rect<s16> rect;
    main.getLayoutRect(name.c_str(), rect);
    mm::Pnt<s16> center;
    center.x = rect.x + rect.width / 2;
    center.y = rect.y + rect.height / 2;
    open.setPosCenter(center);
    open.startAnimation("skill_learn", false);
    open.setDisp(true);
    GfMenuObjUtil::playSE(15);
    bool isHidden = GfMenuReference::getReferenceNumber(2) != 0;
    u32 driver = GfMenuReference::getReferenceDriverID(0);
    SCOM_FIELD_VOICE::createDriverKizuna(driver);
    bool isUnlock1 = GfDataDriverSkill::isSkillLevelUnlock(driver, 1, isHidden);
    bool isUnlock2 = GfDataDriverSkill::isSkillLevelUnlock(driver, 2, isHidden);
    bool isUnlock3 = GfDataDriverSkill::isSkillLevelUnlock(driver, 3, isHidden);
    u32 column = 1;
    if (isUnlock1) {
      column = 2;
    }
    if (isUnlock2) {
      column = 3;
    }
    if (isUnlock3) {
      column = 4;
    }
    if (GfDataDriverSkill::getSkillLevelUnlockNum(driver, column, isHidden) == 1) {
      unknown68.unknown002(&GfMenuObjDrKizunaRing::seqUnlockAnime);
      unknown68.unknown002(&GfMenuObjDrKizunaRing::seqCircleAnime);
      unknown68.unknown002(&GfMenuObjDrKizunaRing::seqOpenAnime);
    }
    unknown68.unknown002(&GfMenuObjDrKizunaRing::seqExecSkill);
    unknown68.unknown002(&GfMenuObjDrKizunaRing::seqComplete);
    unknown68.unknown002(&GfMenuObjDrKizunaRing::seqEndAnime);
    isEnd = false;
    unknown2f8++;
  } else if (!open.isPlayingAnimation()) {
    unknown2f8 = 0;
    refreshRing(main);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjDrKizunaRing::seqEndAnime() {
  getSkillUnlockLevel(GfMenuReference::getReferenceDriverID(0));
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc main(acc.searchChild("LAY_dr_main"));
  unknown164(acc.searchChild("LAY_dr_main"), GfMenuTypes::unknown003_258);
  unknown163(acc.searchChild("LAY_skill_info"), GfMenuTypes::unknown003_33, 0);
  ui::UIObjectAcc cursor(acc.searchChild("IMG_pointcursor"));
  cursor.setDisp(true);
  cursor.startAnimation("loop", false);
  GfMenuObjMainMenu2::setCloseKeyEnable(true);
  ui::UIObjectAcc ring(unknown18, "LAY_dr_main");
  GfMenuObjMainMenu2::openCharChange(ring.unknown10, 0, false);
  return true;
}

void GfMenuObjDrKizunaRing::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupMain(acc);
    getSkillUnlockLevel(GfMenuReference::getReferenceDriverID(0));
    GfMenuReference::setReferenceNumber(0, 0);
    GfMenuReference::setReferenceNumber(1, 1);
    GfMenuReference::setReferenceNumber(2, 0);
    GfMenuObjOperationInfo::add(acc.searchChild("LAY_scale"), acc.searchChild("LAY_dr_main"), 0, 0);
    GfMenuObjOperationInfo::setGuideText(0x10, 0);
    GfMenuObjMainMenu2::setSubIndexText(7);
    GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::unknown002(handle));
    GfMenuObjUtil::setPointSpeedRate(ui::UIObjectAcc(acc.searchChild("LAY_dr_main")), gmo_dr_kizuna_ring::rateTbl[0]);
    break;
  case 3:
    if (event.unknown08 == 1) {
      unknown164(acc.searchChild("LAY_dr_main"), GfMenuTypes::unknown003_258);
      ui::UIObjectAcc cursor(acc.searchChild("IMG_pointcursor"));
      cursor.startAnimation("loop", false);
      cursor.setDisp(true);
    } else if (event.unknown08 == 2) {
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObjUtil::setPointSpeedRate(ui::UIObjectAcc(acc.searchChild("LAY_dr_main")), 1.0f);
      GfMenuObjOperationInfo::remove(acc.searchChild("LAY_scale"), acc.searchChild("LAY_dr_main"), 0, 0);
      GfMenuObjCharSelect::returnSubMenu();
      GfMenuObject::returnFSSubLayer(unknown20);
    }
    break;
  case 0x21:
    acc.setDisp(true);
    break;
  case 0x22:
    GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::unknown003(handle));
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjDrKizunaRing::DriverStockSPListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupDriverSkillInfo(owner);
    break;
  case 8:
  case 0x105:
  case 0x106:
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjDrKizunaRing::SkillDetailListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupSkillDetail(acc);
    unknown20->unknown38 = false;
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_33: {
    ui::UIObjectAcc caption(acc.searchChild("LAY_caption"));
    caption.setDisp(true);
    const char *name = isScreenLR(unknown20->unknown40 % 6) ? "drskillinfo2_2" : "drskillinfo2_1";
    mm::Rect<s16> rect;
    ui::UIObjectAcc main(owner.searchChild("LAY_dr_main"));
    main.getLayoutRect(name, rect);
    mm::Pnt<s16> pos;
    pos.x = rect.x;
    pos.y = rect.y;
    acc.setPos(pos);
    if (unknown20->unknown3c == 0) {
      ui::UIObjectAcc skill(acc.searchChild("LAY_skif_skill"));
      skill.setDisp(true);
      ui::UIObjectAcc lock(acc.searchChild("LAY_skif_lock"));
      lock.setDisp(false);
    } else {
      ui::UIObjectAcc skill(acc.searchChild("LAY_skif_skill"));
      skill.setDisp(false);
      ui::UIObjectAcc lock(acc.searchChild("LAY_skif_lock"));
      lock.setDisp(true);
    }
    if (!unknown20->unknown38) {
      setFadeIn(handle);
      unknown20->unknown38 = true;
    }
    u32 driver = GfMenuReference::getReferenceDriverID(0);
    u32 row = GfMenuReference::getReferenceNumber(0);
    u32 level = GfMenuReference::getReferenceNumber(1);
    int hidden = GfMenuReference::getReferenceNumber(2);
    ui::UIObjectAcc icon(acc.searchChild("IMG_skif_icon@01"));
    ui::UIObjectAcc base(acc.searchChild("IMG_skif_icon_base@01"));
    if (!GfDataDriverSkill::isSkillUnlock(driver, row, level, hidden != 0)) {
      icon.setMulColor("white");
      base.setMulColor("gray");
    } else if (GfDataDriverSkill::getSkill(driver, row, level, hidden != 0) == 0) {
      icon.setMulColor("black");
      base.setMulColor("gray");
    } else {
      icon.setMulColor("white");
      base.setMulColor("white");
    }
    break;
  }
  case GfMenuTypes::unknown003_34:
    if (unknown20->unknown38) {
      unknown20->unknown38 = false;
      setFadeOut(handle);
    }
    break;
  case GfMenuTypes::unknown003_257:
    if (!unknown20->unknown38) {
      setFadeIn(handle);
      unknown20->unknown38 = true;
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool gf::GfMenuSequence<gf::GfMenuObjDrKizunaRing, 8>::wait();
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjDrKizunaRing, 8>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjDrKizunaRing>(const mm::mtl::Delegate<bool()> *);
