#include "gf/menu/object/gf_menu_obj_hana_submenu.h"

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/ctrl/ui_ctrl_curve.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/plugin/ui_object_dock_plugin.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x71;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

// Inferred role: layer and condition of a submenu entry, indexed by the selected submenu; original type name unknown.
struct unknown003 {
  u32 unknown00; // Inferred role: menu layer id; original member name unknown.
  u32 unknown04; // Inferred role: menu condition id; original member name unknown.
};

// Inferred role: the three submenus (0x7100f6ffec); original name unknown.
static const unknown003 unknown004[3] = {{0x2e, 0x12}, {0x2f, 0x13}, {0x30, 0x14}};

GfMenuObjHanaSubmenu::GfMenuObjHanaSubmenu(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(0) {}

GfMenuObjHanaSubmenu::~GfMenuObjHanaSubmenu() { mm::mtl::safeRelease(unknown28); }

void GfMenuObjHanaSubmenu::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 101 as in the original file: it is the line argument of operator new.
#line 101
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main);
  u32 subMenu = acc.searchChild("LAY_sub_menu");
// __LINE__ must be 107 as in the original file: it is the line argument of operator new.
#line 107
  SubmenuListener *submenuListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SubmenuListener(this);
  submenuListener->addRef();
  ui::UIEventManager::get()->registObjectListener(subMenu, submenuListener);
  if (submenuListener != nullptr) {
    submenuListener->release();
  }
  GfMenuObject::initialize();
}

void GfMenuObjHanaSubmenu::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaSubmenu::update() { GfMenuObject::update(); }

void GfMenuObjHanaSubmenu::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjHanaSubmenu::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjHanaSubmenu::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjHanaSubmenu::returnHanaSubMenu() { GF_MENU_REQUEST_EVENT(unknown001, unknown002); }

void GfMenuObjHanaSubmenu::setupSubmenu(ui::UIObjectAcc &acc) {
  GfDataBdat::getFP(BDAT_MENU_SUB_CONTENTS_MS);
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 3; i++) {
    name.format("IMG_sub_menu_bl_icon@%02d", i + 1);
    ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
    icon.setImageIndex(i);
    name.format("LAY_sub_menu_bl_text@%02d", i + 1);
    ui::UIObjectDockPlugin *plugin = ui::UIObjectDockPlugin::create(acc.searchChild(name.c_str()), 0, 0, icon.unknown10);
    plugin->unknown24 = 1;
    mm::mtl::safeRelease(plugin);
  }
}

