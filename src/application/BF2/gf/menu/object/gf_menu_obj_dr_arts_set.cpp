#include "gf/menu/object/gf_menu_obj_dr_arts_set.h"

#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_driver_arts.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_weapon_type_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/ctrl/ui_ctrl_slide_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5b;

GfMenuObjDrArtsSet::GfMenuObjDrArtsSet(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown48(nullptr), unknownc8(nullptr) {}

GfMenuObjDrArtsSet::~GfMenuObjDrArtsSet() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  unknown38 = nullptr;
  unknown40 = nullptr;
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknownc8);
}

void GfMenuObjDrArtsSet::initialize() {
  ui::UIObjectAcc acc(unknown18);
  unknownc8 = GfMenuCallContext::create();
  ui::UISelectObjList::CreateParam createParam;
  createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown28 = ui::UISelectObjList::create(createParam);
  unknown38 = unknown160();
  unknown38->unknown162(0);
  unknown40 = unknown160();
  unknown40->unknown162(0);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 118 as in the original file: it is the line argument of operator new.
#line 118
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main);
  u32 category = acc.searchChild("LAY_category");
// __LINE__ must be 124 as in the original file: it is the line argument of operator new.
#line 124
  WpnTypeListener *wpnTypeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) WpnTypeListener(this);
  wpnTypeListener->addRef();
  ui::UIEventManager::get()->registObjectListener(category, wpnTypeListener);
  if (wpnTypeListener != nullptr) {
    wpnTypeListener->release();
  }
  attachExternalCall(unknown001, category);
  u32 artsList = acc.searchChild("LAY_arts_list");
// __LINE__ must be 129 as in the original file: it is the line argument of operator new.
#line 129
  ArtsListListener *artsListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ArtsListListener(this);
  artsListListener->addRef();
  ui::UIEventManager::get()->registObjectListener(artsList, artsListListener);
  if (artsListListener != nullptr) {
    artsListListener->release();
  }
  attachExternalCall(unknown001, artsList);
  u32 artsDetail = acc.searchChild("LAY_arts_detail");
// __LINE__ must be 134 as in the original file: it is the line argument of operator new.
#line 134
  ArtsDetailListener *artsDetailListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ArtsDetailListener(this);
  artsDetailListener->addRef();
  ui::UIEventManager::get()->registObjectListener(artsDetail, artsDetailListener);
  if (artsDetailListener != nullptr) {
    artsDetailListener->release();
  }
  attachExternalCall(unknown001, artsDetail);
  GfMenuObject::initialize();
}

void GfMenuObjDrArtsSet::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrArtsSet::update() { GfMenuObject::update(); }

void GfMenuObjDrArtsSet::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjDrArtsSet::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 0, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjDrArtsSet::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjDrArtsSet::setupWpnType(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number) {
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("TXT_cate_name"), 0, 0, number, 0, false);
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("TXT_cate_wp_num"), 2, 0, number, 0, true);
}

void GfMenuObjDrArtsSet::setupSlideSelect(ui::UIObjectAcc &acc, mm::mtl::FixedVector<u32, 27> &weaponTypes, ui::UISelectObjList *list) {
  GfDataDriver::getEquipWpnType(weaponTypes, GfMenuReference::getReferenceDriverID(0));
  int count = 0;
  for (u32 *it = weaponTypes.begin(); it != weaponTypes.end(); it++) {
    if (*it != 0) {
      count++;
    }
  }
  for (u32 i = 0; i < list->getSize(); i++) {
    ui::UIObjectAcc object(list->getContents(i));
    object.setTerm();
  }
  list->clear();
  ui::UIListInfoBase::SetupParam setup;
  setup.unknown08 = count;
  list->setup(getAllocator(ALLOCATOR_UNKNOWN_0), setup);
  ui::UICtrlSlideSelect::SlideSetting setting;
  bool isFirst = true;
  for (u32 *it = weaponTypes.begin(); it != weaponTypes.end(); it++) {
    if (*it != 0) {
      ui::UIObjectAcc icon(acc.duplicateChild("IMG_cate_wp_icon@01"));
      icon.setImageIndex(*it - 1);
      icon.setDisp(true);
      list->addObject(icon.unknown10);
      if (isFirst) {
        icon.getPosCenter(setting.unknown0c);
        s16 width;
        s16 height;
        icon.getSize(true, width, height);
        setting.unknown10.x = width + 8;
        setting.unknown10.y = 0;
      }
      isFirst = false;
    }
  }
  setting.unknown08 = 5;
  setting.unknown00 = 0.4f;
  setting.unknown14 = 0.5f;
  setting.unknown18 = 1.0f;
  ui::UICtrlSlideSelect::create(acc.unknown10, setting, list);
}

void GfMenuObjDrArtsSet::setupArtsList(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 4; i++) {
    name.format("IMG_arts_icon@%02d", i + 1);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("LAY_arts_icon@%02d", i + 1);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), true);
    name.format("IMG_arts_icon_type@%02d", i + 1);
    GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild(name.c_str()), 4, 0, number, i, false);
    name.format("IMG_arts_icon_enhance@%02d", i + 1);
    GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild(name.c_str()), 5, 0, number, i, false);
    name.format("IMG_arts_icon_react@%02d", i + 1);
    GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild(name.c_str()), 6, 0, number, i, false);
    name.format("IMG_arts_icon_range@%02d", i + 1);
    GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild(name.c_str()), 7, 0, number, i, false);
  }
}

void GfMenuObjDrArtsSet::setupArtsDetail(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> wpnType, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> artsIndex) {
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnTypeArtsIndex(acc.searchChild("TXT_arts_detail_name"), 3, 0, wpnType, artsIndex, false);
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnTypeArtsIndex(acc.searchChild("TXT_arts_detail_lv"), 0xd, 0, wpnType, artsIndex, true);
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnTypeArtsIndex(acc.searchChild("TXT_arts_detail_info"), 0xf, 0, wpnType, artsIndex, false);
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnTypeArtsIndex(acc.searchChild("TXT_arts_detail_wp_num"), 0x10, 0, wpnType, artsIndex, true);
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnTypeArtsIndex(acc.searchChild("TXT_arts_detail_dr_lv_num"), 0x11, 0, wpnType, artsIndex, true);
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnTypeArtsIndex(acc.searchChild("LAY_arts_detail_body"), 0x12, 0, wpnType, artsIndex, false);
  GfMenuWeaponTypeAdapter *error = GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnTypeArtsIndex(acc.searchChild("LAY_arts_detail_error"), 0x12, 0, wpnType, artsIndex, false);
  error->unknown64 = 1;
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnTypeArtsIndex(acc.searchChild("TXT_arts_detail_err_dr_lv"), 0x11, 0, wpnType, artsIndex, false);
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnTypeArtsIndex(acc.searchChild("LAY_arts_detail_lvup"), 0x13, 0, wpnType, artsIndex, true);
}

bool GfMenuObjDrArtsSet::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

