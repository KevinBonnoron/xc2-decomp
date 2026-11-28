#include "gf/menu/object/gf_menu_obj_party_form3.h"

#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_party_status.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: menu id; original name unknown.
constexpr u32 unknown001 = 0x24;

// Inferred role: call id of the party form layout; original name unknown.
constexpr u32 CALL_UNKNOWN_98 = 98;

GfMenuObjPartyForm3::GfMenuObjPartyForm3(u32 handle)
    : GfMenuObject(handle), m_menuDriverList(nullptr), unknown30(0), unknown34(0), unknown38(0), unknown3c(0), unknown40(-1), unknown44(false), unknown80(this), m_menuCallContext(nullptr),
      unknown318(true), unknown319(false) {
  unknown48.assign(mm::mtl::IntrusivePtr<GfMenuReferenceNumber>());
}

GfMenuObjPartyForm3::~GfMenuObjPartyForm3() {
  unknown48.assign(mm::mtl::IntrusivePtr<GfMenuReferenceNumber>());
  mm::mtl::safeRelease(m_menuDriverList);
  mm::mtl::safeRelease(m_menuCallContext);
}

void GfMenuObjPartyForm3::initialize() {
  unknown318 = !GfGameCond::isGameCond(0xa70);
  {
    GfMenuTypes::Param layerParam;
    if (getFSLayerParam(unknown20, layerParam)) {
      unknown30 = layerParam.get<OpenParam>().unknown00;
      removeFSLayerParam(unknown20);
    }
  }
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 173 as in the original file: it is the line argument of operator new.
#line 173
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_98, main);
  u32 bg = acc.searchChild("LAY_bg");
// __LINE__ must be 179 as in the original file: it is the line argument of operator new.
#line 179
  BGListener *bgListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) BGListener(this);
  bgListener->addRef();
  ui::UIEventManager::get()->registObjectListener(bg, bgListener);
  if (bgListener != nullptr) {
    bgListener->release();
  }
  u32 driverSelect = acc.searchChild("LAY_dr_select");
// __LINE__ must be 183 as in the original file: it is the line argument of operator new.
#line 183
  DriverSelectListener *driverSelectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DriverSelectListener(this);
  driverSelectListener->addRef();
  ui::UIEventManager::get()->registObjectListener(driverSelect, driverSelectListener);
  if (driverSelectListener != nullptr) {
    driverSelectListener->release();
  }
  m_menuDriverList = GfMenuDriverList::create();
  unknown34 = 0;
  unknown38 = 0;
  {
    mm::mtl::FixedVector<u16, 16> drivers;
    GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_UNKNOWN_0, 0);
    unknown34 = drivers.size();
    drivers.clear();
    GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_UNKNOWN_1, 0);
    unknown38 = drivers.size();
    GfMenuDriverList::PartySetup setup;
    setup.unknown14 = GfPartySelect::LIST_TYPE_UNKNOWN_2;
    setup.unknown18 = false;
    m_menuDriverList->setupFromParty(setup);
  }
  if (m_menuDriverList->getSize() == 1) {
    unknown318 = false;
  }
  for (int i = 0; i < 7; i++) {
    unknown48[i] = unknown160();
    unknown48[i]->unknown162(3);
  }
  disableInput(acc.searchChild("LAY_dr_select"));
  GfMenuObject::initialize();
}

void GfMenuObjPartyForm3::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyForm3::update() {
  unknown80.unknown003();
  GfMenuObject::update();
}

void GfMenuObjPartyForm3::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown001), layerParam);
}

void GfMenuObjPartyForm3::setupBGLayout(ui::UIObjectAcc &, u32, bool) {}

void GfMenuObjPartyForm3::setupDriverSelect(ui::UIObjectAcc &acc, GfMenuDriverList *list, u32 first, u32 second, mm::mtl::FixedArray<mm::mtl::IntrusivePtr<GfMenuReferenceNumber>, 7> &numbers) {
  setupDriverLayout(acc, first, second, numbers, 0);
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 7; i++) {
    name.format("LAY_dr@%02d", i + 1);
    ui::UIObjectAcc layer(acc.searchChild(name.c_str()));
    if (i < second + first) {
      name.format("IMG_dr_bustup@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 3, list, i, false);
      name.format("TXT_dr_status_lv_num@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 1, list, i, false);
      name.format("TXT_dr_status_hp_num@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 0, list, i, false);
      name.format("IMG_dr_bl_icon@%02d", i + 1);
      GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 0x1b, list, i, false);
      name.format("IMG_dr_party_no@%02d", i + 1);
      GfMenuReferenceAdapter::create(acc.searchChild(name.c_str()), numbers[i], false);
      if (i == 0) {
        layer.setDispChild(GfGameCond::isGameCond(0xa9d), "IMG_dr_lock@01");
      }
    }
  }
}

void GfMenuObjPartyForm3::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjPartyForm3::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjPartyForm3::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjPartyForm3::seqWaitOpenEnd() {
  ui::UIObjectAcc acc(unknown18, "LAY_dr_select");
  enableInput(acc.unknown10);
  return true;
}

void GfMenuObjPartyForm3::refreshRemoveAddOperation(u32 handle, int index) {
  if (unknown40 >= 0) {
    return;
  }
  u32 count = unknown34;
  if (!unknown318) {
    if (static_cast<u32>(index) < count) {
      GfMenuObjOperationInfo::setActionEnable(handle, 9, false);
      return;
    }
  } else if (static_cast<u32>(index) < count) {
    if (count < 2) {
      GfMenuObjOperationInfo::setActionEnable(handle, 9, false);
      return;
    }
    GfMenuObjOperationInfo::setActionEnable(handle, 9, true);
    GfMenuObjOperationInfo::changeText(handle, 9, false);
    return;
  }
  if (count > 2) {
    GfMenuObjOperationInfo::setActionEnable(handle, 9, false);
  } else {
    GfMenuObjOperationInfo::setActionEnable(handle, 9, true);
    GfMenuObjOperationInfo::changeText(handle, 9, true);
  }
}

bool GfMenuObjPartyForm3::seqAnnounceChange() {
  if (m_menuCallContext != nullptr) {
    return m_menuCallContext->isTerm();
  }
  m_menuCallContext = GfMenuCallContext::create();
  GfMenuObjCommonText::open(m_menuCallContext, 0xd, 0);
  return false;
}

void GfMenuObjPartyForm3::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc main(m_menuObjPartyForm3->unknown18);
  switch (event.unknown00) {
  case 1:
    m_menuObjPartyForm3->unknown80.unknown005();
    if (m_menuObjPartyForm3->unknown30 == 0) {
      GfMenuObjOperationInfo::add(main.searchChild("LAY_dr_select"), 0, 0, 0);
      m_menuObjPartyForm3->refreshRemoveAddOperation(main.searchChild("LAY_dr_select"), 0);
      acc.setDispChild(false, "LAY_index");
      GfMenuObjMainMenu2::setSubIndexText(4);
      GfMenuObjMainMenu2::cancelEnableMainMenu(false);
      GfMenuObjOperationInfo::setGuideText(0xb, 0);
    } else {
      GfMenuObjOperationInfo::open(main.searchChild("LAY_dr_select"), 0, 0, 0);
      m_menuObjPartyForm3->refreshRemoveAddOperation(main.searchChild("LAY_dr_select"), 0);
      m_menuObjPartyForm3->unknown80.unknown002(&GfMenuObjPartyForm3::seqAnnounceChange);
      GfMenuObjOperationInfo::setGuideText(0xb, 2);
    }
    GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeIn(handle, 1, 0));
    break;
  case 2:
    if (m_menuObjPartyForm3->unknown44) {
      mm::mtl::FixedVector<u16, 16> drivers;
      for (u32 i = 0; i < 3; i++) {
        drivers.push_back(i < m_menuObjPartyForm3->unknown34 ? m_menuObjPartyForm3->m_menuDriverList->getContents(i).unknown00 : 0);
      }
      for (u32 i = m_menuObjPartyForm3->unknown34; i < m_menuObjPartyForm3->m_menuDriverList->getSize(); i++) {
        drivers.push_back(m_menuObjPartyForm3->m_menuDriverList->getContents(i).unknown00);
      }
      GfMenuObjPartyStatus::memberChange(1, drivers[0]);
      GfMenuObjPartyStatus::memberChange(2, drivers[1]);
      GfMenuObjPartyStatus::memberChange(3, drivers[2]);
      GfMenuObjUtil::setupPartyDriver(drivers);
    }
    if (m_menuObjPartyForm3->unknown30 == 0) {
      GfMenuObjOperationInfo::remove(main.searchChild("LAY_dr_select"), 0, 0, 0);
    } else {
      GfMenuObjOperationInfo::close();
    }
    GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeOut(handle, 2, 0));
    break;
  case 3:
    if (event.unknown08 == 2) {
      acc.setTerm();
    } else if (event.unknown08 == 1) {
      m_menuObjPartyForm3->unknown80.unknown002(&GfMenuObjPartyForm3::seqWaitOpenEnd);
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    acc.setDisp(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjPartyForm3::BGListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(m_menuObjPartyForm3->unknown18);
  if (event.unknown00 != 1) {
    ui::UIObjectListener::reciveEvent(event, handle);
  }
}

void GfMenuObjPartyForm3::DriverSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(m_menuObjPartyForm3->unknown18);
  switch (event.unknown00) {
  case 1:
    setupDriverSelect(acc, m_menuObjPartyForm3->m_menuDriverList, m_menuObjPartyForm3->unknown34, m_menuObjPartyForm3->unknown38, m_menuObjPartyForm3->unknown48);
    setupInputSelection(handle, 0, m_menuObjPartyForm3->unknown34 + m_menuObjPartyForm3->unknown38);
    disableInput(handle);
    break;
  case 3:
    switch (event.unknown08) {
    case 3:
      setupDriverLayout(acc, m_menuObjPartyForm3->unknown34, m_menuObjPartyForm3->unknown38, m_menuObjPartyForm3->unknown48, 2);
      break;
    case 4:
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
      enableInput(handle);
      m_menuObjPartyForm3->unknown319 = false;
      break;
    case 5:
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
      enableInput(handle);
      break;
    }
    break;
  case 6: {
    int selected = event.unknown08;
    if (selected < 0) {
      break;
    }
    int previous = event.unknown0c;
    if (selected == previous) {
      break;
    }
    mm::mtl::FixStr<32> name;
    // The game formats the layer name and then the frame name into the same string (0x71004ac998, 0x71004ac9ac); the first result is never read.
    name.format("LAY_dr@%02d", selected + 1);
    name.format("IMG_dr_frame@%02d", selected + 1);
    ui::UIObjectAcc frame(acc.searchChild(name.c_str()));
    frame.setImageIndex(1);
    if (previous >= 0) {
      name.format("LAY_dr@%02d", previous + 1);
      name.format("IMG_dr_frame@%02d", previous + 1);
      ui::UIObjectAcc previousFrame(acc.searchChild(name.c_str()));
      previousFrame.setImageIndex(m_menuObjPartyForm3->unknown40 == previous ? 2 : 0);
    }
    m_menuObjPartyForm3->refreshRemoveAddOperation(owner.searchChild("LAY_dr_select"), selected);
    m_menuObjPartyForm3->unknown3c = selected;
    if (previous != -1) {
      GfMenuObjUtil::playSECommonCursor();
    }
    break;
  }
  case 8:
    switch (event.unknown0c) {
    case 1: {
      u32 index = m_menuObjPartyForm3->unknown3c;
      if (index == m_menuObjPartyForm3->unknown40) {
        break;
      }
      mm::mtl::FixStr<32> name;
      // The game calls isGameCond (0x71004acab4) before it tests the index; `index == 0 && isGameCond(0xa9d)` gives another block order (first difference at 0x71004acaa8).
      if (GfGameCond::isGameCond(0xa9d) && index == 0) {
        GfMenuManager::openCommonWindow(0xdc);
        break;
      }
      mm::Rect<s16> rect;
      acc.getLayoutRect("dr_plate01", rect);
      if (m_menuObjPartyForm3->unknown40 < 0) {
        name.format("LAY_dr@%02d", index + 1);
        ui::UIObjectAcc layer(acc.searchChild(name.c_str()));
        // These four statements repeat below and in the cancel path (ruling 8). A static helper with the layer, the rect and an offset gives 664 instructions as the game
        // and 6 differing lines (its `Pnt` has the stack slot x29 - 136 / sp where the game has x29 - 56 / sp + 120; first difference 0x71004acc5c); one with the layer and
        // `y` gives 17 lines. A helper that also holds the `format`, `searchChild` and frame statements of the two identical sites gives 594 instructions (not inlined).
        mm::Pnt<s16> pos;
        layer.getPos(pos);
        pos.y = rect.y - 0x30;
        layer.setPos(pos);
        m_menuObjPartyForm3->unknown40 = index;
        GfMenuObjOperationInfo::setGuideText(0x37, m_menuObjPartyForm3->unknown30 == 0 ? 0 : 2);
        if (m_menuObjPartyForm3->unknown318) {
          GfMenuObjOperationInfo::setActionEnable(owner.searchChild("LAY_dr_select"), 9, false);
        }
      } else {
        name.format("LAY_dr@%02d", m_menuObjPartyForm3->unknown40 + 1);
        ui::UIObjectAcc layer(acc.searchChild(name.c_str()));
        mm::Pnt<s16> pos;
        layer.getPos(pos);
        pos.y = rect.y;
        layer.setPos(pos);
        name.format("IMG_dr_frame@%02d", m_menuObjPartyForm3->unknown40 + 1);
        ui::UIObjectAcc frame(acc.searchChild(name.c_str()));
        frame.setImageIndex(m_menuObjPartyForm3->unknown40 == index);
        m_menuObjPartyForm3->m_menuDriverList->swapContents(index, m_menuObjPartyForm3->unknown40);
        GfMenuObjUtil::CtrlParam param;
        name.format("IMG_dr_bustup@%02d", index + 1);
        param.unknown08 = 0x100000;
        param.unknown0c = 3;
        param.unknown00 = 0.2f;
        param.unknown2c = 0.0f;
        param.unknown30 = 1.0f;
        param.unknown04 = 5;
        // `ctrl` places the call before the load of acc.unknown10: without it the function has 666 instructions against 664.
        int ctrl = GfMenuObjUtil::startCtrl(acc.searchChild(name.c_str()), param, nullptr);
        hookCtrlEvent(acc.unknown10, ctrl);
        name.format("IMG_dr_bustup@%02d", m_menuObjPartyForm3->unknown40 + 1);
        GfMenuObjUtil::startCtrl(acc.searchChild(name.c_str()), param, nullptr);
        m_menuObjPartyForm3->unknown40 = -1;
        m_menuObjPartyForm3->unknown44 = true;
        GfMenuObjMainMenu2::setCloseKeyEnable(false);
        GfMenuObjOperationInfo::setGuideText(0xb, m_menuObjPartyForm3->unknown30 == 0 ? 0 : 2);
        m_menuObjPartyForm3->refreshRemoveAddOperation(owner.searchChild("LAY_dr_select"), index);
        disableInput(handle);
      }
      GfMenuObjUtil::playSECommonDecide();
      break;
    }
    case 2: {
      mm::mtl::FixStr<32> name;
      if (m_menuObjPartyForm3->unknown319) {
        break;
      }
      if (m_menuObjPartyForm3->unknown40 < 0) {
        if (m_menuObjPartyForm3->unknown30 == 0) {
          returnFSSubLayer(owner.unknown10, 1);
          GfMenuObjUtil::playSECommonCancel();
        } else {
          closeFSLayer(owner.unknown10, true, true);
        }
        break;
      }
      mm::Rect<s16> rect;
      acc.getLayoutRect("dr_plate01", rect);
      name.format("LAY_dr@%02d", m_menuObjPartyForm3->unknown40 + 1);
      ui::UIObjectAcc layer(acc.searchChild(name.c_str()));
      mm::Pnt<s16> pos;
      layer.getPos(pos);
      pos.y = rect.y;
      layer.setPos(pos);
      name.format("IMG_dr_frame@%02d", m_menuObjPartyForm3->unknown40 + 1);
      ui::UIObjectAcc frame(acc.searchChild(name.c_str()));
      frame.setImageIndex(m_menuObjPartyForm3->unknown40 == m_menuObjPartyForm3->unknown3c);
      m_menuObjPartyForm3->unknown40 = -1;
      GfMenuObjOperationInfo::setGuideText(0xb, m_menuObjPartyForm3->unknown30 == 0 ? 0 : 2);
      m_menuObjPartyForm3->refreshRemoveAddOperation(owner.searchChild("LAY_dr_select"), m_menuObjPartyForm3->unknown3c);
      GfMenuObjUtil::playSECommonCancel();
      break;
    }
    case 9: {
      if (m_menuObjPartyForm3->unknown40 >= 0) {
        break;
      }
      u32 index = m_menuObjPartyForm3->unknown3c;
      u32 count = m_menuObjPartyForm3->unknown34;
      // The game builds this accessor (0x71004acb28) and never uses it; the layer and the guide objects come from `acc` and `owner`.
      ui::UIObjectAcc background(owner.searchChild("LAY_bg"));
      mm::mtl::FixStr<32> name;
      // The two arms repeat their tail (the jumps at 0x71004ad140 and 0x71004ad23c): the game destroys `layer` after the setup of the layout, and it lays out the failed
      // checks after the arms. `count >= 2` and `count <= 2` as the conditions of the arms give its `cmp #2; b.lo/b.hi`.
      if (index < count) {
        if (count >= 2) {
          name.format("LAY_dr@%02d", index + 1);
          ui::UIObjectAcc layer(acc.searchChild(name.c_str()));
          layer.setScale(mm::Vec2(1.0f, 1.0f));
          // The game clears the element before it copies the driver in (`str wzr, [sp, #0x60]`, 0x71004acb84); see the second arm.
          MenuDriverInfo info = {};
          GfMenuDriverList *list = m_menuObjPartyForm3->m_menuDriverList;
          info = list->getContents(index);
          list = m_menuObjPartyForm3->m_menuDriverList;
          list->contents.erase(list->contents.begin() + index);
          list->subSize(1);
          list->contentsChanged = true;
          m_menuObjPartyForm3->m_menuDriverList->addContents(info);
          m_menuObjPartyForm3->unknown34--;
          m_menuObjPartyForm3->unknown38++;
          setupDriverLayout(acc, m_menuObjPartyForm3->unknown34, m_menuObjPartyForm3->unknown38, m_menuObjPartyForm3->unknown48, 1);
          m_menuObjPartyForm3->refreshRemoveAddOperation(owner.searchChild("LAY_dr_select"), index);
          m_menuObjPartyForm3->unknown44 = true;
          GfMenuObjMainMenu2::setCloseKeyEnable(false);
          disableInput(handle);
          GfMenuObjUtil::playSECommonDecide();
          m_menuObjPartyForm3->unknown319 = true;
        } else {
          GfMenuObjUtil::playSECommon(2);
        }
      } else if (count <= 2) {
        name.format("LAY_dr@%02d", index + 1);
        ui::UIObjectAcc layer(acc.searchChild(name.c_str()));
        layer.setScale(mm::Vec2(1.0f, 1.0f));
        // The game clears the element before it copies the driver in (`str wzr, [sp, #0x60]`, 0x71004acb84), and the clear survives because the inlined getContents
        // asserts split the block; `MenuDriverInfo info = list->getContents(index)` has 663 instructions against 664. The two arms share these statements up to the
        // `contentsChanged` store, a static helper with the form, the index and the element gives 662 instructions and 112 differing lines (ruling 8).
        MenuDriverInfo info = {};
        GfMenuDriverList *list = m_menuObjPartyForm3->m_menuDriverList;
        info = list->getContents(index);
        list = m_menuObjPartyForm3->m_menuDriverList;
        list->contents.erase(list->contents.begin() + index);
        list->subSize(1);
        list->contentsChanged = true;
        list = m_menuObjPartyForm3->m_menuDriverList;
        if (list->getSize() > count) {
          // The game advances the iterator with a loop, like ui::UISelectObjList::insertObject: it tests the count against zero (0x71004ad1d8) and then computes
          // begin + (count - 1) + 1; `begin() + count` gives 661 instructions against the game's 664.
          MenuDriverInfo *position = list->contents.begin();
          for (u32 i = 0; i < count; i++) {
            position++;
          }
          list->contents.insert(position, info);
          list->addSize(1);
          list->contentsChanged = true;
        } else {
          list->addContents(info);
        }
        m_menuObjPartyForm3->unknown34++;
        m_menuObjPartyForm3->unknown38--;
        setupDriverLayout(acc, m_menuObjPartyForm3->unknown34, m_menuObjPartyForm3->unknown38, m_menuObjPartyForm3->unknown48, 1);
        m_menuObjPartyForm3->refreshRemoveAddOperation(owner.searchChild("LAY_dr_select"), index);
        m_menuObjPartyForm3->unknown44 = true;
        GfMenuObjMainMenu2::setCloseKeyEnable(false);
        disableInput(handle);
        GfMenuObjUtil::playSECommonDecide();
        m_menuObjPartyForm3->unknown319 = true;
      } else {
        GfMenuObjUtil::playSECommon(2);
      }
      break;
    }
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPartyForm3>(const mm::mtl::Delegate<bool()> *);