void GfMenuObjHanaSubmenu::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::add(acc.searchChild("LAY_sub_menu"), 0, 0, 0);
    GfMenuObjOperationInfo::setGuideText(10, 0);
    setFadeIn(handle);
    break;
  case 3:
    if (event.unknown08 == 2) {
      GfMenuObjOperationInfo::remove(acc.searchChild("LAY_sub_menu"), 0, 0, 0);
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObjCharSelect::returnSubMenu();
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    setFadeOut(handle);
    break;
  case GfMenuTypes::unknown003_257:
    GfMenuObjOperationInfo::add(acc.searchChild("LAY_sub_menu"), 0, 0, 0);
    GfMenuObjOperationInfo::setGuideText(10, 0);
    GfMenuObjCharSelect::dispOnChar(1);
    unknown163(acc.searchChild("LAY_sub_menu"), GfMenuTypes::unknown003_258, 0);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjHanaSubmenu::SubmenuListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(m_menuObjHanaSubmenu->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    setupSubmenu(acc);
    GfMenuObjUtil::CursorParam param;
    param.unknown00 = ui::UIObjectAcc(handle).getParentHandle();
    param.unknown04 = owner.searchChild("IMG_sub_cursor");
    // Redundant store the game holds (P3): the constructor already cleared the cursor type at offset 0x1a of the parameter, and the game clears it again
    // after the search of IMG_sub_cursor (0x71004759b4: strh wzr).
    param.unknown1a = 0;
    param.unknown08 = "LAY_sub_menu_bl@%02d";
    // The dock type of the cursor setting (offset 0x38 of the parameter, default 1) is set to 0 (0x71004759b8: strh wzr); the default store is then dead.
    param.m_cursorSetting.unknown18 = 0;
    m_menuObjHanaSubmenu->unknown28 = GfMenuObjUtil::createCursor(param);
    m_menuObjHanaSubmenu->unknown28->open(0);
    ui::UIObjectAcc icon(acc.searchChild("IMG_sub_menu_bl_icon@01"));
    mm::Vec2 scale;
    icon.getScale(scale);
    m_menuObjHanaSubmenu->unknown34 = scale.x;
    m_menuObjHanaSubmenu->unknown38 = scale.x * 1.5f;
    GfMenuObject::setupInputSelection(handle, 0, 3);
    GfMenuObject::enableInput(handle);
    break;
  }
  case 6: {
    int current = event.unknown08;
    int previous = event.unknown0c;
    m_menuObjHanaSubmenu->unknown28->inputChange(current);
    mm::mtl::FixStr<32> currentBase;
    mm::mtl::FixStr<32> previousBase;
    mm::mtl::FixStr<32> currentIcon;
    mm::mtl::FixStr<32> previousIcon;
    currentBase.format("IMG_sub_menu_bl_bg@%02d", current + 1);
    previousBase.format("IMG_sub_menu_bl_bg@%02d", previous + 1);
    currentIcon.format("IMG_sub_menu_bl_icon@%02d", current + 1);
    previousIcon.format("IMG_sub_menu_bl_icon@%02d", previous + 1);
    if (current >= 0) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x80000;
      param.unknown0c = ui::CURVE_TYPE_LINEAR;
      param.unknown00 = 0.2f;
      param.unknown2c = m_menuObjHanaSubmenu->unknown38;
      GfMenuObjUtil::startCtrl(acc.searchChild(currentIcon.c_str()), param, nullptr);
      ui::UIObjectAcc base(acc.searchChild(currentBase.c_str()));
      base.startAnimation("sellect", false);
      m_menuObjHanaSubmenu->unknown30 = current;
    }
    if (previous >= 0 && current != previous) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x80000;
      param.unknown0c = ui::CURVE_TYPE_LINEAR;
      param.unknown00 = 0.2f;
      param.unknown2c = m_menuObjHanaSubmenu->unknown34;
      GfMenuObjUtil::startCtrl(acc.searchChild(previousIcon.c_str()), param, nullptr);
      ui::UIObjectAcc base(acc.searchChild(previousBase.c_str()));
      base.startAnimation("idol", false);
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      u32 index = m_menuObjHanaSubmenu->unknown30;
      if (GfMenuObjUtil::getMenuCondition(unknown004[index].unknown04)) {
        GfMenuObjOperationInfo::remove(owner.searchChild("LAY_sub_menu"), 0, 0, 0);
        ui::EventData end;
        end.unknown00 = GfMenuTypes::unknown003_259;
        ui::UIManager::get()->requestObjectEvent(handle, end, 0.0f);
        if (m_menuObjHanaSubmenu->unknown30 < 3) {
          GfMenuObjCharSelect::dispOffChar(1);
          GfMenuObject::changeFSSubLayer(owner.unknown10, 3, GfMenuObject::getMenuLayerID(unknown004[index].unknown00), true);
        }
      }
    } else if (event.unknown0c == 2) {
      // The game calls searchChild before it loads the UIManager instance (0x7100475624).
      u32 main = owner.searchChild("LAY_main");
      ui::EventData end;
      end.unknown00 = GfMenuTypes::unknown003_34;
      ui::UIManager::get()->requestObjectEvent(main, end, 0.0f);
      GfMenuObject::disableInput(handle);
    }
    break;
  case GfMenuTypes::unknown003_258:
    acc.setDisp(true);
    GfMenuObject::enableInput(handle);
    break;
  case GfMenuTypes::unknown003_259:
    acc.setDisp(false);
    GfMenuObject::disableInput(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf
