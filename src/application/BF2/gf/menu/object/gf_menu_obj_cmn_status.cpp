#include "gf/menu/object/gf_menu_obj_cmn_status.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_diff_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/adapter/gf_menu_weapon_adapter.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_radar_graph.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x52;

bool GfMenuObjCmnStatus::s_DispFlag[2];

GfMenuObjCmnStatus::GfMenuObjCmnStatus(u32 handle) : GfMenuObject(handle), unknown28(), unknown38(nullptr) {
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown28[0] = ui::UISelectObjList::create(param);
  param = ui::UISelectObjList::CreateParam();
  param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown28[1] = ui::UISelectObjList::create(param);
}

GfMenuObjCmnStatus::~GfMenuObjCmnStatus() {
  mm::mtl::safeRelease(unknown28[0]);
  mm::mtl::safeRelease(unknown28[1]);
  mm::mtl::safeRelease(unknown38);
}

bool GfMenuObjCmnStatus::isOpenDrStatus() { return s_DispFlag[0]; }

bool GfMenuObjCmnStatus::isOpenBlStatus() { return s_DispFlag[1]; }

void GfMenuObjCmnStatus::finalize() {
  GfMenuReference::resetDriverVirtual();
  GfMenuReference::resetBladeVirtual();
  GfMenuObject::finalize();
}

void GfMenuObjCmnStatus::update() { GfMenuObject::update(); }

void GfMenuObjCmnStatus::setInputDisable() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    GfMenuObject::disableInput(acc.unknown10);
  }
}

void GfMenuObjCmnStatus::setInputEnable() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    GfMenuObject::enableInput(acc.unknown10);
  }
}

void GfMenuObjCmnStatus::openDrStatus(u32 driver, int page) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = driver;
    event.unknown0c = page;
    GfMenuObject::sendEvent(acc.searchChild("LAY_status_dr"), event, 0.0f);
    s_DispFlag[0] = true;
  }
}

void GfMenuObjCmnStatus::closeDrStatus() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.searchChild("LAY_status_dr"), event, 0.0f);
    s_DispFlag[0] = false;
  }
}

bool GfMenuObjCmnStatus::swapDrStatus() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::UIObjectAcc status(acc.unknown10, "LAY_status_dr");
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(status.unknown10, event, 0.0f);
    s_DispFlag[0] = !s_DispFlag[0];
    return s_DispFlag[0];
  }
  return false;
}

void GfMenuObjCmnStatus::openBlStatus(u32 blade, int page) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = blade;
    event.unknown0c = page;
    GfMenuObject::sendEvent(acc.searchChild("LAY_status_bl"), event, 0.0f);
    s_DispFlag[1] = true;
  }
}

void GfMenuObjCmnStatus::closeBlStatus() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.searchChild("LAY_status_bl"), event, 0.0f);
    s_DispFlag[1] = false;
  }
}

bool GfMenuObjCmnStatus::swapBlStatus() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::UIObjectAcc status(acc.unknown10, "LAY_status_bl");
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(status.unknown10, event, 0.0f);
    s_DispFlag[1] = !s_DispFlag[1];
    return s_DispFlag[1];
  }
  return false;
}

void GfMenuObjCmnStatus::updateBladeBase(u32 page) {
  u32 type = page - 2;
  bool isSkill = type < 5;
  ui::UIObjectAcc index(unknown18, "LAY_status_bl_index");
  ui::UIObjectAcc indexSkill(unknown18, "LAY_status_bl_index_sk");
  ui::UIObjectAcc base(unknown18, "IMG_status_bl_base");
  ui::UIObjectAcc baseSkill(unknown18, "IMG_status_bl_base_sk");
  index.setDisp(!isSkill);
  base.setDisp(!isSkill);
  indexSkill.setDisp(isSkill);
  baseSkill.setDisp(isSkill);
}

void GfMenuObjCmnStatus::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  attachExternalCall(unknown001, main.unknown10);
// __LINE__ must be 224 as in the original file: it is the line argument of operator new.
#line 224
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
// __LINE__ must be 227 as in the original file: it is the line argument of operator new.
#line 227
  CharStatusListener *driverListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) CharStatusListener(this);
  driverListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_status_dr"), driverListener);
  if (driverListener != nullptr) {
    driverListener->release();
  }
// __LINE__ must be 230 as in the original file: it is the line argument of operator new.
#line 230
  CharStatusListener *bladeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) CharStatusListener(this);
  bladeListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_status_bl"), bladeListener);
  if (bladeListener != nullptr) {
    bladeListener->release();
  }
  GfMenuObject::initialize();
}

void GfMenuObjCmnStatus::setBlPageParam(u32 handle) {
  ui::UIObjectAcc acc(handle);
  mm::mtl::FixStr<32> name;
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_name_role"), 0x41, 0, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_atk"), 7, 0, true);
  GfMenuCharDataAdapter *right = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_r_atk"), 7, 0, true);
  GfMenuCharDataAdapter *left = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_l_atk"), 7, 0, true);
  if (left != nullptr) {
    left->unknown79 = 1;
  }
  GfMenuDiffAdapter::create(acc.searchChild("LAY_status_bl_param_now_atk"), right, left, 3, true);
  GfMenuDiffAdapter::create(acc.searchChild("LAY_status_bl_param_dif_atk"), right, left, 4, true);
  GfMenuDiffAdapter::create(acc.searchChild("TXT_status_bl_param_l_atk"), right, left, 1, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_pdef"), 4, 0, true);
  right = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_r_pdef"), 4, 0, true);
  left = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_l_pdef"), 4, 0, true);
  if (left != nullptr) {
    left->unknown79 = 1;
  }
  GfMenuDiffAdapter::create(acc.searchChild("LAY_status_bl_param_now_pdef"), right, left, 3, true);
  GfMenuDiffAdapter::create(acc.searchChild("LAY_status_bl_param_dif_pdef"), right, left, 4, true);
  GfMenuDiffAdapter::create(acc.searchChild("TXT_status_bl_param_l_pdef"), right, left, 1, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_edef"), 5, 0, true);
  right = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_r_edef"), 5, 0, true);
  left = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_l_edef"), 5, 0, true);
  if (left != nullptr) {
    left->unknown79 = 1;
  }
  GfMenuDiffAdapter::create(acc.searchChild("LAY_status_bl_param_now_edef"), right, left, 3, true);
  GfMenuDiffAdapter::create(acc.searchChild("LAY_status_bl_param_dif_edef"), right, left, 4, true);
  GfMenuDiffAdapter::create(acc.searchChild("TXT_status_bl_param_l_edef"), right, left, 1, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_cri"), 8, 0, true);
  right = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_r_cri"), 8, 0, true);
  left = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_l_cri"), 8, 0, true);
  if (left != nullptr) {
    left->unknown79 = 1;
  }
  GfMenuDiffAdapter::create(acc.searchChild("LAY_status_bl_param_now_cri"), right, left, 3, true);
  GfMenuDiffAdapter::create(acc.searchChild("LAY_status_bl_param_dif_cri"), right, left, 4, true);
  GfMenuDiffAdapter::create(acc.searchChild("TXT_status_bl_param_l_cri"), right, left, 1, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_grd"), 6, 0, true);
  right = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_r_grd"), 6, 0, true);
  left = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_l_grd"), 6, 0, true);
  if (left != nullptr) {
    left->unknown79 = 1;
  }
  GfMenuDiffAdapter::create(acc.searchChild("LAY_status_bl_param_now_grd"), right, left, 3, true);
  GfMenuDiffAdapter::create(acc.searchChild("LAY_status_bl_param_dif_grd"), right, left, 4, true);
  GfMenuDiffAdapter::create(acc.searchChild("TXT_status_bl_param_l_grd"), right, left, 1, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_power"), 0x37, 0, true);
  right = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_r_power"), 0x37, 0, true);
  left = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_l_power"), 0x37, 0, true);
  if (left != nullptr) {
    left->unknown79 = 1;
  }
  GfMenuDiffAdapter::create(acc.searchChild("LAY_status_bl_param_now_power"), right, left, 3, true);
  GfMenuDiffAdapter::create(acc.searchChild("LAY_status_bl_param_dif_power"), right, left, 4, true);
  GfMenuDiffAdapter::create(acc.searchChild("TXT_status_bl_param_l_power"), right, left, 1, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_status_bl_param_rank"), 0x54, 0, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_status_bl_param_rarity"), 0x55, 0, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_name_owner"), 0x3d, 0, true);
  GfMenuWeaponAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_name_wpn"), 0, 0, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_txt_kzn_l"), 0x4e, 0, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_txt_kzn_r"), 0x4f, 0, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_ct"), 0x46, 0, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_name_aff"), 0x4d, 0, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_idx_buff"), 0x50, 0, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_status_bl_param_buff"), 0x51, 0, true);
  for (u32 i = 0; i != 4; i++) {
    name.format("TXT_status_bl_param_sp_name@%02d", i + 1);
    GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 0x2b, 0, true);
    if (adapter != nullptr) {
      adapter->unknown80 = i;
      name.format("LAY_status_bl_param_sp@%02d", i + 1);
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("TXT_status_bl_param_sp_cap@%02d", i + 1);
    adapter = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 0x2c, 0, true);
    if (adapter != nullptr) {
      adapter->unknown80 = i;
    }
    name.format("IMG_status_bl_param_sp_icon@%02d", i + 1);
    ui::UIObjectAcc icon(acc.unknown10, name.c_str());
    icon.setImageIndex(i + 1);
  }
  for (u32 i = 0; i < 3; i++) {
    name.format("TXT_status_bl_param_bs_name@%02d", i + 1);
    GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 0x2d, 0, true);
    if (adapter != nullptr) {
      adapter->unknown80 = i;
      name.format("LAY_status_bl_param_bs@%02d", i + 1);
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("TXT_status_bl_param_bs_cap@%02d", i + 1);
    adapter = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 0x2e, 0, true);
    if (adapter != nullptr) {
      adapter->unknown80 = i;
    }
  }
  for (u32 i = 1; i != 4; i++) {
    int slot = i - 1;
    name.format("TXT_status_bl_param_btl_name@%02d", i);
    GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 0x32, 0, true);
    if (adapter != nullptr) {
      adapter->unknown80 = slot;
      name.format("LAY_status_bl_param_btl@%02d", i);
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("TXT_status_bl_param_btl_cap@%02d", i);
    adapter = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 0x33, 0, true);
    if (adapter != nullptr) {
      adapter->unknown80 = slot;
    }
    name.format("TXT_status_bl_param_btl_lv@%02d", i);
    adapter = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 0x34, 0, true);
    if (adapter != nullptr) {
      adapter->unknown80 = slot;
    }
  }
  for (u32 i = 1; i != 4; i++) {
    int slot = i - 1;
    name.format("TXT_status_bl_param_fs_name@%02d", i);
    GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 0x2f, 0, true);
    if (adapter != nullptr) {
      adapter->unknown80 = slot;
      name.format("LAY_status_bl_param_fs@%02d", i);
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("TXT_status_bl_param_fs_cap@%02d", i);
    adapter = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 0x30, 0, true);
    if (adapter != nullptr) {
      adapter->unknown80 = slot;
    }
    name.format("TXT_status_bl_param_fs_lv@%02d", i);
    adapter = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 0x31, 0, true);
    if (adapter != nullptr) {
      adapter->unknown80 = slot;
    }
  }
  for (u32 i = 1; i != 4; i++) {
    u32 slot = i - 1;
    name.format("TXT_status_bl_param_asc_name@%02d", i);
    GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromReferenceBladeEquip(acc.searchChild(name.c_str()), 0, 0, slot, true);
    if (adapter != nullptr) {
      adapter->unknown70 = slot;
      name.format("LAY_status_bl_param_asc@%02d", i);
      adapter->unknown24 = acc.searchChild(name.c_str());
      name.format("TXT_status_bl_param_asc_cap@%02d", i);
      GfMenuItemAdapter::createFromReferenceBladeEquip(acc.searchChild(name.c_str()), 9, 0, slot, true);
      adapter->unknown70 = slot;
    } else {
      name.format("TXT_status_bl_param_asc_cap@%02d", i);
      GfMenuItemAdapter::createFromReferenceBladeEquip(acc.searchChild(name.c_str()), 9, 0, slot, true);
    }
  }
}

void GfMenuObjCmnStatus::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case GfMenuTypes::unknown003_257: {
    u32 target = event.unknown08;
    u32 size = event.unknown0c;
    int mode = event.unknown10;
    if (target != 0) {
      GfMenuObject::enableInput(acc.unknown10);
      if (mode == 1) {
        GfMenuObject::setupInputSelection(acc.unknown10, 0, size);
      }
    } else {
      GfMenuObject::disableInput(acc.unknown10);
    }
    GfMenuObject::migrateInput(acc.unknown10, target);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf
