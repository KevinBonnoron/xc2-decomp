#include "gf/menu/object/gf_menu_obj_main_submenu.h"

#include <string.h>

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_util.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: entry of a submenu; original type name unknown.
struct unknown001 {
  u32 unknown00; // Inferred role: full screen layer opened by the entry; original member name unknown.
  u32 unknown04; // Inferred role: menu condition of the entry; original member name unknown.
  u16 unknown08; // Inferred role: info text of the entry; original member name unknown.
};

static_assert(offsetof(unknown001, unknown04) == 0x04, "");
static_assert(offsetof(unknown001, unknown08) == 0x08, "");
static_assert(sizeof(unknown001) == 0x0c, "");

// Inferred role: entries of the book submenu; original name unknown.
static const unknown001 unknown002[2] = {{69, 21, 13}, {66, 22, 14}};
// Inferred role: entries of the crystal submenu; original name unknown.
static const unknown001 unknown003[3] = {{65, 24, 12}, {20, 23, 11}, {69, 21, 13}};
// Inferred role: entries of the system submenu; original name unknown.
static const unknown001 unknown004[3] = {{68, 33, 15}, {54, 32, 16}, {26, 34, 17}};

GfMenuObjMainSubmenu::GfMenuObjMainSubmenu(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(0), unknown2c(0), unknown30(nullptr), unknown64(true), unknown68(nullptr), unknown70{-1, -1, -1} {}

GfMenuObjMainSubmenu::~GfMenuObjMainSubmenu() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown68);
}

void GfMenuObjMainSubmenu::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
// __LINE__ must be 107 as in the original file: it is the line argument of operator new.
#line 107
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
// __LINE__ must be 108 as in the original file: it is the line argument of operator new.
#line 108
  ListListener *listListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
  listListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_item_list"), listListener);
  if (listListener != nullptr) {
    listListener->release();
  }
  {
    ui::UISelectObjList::CreateParam createParam;
    createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
    unknown30 = ui::UISelectObjList::create(createParam);
  }
  {
    ui::UIObjectAcc acc(unknown18);
    u32 count;
    const unknown001 *entries;
    if (strcmp(acc.getName(), "mnu094_submenu_book") == 0) {
      unknown24 = 1;
      unknown28 = 5;
      unknown2c = 0xe;
      count = 2;
      entries = unknown002;
    } else if (strcmp(acc.getName(), "mnu094_submenu_crystal") == 0) {
      unknown24 = 2;
      unknown28 = 6;
      unknown2c = 0xf;
      count = 3;
      entries = unknown003;
    } else if (strcmp(acc.getName(), "mnu094_submenu_system") == 0) {
      unknown24 = 3;
      unknown28 = 8;
      unknown2c = 0x11;
      count = 3;
      entries = unknown004;
    } else {
      count = 0;
      entries = nullptr;
    }
    unknown38.clear();
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < count; i++) {
      name.format("LAY_item@%02d", i + 1);
      if (GfMenuObjUtil::getMenuCondition(entries[i].unknown04)) {
        unknown30->addContents(main.searchChild(name.c_str()));
        unknown38.push_back(i);
        GfMenuObjUtil::setChildDisp(main.unknown10, name.c_str(), true);
      } else {
        GfMenuObjUtil::setChildDisp(main.unknown10, name.c_str(), false);
      }
    }
  }
  unknown68 = GfMenuCallContext::create();
  GfMenuObject::disableInput(main.searchChild("LAY_item_list"));
  GfMenuObject::initialize();
}

void GfMenuObjMainSubmenu::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMainSubmenu::update() { GfMenuObject::update(); }

bool GfMenuObjMainSubmenu::isEnableSkipTime() {
  if (GfDataUtil::getScenarioFlag() > 0xfbc && GfDataUtil::getScenarioFlag() < 0xfc9 && GfGameManager::getMapID() == 10) {
    return false;
  }
  return true;
}

void GfMenuObjMainSubmenu::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    ui::EventData sendData;
    sendData.unknown00 = GfMenuTypes::unknown003_33;
    GfMenuObject::sendEvent(acc.unknown10, sendData, 0.0f);
    break;
  }
  case 2: {
    ui::EventData sendData;
    sendData.unknown00 = GfMenuTypes::unknown003_34;
    sendData.unknown08 = 1;
    GfMenuObject::sendEvent(acc.unknown10, sendData, 0.0f);
    break;
  }
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
      GfMenuObject::enableInput(acc.searchChild("LAY_item_list"));
    } else if (event.unknown08 == 2) {
      acc.setTerm();
    }
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
    if (!unknown20->unknown64) {
      ui::EventData sendData;
      sendData.unknown00 = 3;
      sendData.unknown08 = 2;
      ui::UIManager::get()->requestObjectEvent(handle, sendData, 0.0f);
    } else {
      bool unknown = event.unknown08 == 1;
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown04 = 1;
      param.unknown00 = 6;
      param.unknown10 = 2;
      param.unknown0c = unknown;
      GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    }
    ui::EventData sendData;
    sendData.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.searchChild("LAY_item_list"), sendData, 0.0f);
    break;
  }
  case 0x24: {
    GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 1;
    param.unknown10 = 2;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    unknown20->unknown64 = false;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMainSubmenu::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc root(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    mm::Rect<s16> rect;
    acc.getLayoutRect("lay_item02", rect);
    mm::Rect<s16> firstRect;
    acc.getLayoutRect("lay_item01", firstRect);
    int interval = rect.x - 1 - firstRect.x;
    mm::Pnt<s16> pos(rect.x + rect.width / 2, rect.height / 2 + rect.y);
    GfMenuObjUtil::placeObjectH(unknown20->unknown30, pos, interval);
    GfMenuObjOperationInfo::setGuideText(unknown20->unknown28, 0);
    GfMenuObjMainMenu2::setSubIndexText(unknown20->unknown2c);
    ui::EventData sendData;
    sendData.unknown00 = GfMenuTypes::unknown003_33;
    GfMenuObject::sendEvent(acc.unknown10, sendData, 0.0f);
    GfMenuObject::disableInput(handle);
    break;
  }
  case 6: {
    int index = event.unknown08;
    int previous = event.unknown0c;
    mm::mtl::FixStr<32> name;
    if (index == -1) {
      break;
    }
    u32 entry = unknown20->unknown38[index];
    name.format("IMG_item_pic_grow@%02d", entry + 1);
    {
      ui::UIObjectAcc grow(acc.searchChild(name.c_str()));
      grow.setAlpha(1.0f);
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 4;
      param.unknown00 = 2.0f;
      param.unknown3c = 0.5f;
      param.unknown10 = true;
      param.unknown14 = 8;
      param.unknown0c = 3;
      param.unknown18 = unknown20->unknown70[entry];
      unknown20->unknown70[entry] = GfMenuObjUtil::startCtrl(grow.unknown10, param, nullptr);
    }
    if (previous != -1) {
      u32 previousEntry = unknown20->unknown38[previous];
      name.format("LAY_item_pic@%02d", entry + 1);
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = "cmn_fade_emotion";
      param.unknown58 = "fade_in_select";
      param.unknown11 = true;
      GfMenuObjUtil::startCtrl(acc.searchChild(name.c_str()), param, nullptr);
      name.format("IMG_item_pic_grow@%02d", previousEntry + 1);
      ui::UIObjectAcc grow(acc.searchChild(name.c_str()));
      if (unknown20->unknown70[previousEntry] != -1 && unknown20->unknown70[previousEntry] == GfMenuObjUtil::getCtrlID(grow.unknown10)) {
        GfMenuObjUtil::stopCtrl(unknown20->unknown70[previousEntry]);
        unknown20->unknown70[previousEntry] = -1;
      }
    }
    unknown20->unknown30->setIndex(index);
    for (u32 i = 0; i < unknown20->unknown30->getSize(); i++) {
      u32 item = unknown20->unknown38[i];
      name.format("LAY_item_pic@%02d", item + 1);
      ui::UIObjectAcc pic(acc.searchChild(name.c_str()));
      pic.setMulColor(item == entry ? "white" : "char_unselect");
      name.format("IMG_item_pic_grow@%02d", item + 1);
      ui::UIObjectAcc grow(acc.searchChild(name.c_str()));
      if (item == entry) {
        grow.setAlpha(1.0f);
        grow.setDisp(true);
      } else {
        grow.setAlpha(0.0f);
        grow.setDisp(false);
      }
    }
    u16 text = 0;
    switch (unknown20->unknown24) {
    case 1:
      text = unknown002[entry].unknown08;
      break;
    case 2:
      text = unknown003[entry].unknown08;
      break;
    case 3:
      text = unknown004[entry].unknown08;
      break;
    }
    if (text != 0) {
      ui::UIObjectAcc info(acc.unknown10, "TXT_item_info");
      u16 textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_MENU_DESCRIPTION, text);
      info.setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_SUB_CONTENTS_MS), textId));
    }
    if (previous != -1 && index != previous) {
      GfMenuObjUtil::playSECommonCursor();
    }
    break;
  }
  case 8: {
    int index = event.unknown08;
    if (index >= 0 && event.unknown0c == 1) {
      u32 entry = unknown20->unknown38[index];
      u32 layer;
      switch (unknown20->unknown24) {
      case 1:
        layer = unknown002[entry].unknown00;
        break;
      case 2:
        layer = unknown003[entry].unknown00;
        break;
      case 3:
        layer = unknown004[entry].unknown00;
        break;
      default:
        layer = 0;
        break;
      }
      if (layer != 0) {
        if (layer == 0x36 && !isEnableSkipTime()) {
          GfMenuObjCommonText::open(unknown20->unknown68, 0xb6, 0);
        } else {
          GfMenuObjMainMenu2::setSystemKeyEnable(false);
          GfMenuTypes::Param param;
          param.set<u16>(index);
          GfMenuObject::registFSLayerParam(unknown20->unknown20, param);
          GfMenuObject::changeFSSubLayer(acc.unknown10, 1, layer, true);
          ui::EventData sendData;
          sendData.unknown00 = GfMenuTypes::unknown003_34;
          GfMenuObject::sendEvent(acc.unknown10, sendData, 0.0f);
          GfMenuObjUtil::playSECommonDecide();
        }
      }
    }
    break;
  }
  case GfMenuTypes::unknown003_33: {
    unknown20->unknown60 = 0;
    GfMenuTypes::Param param;
    if (GfMenuObject::getFSLayerParam(unknown20->unknown20, param)) {
      unknown20->unknown60 = param.get<u16>();
      GfMenuObject::removeFSLayerParam(unknown20->unknown20);
    }
    GfMenuObjMainMenu2::setSystemKeyEnable(true);
    GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    GfMenuObject::setupInputSelection(acc.unknown10, unknown20->unknown60, unknown20->unknown30->getSize());
    break;
  }
  case GfMenuTypes::unknown003_34:
    GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjMainMenu2::setSystemKeyEnable(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
