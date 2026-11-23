#include "gf/menu/object/gf_menu_obj_lvup_select.h"

#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_cmn_status.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x57;
// Inferred role: common window of the level up confirmation; original name unknown.
constexpr u16 unknown002 = 0xa7;

GfMenuObjLvupSelect::GfMenuObjLvupSelect(u32 handle) : GfMenuObject(handle), unknown28(this), unknown2b8(false), m_menuCallContext(nullptr) {
  unknown2c8 = unknown160();
  unknown2d0 = unknown160();
  m_menuCallContext = GfMenuCallContext::create();
}

GfMenuObjLvupSelect::~GfMenuObjLvupSelect() {
  mm::mtl::safeRelease(m_menuCallContext);
  unknown2d0 = nullptr;
  unknown2c8 = nullptr;
}

void GfMenuObjLvupSelect::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  // The three listener registrations of this function (here and at lines 146 and 157 of the original file) repeat the same statements (add a reference, register, release): written
  // out because a file-local helper taking the listener does not match, 320 instructions against the game's 317 with the reference added inside it (as a template or on the base
  // pointer; the constructor stores of the first listener, 0x71004813d0, change) and 317 with the reference added by the caller (a register differs); ruling 8, the same block is
  // written out in the other menu objects' initialize.
// __LINE__ must be 116, 146 and 157 as in the original file: it is the line argument of operator new.
#line 116
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main.unknown10);
  {
    ui::UIObjectAcc select(main.unknown10, "LAY_lvup_sellect");
    int count = select.countChild("LAY_lvslc_lvset@%02d", 1);
    int offset = -(count / 2);
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < count; i++) {
      name.format("TXT_lvslc_lvnum@%02d", i + 1);
      GfMenuReferenceAdapter *adapter = GfMenuReferenceAdapter::create(select.searchChild(name.c_str()), unknown2c8, true);
      if (adapter != nullptr) {
        adapter->unknown44 = offset;
        offset++;
        name.format("LAY_lvslc_lvset@%02d", i + 1);
        adapter->unknown24 = select.searchChild(name.c_str());
      }
    }
#line 146
    SelectListener *selectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SelectListener(this);
    selectListener->addRef();
    ui::UIEventManager::get()->registObjectListener(select.unknown10, selectListener);
    if (selectListener != nullptr) {
      selectListener->release();
    }
  }
  {
    ui::UIObjectAcc image(main.unknown10, "LAY_dr_img");
    GfMenuCharDataAdapter::createFromReferenceDriver(image.searchChild("IMG_dr_img"), 0x1c, 0, false);
#line 157
    DrImgListener *imageListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DrImgListener(this);
    imageListener->addRef();
    ui::UIEventManager::get()->registObjectListener(image.unknown10, imageListener);
    if (imageListener != nullptr) {
      imageListener->release();
    }
  }
  {
    ui::UIObjectAcc bonus(main.unknown10, "LAY_bonus_exp");
    GfMenuReferenceAdapter::create(bonus.searchChild("TXT_bonus_exp_num"), unknown2d0, false);
    unknown2d0->unknown162(0);
    unknown2d0->unknown165(0);
    unknown2d0->unknown166(999999999);
  }
  GfMenuObject::initialize();
}

void GfMenuObjLvupSelect::finalize() { GfMenuObject::finalize(); }

void GfMenuObjLvupSelect::update() {
  unknown28.unknown003();
  GfMenuObject::update();
}

void GfMenuObjLvupSelect::updateBonusExp() {
  u32 driver = GfMenuReference::getReferenceDriverID(0);
  if (driver != 0) {
    DataParamAcc acc(OBJECT_TYPE_PC, driver, GIMMICK_TYPE_UNKNOWN_0);
    if (acc.isValid()) {
      u32 battleExp;
      u32 exp = acc.getExp();
      u32 level = acc.getLevel(false);
      u32 virtualLevel = GfMenuReference::getDriverVirtualLevel();
      if (level < virtualLevel) {
        battleExp = acc.getBattleExp();
        GfBdatBtl *bdatBattle = GfBdatBtl::get();
        for (u32 i = 0; i < virtualLevel - level; i++) {
          u32 growExp = bdatBattle->getGrowLevelExp(level + i + 1);
          exp = battleExp + exp - growExp;
          battleExp = 0;
        }
      }
      unknown2d0->unknown0c = exp;
    }
  }
}

bool GfMenuObjLvupSelect::seqConfirmLevelUp() {
  if (!unknown2b8) {
    GfMenuManager::openCommonWindow(unknown002);
    unknown2b8 = true;
    return false;
  }
  if (!GfMenuManager::isOpenCommonWindow()) {
    s16 result = GfMenuManager::getCommonWindowResult();
    if (result == 0) {
      unknown28.unknown002(&GfMenuObjLvupSelect::seqExecLevelUp);
    } else {
      enableFSInput(4);
    }
    unknown2b8 = false;
    return true;
  }
  return false;
}

bool GfMenuObjLvupSelect::seqExecLevelUp() {
  ui::UIObjectAcc effect(unknown18, "IMG_lv_lvupeff@01");
  if (!unknown2b8) {
    effect.startAnimation("start", false);
    effect.setDisp(true);
    ui::UIObjectAcc number(unknown18, "LAY_lv_lvupeff_num@01");
    number.setDisp(true);
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x22;
    param.unknown00 = 1.0f;
    param.unknown20 = 0x20;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(number.unknown10, param, nullptr);
    GfGameUtil::execLevelUp(GfMenuReference::getReferenceDriverID(0), unknown2c0);
    unknown2b8 = true;
    return false;
  }
  if (effect.isPlayingAnimation()) {
    return false;
  }
  effect.setDisp(false);
  ui::UIObjectAcc(unknown18, "LAY_lv_lvupeff_num@01").setDisp(false);
  {
    ui::UIObjectAcc select(unknown18, "LAY_lvup_sellect");
    GfMenuObject::sendCloseEvent(select.unknown10, 0, 0.0f);
  }
  {
    ui::UIObjectAcc main(unknown18, "LAY_main");
    GfMenuObject::sendCloseEvent(main.unknown10, 0, 0.0f);
  }
  ui::UIObjectAcc main(unknown18, "LAY_main");
  GfMenuObject::addResultCallContext(main.unknown10, 0, 0);
  return true;
}

void GfMenuObjLvupSelect::openLevelSelect(GfMenuCallContext *context, u32 level) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCStart(context)) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = 0;
    event.unknown0c = level;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
  }
}

void GfMenuObjLvupSelect::openLevelup(GfMenuCallContext *context, u32 level, u32 levelMax) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCStart(context)) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = 0;
    event.unknown0c = level;
    event.unknown10 = levelMax;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
  }
}

void GfMenuObjLvupSelect::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case GfMenuTypes::unknown003_33: {
    u32 driver = event.unknown0c;
    GfMenuReference::setReferenceDriverID(0, driver);
    GfMenuReference::setDriverVirtualLevel(GfDataDriver::getLevel(driver) + 1);
    m_menuObjLvupSelect->updateBonusExp();
    GfMenuObject::sendOpenEvent(acc.searchChild("LAY_lvup_sellect"), 0, 0.0f);
    GfMenuObject::sendOpenEvent(acc.searchSibiling("LAY_dr_img"), 0, 0.0f);
    break;
  }
  case GfMenuTypes::unknown003_34:
    GfMenuObject::termCallContext(acc.unknown10);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjLvupSelect::SelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::setFSInputObject(4, acc.unknown10);
    acc.setDisp(false);
    break;
  case 3:
    switch (event.unknown08) {
    case 1:
      GfMenuObject::enableFSInput(4);
      break;
    case 2:
      GfMenuReference::resetDriverVirtual();
      break;
    }
    break;
  case 6: {
    int index = event.unknown08;
    if (index != -1) {
      int previous = event.unknown0c;
      int level = GfDataDriver::getLevel(GfMenuReference::getReferenceDriverID(0));
      m_menuObjLvupSelect->unknown2c8->unknown162(index + level + 1);
      GfMenuReference::setDriverVirtualLevel(index + level + 1);
      // Each statement reads unknown2c8 through its own operator-> (one `_ptr != 0` assert before the loads, 0x7100481bc4 and 0x7100481c04); the form without the locals calls it twice
      // per statement and gives 290 instructions against the game's 264.
      GfMenuReferenceNumber *numberMin = m_menuObjLvupSelect->unknown2c8.operator->();
      acc.setDispChild(numberMin->unknown0c != numberMin->unknown10, "IMG_lvslc_arrow@01");
      GfMenuReferenceNumber *numberMax = m_menuObjLvupSelect->unknown2c8.operator->();
      acc.setDispChild(numberMax->unknown0c != numberMax->unknown14, "IMG_lvslc_arrow@02");
      m_menuObjLvupSelect->updateBonusExp();
      if (previous != -1 && index != previous) {
        GfMenuObjUtil::playSECommonCursor();
      }
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      int index = event.unknown08;
      int level = GfDataDriver::getLevel(GfMenuReference::getReferenceDriverID(0));
      m_menuObjLvupSelect->unknown2c0 = index + level + 1;
      m_menuObjLvupSelect->unknown2b8 = false;
      m_menuObjLvupSelect->unknown28.unknown002(&GfMenuObjLvupSelect::seqConfirmLevelUp);
    } else if (event.unknown0c == 2) {
      GfMenuObject::addResultCallContext(acc.getParentHandle(), 1, 0);
      GfMenuObject::sendCloseEvent(acc.getParentHandle(), 0, 0.0f);
      GfMenuObjUtil::playSECommonCancel();
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
    } else {
      break;
    }
    GfMenuObject::disableFSInput();
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    u32 driver = GfMenuReference::getReferenceDriverID(0);
    int level = GfDataDriver::getLevel(driver);
    u32 next = level + 1;
    u32 enableLevel;
    u32 maxLevel;
    GfDataDriver::getEnableLevel(enableLevel, maxLevel, driver);
    if (enableLevel < next) {
      enableLevel = next;
    }
    GfMenuObject::resetInputSelection(acc.unknown10);
    GfMenuObject::setupInputSelection(acc.unknown10, 0, enableLevel - level);
    m_menuObjLvupSelect->unknown2c8->unknown162(next);
    m_menuObjLvupSelect->unknown2c8->unknown165(next);
    m_menuObjLvupSelect->unknown2c8->unknown166(enableLevel);
    GfMenuObjCmnStatus::openDrStatus(1, 0);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown04 = 1;
    param.unknown00 = 6;
    param.unknown10 = 2;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    GfMenuObject::sendCloseEvent(acc.searchSibiling("LAY_dr_img"), 0, 0.0f);
    GfMenuObjCmnStatus::closeDrStatus();
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjLvupSelect::DrImgListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown04 = 1;
    param.unknown00 = 6;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjLvupSelect>(const mm::mtl::Delegate<bool()> *);
