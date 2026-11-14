#include "gf/menu/adapter/gf_menu_element_combo_adapter.h"

#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {
struct GF_OBJ_HANDLE;

// Inferred role: route number of an element combo without route; original name unknown.
constexpr int ELEMENT_COMBO_ROUTE_UNKNOWN_7 = 7;
// Inferred role: battle state read by GfMenuManager::isBattleState, normal; original name unknown.
constexpr u32 BATTLE_STATE_UNKNOWN_0 = 0;
constexpr u32 BATTLE_STATE_UNKNOWN_1 = 1;

static GfMenuElementComboAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuElementComboAdapter::update_ComboRouteColor, {GfMenuAdapter::unknown004_8, 0, 0}},
    {&GfMenuElementComboAdapter::update_ComboRouteIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuElementComboAdapter::update_ComboRouteEffectName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuElementComboAdapter::update_ComboRouteEffect, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuElementComboAdapter::update_ComboRouteAttrPtn, {GfMenuAdapter::unknown004_9, 0, 0}},
    {&GfMenuElementComboAdapter::update_ComboRoutePassedDisp, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuElementComboAdapter::update_ComboRouteCurrentDisp, {GfMenuAdapter::unknown004_3, 0, 0}},
};

GfMenuElementComboAdapter::GfMenuElementComboAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, true, isUpdateAlways), unknown50(0), unknown54(ELEMENT_COMBO_ROUTE_UNKNOWN_7), unknown58(nullptr) {}

GfMenuElementComboAdapter *GfMenuElementComboAdapter::create(u32 handle, u32 type, u32 elementCombo, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 149 as in the original source: it is the line argument of operator new.
#line 149
      GfMenuElementComboAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuElementComboAdapter(plugin, isUpdateAlways);
      adapter->unknown30.bind(adapter, info.update);
      adapter->unknown50 = elementCombo;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

GfMenuElementComboAdapter *GfMenuElementComboAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  GfMenuElementComboAdapter *adapter = create(handle, type, converter->getElementComboId(), isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown54 = converter->getElementComboRouteNo();
    adapter->unknown58 = converter;
  }
  return adapter;
}

GfMenuElementComboAdapter *GfMenuElementComboAdapter::createReferenceRoute(u32 handle, u32 type, u32 routeNo, bool isUpdateAlways) {
  // __LINE__ must be 178 as in the original source: it is the line argument of operator new.
#line 178
  ReferenceRouteConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceRouteConverter(routeNo);
  return createFromCoverter(handle, type, converter, isUpdateAlways);
}

GfMenuElementComboAdapter::~GfMenuElementComboAdapter() {
  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }
}

bool GfMenuElementComboAdapter::update_ComboRouteColor() {
  u8 atr = GfMenuObjUtil::getElementComboAtr(unknown50);
  mm::mtl::FixStr<32> color;
  color.format("elemental%02d", atr);
  setAddColor(color.c_str());
  return true;
}

bool GfMenuElementComboAdapter::update_ComboRouteIcon() {
  setNumber(GfMenuObjUtil::getElementComboAtr(unknown50));
  return true;
}

bool GfMenuElementComboAdapter::update_ComboRouteEffectName() {
  setText(GfMenuObjUtil::getElementComboEffectName(unknown50));
  return true;
}

bool GfMenuElementComboAdapter::update_ComboRouteEffect() {
  setNumber(GfMenuObjUtil::getElementComboEffect(unknown50));
  return true;
}

bool GfMenuElementComboAdapter::update_ComboRouteAttrPtn() {
  u8 atr = GfMenuObjUtil::getElementComboAtr(unknown50);
  mm::mtl::FixStr<32> pattern;
  pattern.format("element%02d", atr);
  setTextFacePattern(pattern.c_str());
  return true;
}

bool GfMenuElementComboAdapter::update_ComboRouteCurrentDisp() {
  u32 current = GfMenuReference::getElementComboRootCurrent();
  return unknown54 == current;
}

bool GfMenuElementComboAdapter::update_ComboRoutePassedDisp() {
  if (idDispComboRouteNo(unknown54)) {
    return true;
  }
  return false;
}

bool GfMenuElementComboAdapter::idDispComboRouteNo(u32 routeNo) {
  u32 current = GfMenuReference::getElementComboRootCurrent();
  if (current != routeNo) {
    switch (current) {
    case 0:
      break;
    case 1:
      switch (routeNo) {
      case 2:
      case 5:
      case 6:
        return false;
      }
      break;
    case 2:
      switch (routeNo) {
      case 1:
      case 3:
      case 4:
        return false;
      }
      break;
    case 7:
      return false;
    default:
      if (routeNo >= 3 && routeNo <= 6) {
        return false;
      }
      if (!(current == 3 || current == 4)) {
        if (routeNo == 1 && (current == 5 || current == 6)) {
          return false;
        }
      } else if (routeNo == 2) {
        return false;
      }
      break;
    }
  }
  return true;
}

GfObjPropertyEnemy *GfMenuElementComboAdapter::getTargetProperty() {
  GF_OBJ_HANDLE *handle = GfMenuManager::getTargetObjHandle();
  if (handle == unknown020) {
    return nullptr;
  }
  GfObjAcc acc(handle);
  if (acc.getType() != OBJECT_TYPE_ENEMY) {
    return nullptr;
  }
  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property == nullptr) {
    return nullptr;
  }
  return property->getEnemy();
}

u32 GfMenuElementComboAdapter::getTargetElementComboId() {
  GfObjPropertyEnemy *enemy = getTargetProperty();
  if (enemy == nullptr) {
    return 0;
  }
  return enemy->unknowndc;
}

u32 GfMenuElementComboAdapter::getTargetElementComboLv() {
  GfObjPropertyEnemy *enemy = getTargetProperty();
  if (enemy == nullptr) {
    return 0;
  }
  if (enemy->unknowndc != 0) {
    return enemy->unknowne8;
  }
  return 0;
}

u32 GfMenuElementComboAdapter::ReferenceRouteConverter::getElementComboRouteNo() { return routeNo; }

u32 GfMenuElementComboAdapter::ReferenceRouteConverter::getElementComboId() {
  const GfMenuReference::ElemComboRoot &root = GfMenuReference::getElementComboRootInfo(routeNo);
  if (getTargetElementComboLv() != 0) {
    return root.unknown00;
  }
  return 0;
}

u32 GfMenuElementComboAdapter::TargetEnemyConverter::getElementComboRouteNo() { return ELEMENT_COMBO_ROUTE_UNKNOWN_7; }

u32 GfMenuElementComboAdapter::TargetEnemyConverter::getElementComboId() { return getTargetElementComboId(); }

void GfMenuElementComboAdapter::update(const fw::UpdateInfo &info) {
  if (unknown58 != nullptr) {
    u32 combo = unknown58->getElementComboId();
    if (unknown50 != combo) {
      unknown50 = combo;
      setChange();
    }
  }

  if (unknown30.isValid() && (unknown20 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1)) != 0 && (GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_0) || GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_1))) {
    if (unknown50 != 0) {
      setDisp(unknown30());
    } else {
      setDisp(false);
    }
    unknown20 &= ~FLAG_UNKNOWN_0;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuElementComboAdapter>(const mm::mtl::Delegate<bool()> *);