void GfMenuObjDrArtsSet::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_arts_detail", false);
    unknown163(handle, GfMenuTypes::unknown003_33, 0);
    break;
  case 2:
    GfMenuObjOperationInfo::close();
    GfMenuObject::termCallContext(handle);
    acc.setDisp(false);
    acc.setTerm();
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::returnFSSubLayer(handle, 2);
    }
    break;
  case GfMenuTypes::unknown003_33:
    setFadeIn(handle);
    unknown163(acc.searchChild("LAY_category"), GfMenuTypes::unknown003_33, 0);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObjOperationInfo::close();
    setFadeOut(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjDrArtsSet::ArtsListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(unknown20->unknown18);
  switch (event.unknown00) {
  case 1: {
    setupArtsList(acc, unknown20->unknown38);
    GfMenuObjUtil::CursorParam param;
    param.unknown00 = handle;
    param.unknown04 = acc.searchChild("IMG_arts_list_cursor");
    param.unknown1a = 1;
    param.unknown08 = "IMG_arts_icon@%02d";
    param.unknown20.unknown18 = 5;
    unknown20->unknown48 = GfMenuObjUtil::createCursor(param);
    GfMenuObject::disableInput(handle);
    break;
  }
  case 6: {
    u32 index = event.unknown08;
    if (unknown20->unknown48->inputChange(index)) {
      mm::mtl::FixedArray<u32, 4> arts;
      if (GfDataDriverArts::getEnableArts(arts, GfMenuReference::getReferenceDriverID(0), unknown20->unknown38->unknown0c)) {
        unknown20->unknown40->unknown162(index);
      }
    }
    break;
  }
  case 8:
    switch (event.unknown0c) {
    case 9: {
      u32 driver = GfMenuReference::getReferenceDriverID(0);
      u32 weaponType = unknown20->unknown38->unknown0c;
      mm::mtl::FixedArray<u32, 4> arts;
      if (GfDataDriverArts::getEnableArts(arts, driver, weaponType)) {
        // The game zero-extends the arts index (ldr w8, [x8, #12] at 0x7100448aac) although
        // GfMenuReferenceNumber::unknown0c is int; retyping it breaks other matched functions, so the index is
        // kept as the u32 the game's access shows (P1, ruling 2026-11-14).
        u32 slot = unknown20->unknown40->unknown0c;
        u32 art = arts[slot];
        u32 level = GfDataDriverArts::getArtsLevel(driver, art);
        u32 driverLevel = GfDataDriver::getLevel(driver);
        if (art != 0) {
          u32 window;
          if (level < GfDataDriverArts::getLevelMax(art)) {
            if (GfDataDriverArts::getNeedLevelupWp(driver, art) <= GfDataDriverArts::getWp(driver, weaponType)) {
              if (driverLevel < GfDataDriverArts::getLevelCap(art, level + 1)) {
                window = 0x1a;
              } else {
                GfGameUtil::execDriverArtsLevelUp(driver, art, level + 1);
                window = 0x19;
              }
            } else {
              window = 0x1a;
            }
          } else {
            window = 0x1b;
          }
          unknown20->unknownc8->reset();
          GfMenuObjCommonText::open(unknown20->unknownc8, window, 0);
          GfMenuObject::setCallContextEventHandler(unknown20->unknownc8, handle);
          GfMenuObject::disableInput(handle);
        }
      }
      break;
    }
    case 2:
      unknown164(handle, GfMenuTypes::unknown003_34);
      unknown163(owner.searchChild("LAY_category"), GfMenuTypes::unknown003_33, 0);
      break;
    }
    break;
  case GfMenuTypes::unknown003_33:
    unknown20->unknown48->open(0);
    unknown164(owner.searchChild("LAY_arts_detail"), GfMenuTypes::unknown003_33);
    GfMenuObject::setupInputSelection(handle, 0, 4);
    GfMenuObject::enableInput(handle);
    GfMenuObjOperationInfo::open(handle, 0, 0, 0);
    break;
  case GfMenuTypes::unknown003_34:
    unknown20->unknown48->setDisp(false);
    unknown164(owner.searchChild("LAY_arts_detail"), GfMenuTypes::unknown003_34);
    GfMenuObject::disableInput(handle);
    break;
  case 0x41:
    if (unknown20->unknownc8 != nullptr && unknown20->unknownc8->unknown0c == event.unknown08) {
      GfMenuObject::enableInput(handle);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjDrArtsSet::ArtsDetailListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupArtsDetail(acc, unknown20->unknown38, unknown20->unknown40);
    break;
  case GfMenuTypes::unknown003_33:
    setFadeIn(handle);
    break;
  case GfMenuTypes::unknown003_34:
    setFadeOut(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
