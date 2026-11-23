#include "gf/menu/object/gf_menu_obj_lvup_main.h"

#include "gf/data/gf_data_driver.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/gf_info.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/menu/object/gf_menu_obj_lvup_select.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/sound/gf_sound.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjLvupMain::GfMenuObjLvupMain(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), m_menuDriverList(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(0xff), unknown50(this), unknown2e0(false), unknown2e4(0),
      unknown2f0(nullptr), unknown2f8(nullptr), unknown300(false) {
  unknown2f0 = GfMenuCallContext::create();
  unknown2f8 = GfMenuCallContext::create();
}

GfMenuObjLvupMain::~GfMenuObjLvupMain() {
  mm::mtl::safeRelease(unknown2f0);
  mm::mtl::safeRelease(unknown2f8);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(m_menuDriverList);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjLvupMain::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  mm::mtl::FixStr<32> name;
// __LINE__ must be 103 as in the original file: it is the line argument of operator new.
#line 103
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_contents"), mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  m_menuDriverList = GfMenuDriverList::create();
  {
    ui::UIObjectAcc menu(main.unknown10, "LAY_mode_menu");
    ui::UISelectObjList::CreateParam createParam;
    createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
    unknown28 = ui::UISelectObjList::create(createParam);
    unknown28->pickupObject(menu.unknown10, "LAY_mode_sltag@%02d", 1);
// __LINE__ must be 120 as in the original file: it is the line argument of operator new.
#line 120
    MenuListener *menuListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MenuListener(this);
    menuListener->addRef();
    ui::UIEventManager::get()->registObjectListener(menu.unknown10, menuListener);
    if (menuListener != nullptr) {
      menuListener->release();
    }
  }
  {
    ui::UIObjectAcc driverSet(main.unknown10, "LAY_lv_driverset");
    {
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown38 = ui::UISelectObjList::create(createParam);
    }
    unknown38->pickupObject(driverSet.unknown10, "LAY_lv_drinfo@%02d", 1);
    MM_VERIFY(unknown38->getSize());
    {
      GfMenuDriverList::PartySetup setup;
      setup.unknown18 = false;
      setup.unknown14 = GfPartySelect::LIST_TYPE_UNKNOWN_2;
      setup.m_setupParam.unknown08 = unknown38->getSize();
      m_menuDriverList->setupFromParty(setup);
    }
    {
      ui::UICtrlCursorSelect::CursorSetting setting;
      setting.setType(0);
      setting.unknown18 = 0;
      unknown40 = ui::UICtrlCursorSelect::create(driverSet.searchChild("IMG_lv_drcursor"), setting, unknown38);
    }
    for (u32 i = 0; i < unknown38->getSize(); i++) {
      name.format("TXT_lv_drname@%02d", i + 1);
      GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromDriverList(driverSet.searchChild(name.c_str()), 2, m_menuDriverList, i, false);
      if (adapter != nullptr) {
        name.format("LAY_lv_drinfo@%02d", i + 1);
        adapter->unknown24 = driverSet.searchChild(name.c_str());
      }
      name.format("IMG_lv_drimage@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(driverSet.searchChild(name.c_str()), 3, m_menuDriverList, i, false);
      name.format("TXT_lv_lvnum_num@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(driverSet.searchChild(name.c_str()), 1, m_menuDriverList, i, true);
      name.format("TXT_lv_lvupeff_num@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(driverSet.searchChild(name.c_str()), 1, m_menuDriverList, i, true);
      name.format("TXT_lv_nowexp_num@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(driverSet.searchChild(name.c_str()), 0x13, m_menuDriverList, i, true);
      name.format("TXT_lv_nexp_num@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(driverSet.searchChild(name.c_str()), 0x14, m_menuDriverList, i, true);
      name.format("TXT_lv_bexp_num@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(driverSet.searchChild(name.c_str()), 0x15, m_menuDriverList, i, true);
      name.format("IMG_lv_exp_gauge_exp@%02d", i + 1);
      {
        ui::UIObjectAcc gauge(driverSet.unknown10, name.c_str());
        GfMenuCharDataAdapter::createFromDriverList(gauge.unknown10, 0x16, m_menuDriverList, i, true);
        gauge.setExtType(1);
      }
      name.format("IMG_lv_exp_gauge_bexp@%02d", i + 1);
      {
        ui::UIObjectAcc gauge(driverSet.unknown10, name.c_str());
        GfMenuCharDataAdapter::createFromDriverList(driverSet.searchChild(name.c_str()), 0x17, m_menuDriverList, i, true);
        gauge.setExtType(1);
      }
    }
// __LINE__ must be 209 as in the original file: it is the line argument of operator new.
#line 209
    SelectListener *selectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SelectListener(this);
    selectListener->addRef();
    ui::UIEventManager::get()->registObjectListener(driverSet.unknown10, selectListener);
    if (selectListener != nullptr) {
      selectListener->release();
    }
    GfMenuObject::setFSInputObject(1, driverSet.unknown10);
  }
  GfMenuObject::initialize();
}

void GfMenuObjLvupMain::finalize() { GfMenuObject::finalize(); }

void GfMenuObjLvupMain::update() {
  unknown50.unknown003();
  GfMenuObject::update();
}

void GfMenuObjLvupMain::refreshLevelUpInfo() {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < m_menuDriverList->getSize(); i++) {
    u32 driver = m_menuDriverList->getContents(i).unknown00;
    ui::UIObjectAcc acc(unknown38->getObject(i));
    bool enable = GfDataDriver::isEnableLevelUp(driver);
    name.format("LAY_lv_lvup_enable@%02d", i + 1);
    acc.setDispChild(enable, name.c_str());
    name.format("IMG_lv_lvup_enable@%02d", i + 1);
    ui::UIObjectAcc image(acc.unknown10, name.c_str());
    image.startAnimation("loop", false);
  }
}

bool GfMenuObjLvupMain::seqClose() {
  // The game computes the frames of two seconds as a float before the fade out call and converts them to an integer after the accessor is built; converting first, or writing 2.0f / m_fSecPerFrame,
  // gives 91 instructions instead of 93.
  f32 frameCount = 1.0f / GfInfo::m_fSecPerFrame + 1.0f / GfInfo::m_fSecPerFrame;
  GfMenuSoundManager::fadeOutFieldBgm(2.0f);
  // The game builds and destroys this accessor without using it.
  ui::UIObjectAcc main(unknown18);
  u32 frames = static_cast<u32>(frameCount);
  GfMenuObjFade::StartParam param;
  param.unknown00 = 2;
  param.unknown04 = 0.0f;
  param.unknown08 = 0.0f;
  param.unknown0c = 0.0f;
  param.unknown10 = 1.0f;
  param.unknown02 = frames;
  GfMenuObjFade::start(param);
  unknown50.unknown004(frames);
  unknown50.unknown002(&GfMenuObjLvupMain::seqClose2);
  return true;
}

bool GfMenuObjLvupMain::seqClose2() {
  m_soundHandle = GfMenuObjUtil::playJingle(4);
  unknown50.unknown002(&GfMenuObjLvupMain::seqClose3);
  return true;
}

bool GfMenuObjLvupMain::seqClose3() {
  bool isEnd;
  if (GfSound::get() == nullptr || !GfSound::get()->isPlaying(m_soundHandle)) {
    GfMenuSoundManager::fadeInFieldBgm(2.0f);
    GfMenuObjOperationInfo::close();
    isEnd = true;
    closeFSLayer(unknown18, true, true);
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjLvupMain::seqEndLevelUp() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  u32 index = m_menuDriverList->getIndex(true);
  mm::mtl::FixStr<32> name;
  name.format("IMG_lv_lvup_eff@%02d", index + 1);
  ui::UIObjectAcc effect(main.unknown10, name.c_str());
  bool isEnd;
  if (!effect.isPlayingAnimation()) {
    sendOpenEvent(main.searchChild("LAY_lv_driverset"), 0, 0.0f);
    refreshLevelUpInfo();
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjLvupMain::seqExecLevelUp() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  u32 index = m_menuDriverList->getIndex(true) + 1;
  mm::mtl::FixStr<32> name;
  name.format("IMG_lv_lvup_eff@%02d", index);
  ui::UIObjectAcc effect(main.unknown10, name.c_str());
  effect.startAnimation("fade_in", false);
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "mnu061_levelup";
  param.unknown58 = "fade_in";
  param.unknown11 = true;
  param.unknown14 = 10;
  name.format("TXT_lv_lvup_text@%02d", index);
  ui::UIObjectAcc text(main.unknown10, name.c_str());
  GfMenuObjUtil::startCtrl(text.unknown10, param, nullptr);
  param.unknown08 = 0x10000000;
  param.unknown50 = "mnu061_levelup_shadow";
  param.unknown58 = "fade_in";
  param.unknown11 = true;
  param.unknown14 = 10;
  name.format("IMG_lv_lvup_text_bg@%02d", index);
  ui::UIObjectAcc background(main.unknown10, name.c_str());
  GfMenuObjUtil::startCtrl(background.unknown10, param, nullptr);
  GfMenuObjUtil::playJingle(5);
  return true;
}

void GfMenuObjLvupMain::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjUtil::unknown002(acc.unknown10);
    m_menuObjLvupMain->refreshLevelUpInfo();
    break;
  case 3:
    if (event.unknown08 == 1) {
      if (!m_menuObjLvupMain->unknown300) {
        sendOpenEvent(acc.searchChild("LAY_lv_driverset"), 0, 0.0f);
      } else {
        m_menuObjLvupMain->unknown2e0 = false;
        m_menuObjLvupMain->unknown50.unknown005();
        m_menuObjLvupMain->unknown50.unknown002(&GfMenuObjLvupMain::seqExecLevelUp);
        m_menuObjLvupMain->unknown50.unknown002(&GfMenuObjLvupMain::seqEndLevelUp);
      }
    }
    break;
  case 0x41: {
    u32 call = event.unknown08;
    if (m_menuObjLvupMain->unknown2f8->unknown0c == call) {
      if (event.unknown10 == 0) {
        m_menuObjLvupMain->unknown300 = true;
      } else {
        m_menuObjLvupMain->unknown300 = false;
      }
    }
    break;
  }
  case 0x42:
    if (event.unknown08 == m_menuObjLvupMain->unknown2f8->unknown0c) {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown00 = 6;
      param.unknown04 = 0;
      param.unknown10 = 1;
      GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
      m_menuObjLvupMain->refreshLevelUpInfo();
      GfMenuObjOperationInfo::setGuideDisp(true);
      mm::mtl::FixStr<32> name;
      if (m_menuObjLvupMain->unknown300) {
        name.format("LAY_lv_lvup_enable@%02d", m_menuObjLvupMain->m_menuDriverList->getIndex(true) + 1);
        ui::UIObjectAcc enable(acc.unknown10, name.c_str());
        enable.setDisp(false);
      }
    }
    break;
  case 0x100: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 6;
    param.unknown04 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    GfMenuObjOperationInfo::setGuideDisp(false);
    GfMenuDriverList *list = m_menuObjLvupMain->m_menuDriverList;
    GfMenuCallContext *context = m_menuObjLvupMain->unknown2f8;
    GfMenuObjLvupSelect::openLevelSelect(context, list->getContents(list->getIndex(false)).unknown00);
    m_menuObjLvupMain->unknown300 = false;
    GfMenuObject::setCallContextEventHandler(m_menuObjLvupMain->unknown2f8, acc.unknown10);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjLvupMain::MenuListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::setupInputSelectionFromList(acc.unknown10, *m_menuObjLvupMain->unknown28);
    acc.setDisp(false);
    return;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(0);
    }
    return;
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      u32 previous = event.unknown0c;
      mm::mtl::FixStr<32> name;
      if (previous != 0xffffffff) {
        name.format("IMG_mode_slbase@%02d", previous + 1);
        ui::UIObjectAcc base(m_menuObjLvupMain->unknown28->getObject(previous), name.c_str());
        base.setImageIndex(0);
      }
      name.format("IMG_mode_slbase@%02d", index + 1);
      ui::UIObjectAcc base(m_menuObjLvupMain->unknown28->getObject(index), name.c_str());
      base.setImageIndex(1);
      m_menuObjLvupMain->unknown28->setIndex(index);
    }
    return;
  }
  case 8:
    if (event.unknown08_u64 >> 32 == 1) {
      int type = event.unknown08_u64;
      if (type == 3) {
        closeFSLayer(acc.unknown10, true, true);
        m_menuObjLvupMain->unknown48 = 3;
      } else if (type == 1 || type == 2) {
        sendOpenEvent(acc.searchSibiling("LAY_lv_driverset"), 0, 0.0f);
        m_menuObjLvupMain->m_menuDriverList->setIndex(0);
        m_menuObjLvupMain->unknown48 = type;
        sendCloseEvent(acc.unknown10, 0, 0.0f);
        disableFSInput();
      } else {
        m_menuObjLvupMain->unknown48 = type;
      }
    }
    return;
  case 0x21: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    return;
  }
  case 0x22: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 1;
    param.unknown10 = 2;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    return;
  }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjLvupMain::SelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDispChild(false, "IMG_lv_drcursor");
    GfMenuObjOperationInfo::open(acc.unknown10, 0, 0, 0);
    GfMenuObjOperationInfo::setGuideText(0x2a, 2);
    return;
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      u32 previous = event.unknown0c;
      m_menuObjLvupMain->unknown38->setIndex(index);
      m_menuObjLvupMain->m_menuDriverList->setIndex(index);
      acc.setDispChild(true, "IMG_lv_drcursor");
      if (previous != 0xffffffff && index != previous) {
        GfMenuObjUtil::playSECommonCursor();
      }
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      if (!GfDataDriver::isEnableLevelUp(m_menuObjLvupMain->m_menuDriverList->getContents(m_menuObjLvupMain->m_menuDriverList->getIndex(false)).unknown00)) {
        GfMenuObjUtil::playSECommon(2);
      } else if (m_menuObjLvupMain->unknown48 == 2) {
        ui::EventData sendData;
        sendData.unknown00 = 0x100;
        sendEventToParent(acc.unknown10, sendData, 0.0f);
        GfMenuObjUtil::playSECommonDecide();
        disableFSInput();
      }
    } else if (event.unknown0c == 2) {
      GfMenuObjCommonText::open(m_menuObjLvupMain->unknown2f0, 0xa5, 0);
      GfMenuObject::setCallContextEventHandler(m_menuObjLvupMain->unknown2f0, acc.unknown10);
    }
    return;
  case 0x21:
    resetInputSelection(acc.unknown10);
    setupInputSelectionFromList(acc.unknown10, *m_menuObjLvupMain->m_menuDriverList);
    enableFSInput(1);
    m_menuObjLvupMain->unknown48 = 2;
    return;
  case 0x22:
    acc.setDispChild(false, "IMG_lv_drcursor");
    return;
  case 0x41:
    if ((event.unknown10 | event.unknown14) == 0) {
      u32 call = event.unknown08;
      if (m_menuObjLvupMain->unknown2f0->unknown0c == call) {
        m_menuObjLvupMain->unknown50.unknown005();
        m_menuObjLvupMain->unknown50.unknown002(&GfMenuObjLvupMain::seqClose);
        disableFSInput();
      }
    }
    return;
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

} // namespace gf

template bool gf::GfMenuSequence<gf::GfMenuObjLvupMain, 8>::wait();
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjLvupMain, 8>>(const mm::mtl::Delegate<bool()> *);
