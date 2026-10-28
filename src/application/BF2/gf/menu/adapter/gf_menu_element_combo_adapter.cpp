#include "gf/menu/adapter/gf_menu_element_combo_adapter.h"

#include "gf/data/gf_object_type.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "ui/ui_str.h"

namespace gf {
struct GF_OBJ_HANDLE;

constexpr int ELEMENT_COMBO_ROUTE_NONE = 7;
constexpr u32 BATTLE_STATE_NORMAL = 0;
constexpr u32 BATTLE_STATE_UNKNOWN_1 = 1;

GfMenuElementComboAdapter::GfMenuElementComboAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, true, isUpdateAlways), unknown50(0), unknown54(ELEMENT_COMBO_ROUTE_NONE), unknown58(nullptr) {}

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

GfObjPropertyEnemy *GfMenuElementComboAdapter::getTargetProperty() {
  GF_OBJ_HANDLE *handle = GfMenuManager::getTargetObjHandle();
  if (handle != INVALID_HANDLE) {
    GfObjAcc acc(handle);
    if (acc.getType() == OBJECT_TYPE_ENEMY) {
      GfObjProperty *property = GfObjUtil::getProperty(handle);
      if (property == nullptr) {
        return nullptr;
      }
      return property->getEnemy();
    }
  }
  return nullptr;
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
  GfObjPropertyEnemy *enemy = getTargetProperty();
  u32 id = 0;
  if (enemy != nullptr && enemy->unknowndc != 0 && enemy->unknowne8 != 0) {
    id = root.unknown00;
  }
  return id;
}

u32 GfMenuElementComboAdapter::TargetEnemyConverter::getElementComboRouteNo() { return ELEMENT_COMBO_ROUTE_NONE; }

u32 GfMenuElementComboAdapter::TargetEnemyConverter::getElementComboId() { return getTargetElementComboId(); }

void GfMenuElementComboAdapter::update(const fw::UpdateInfo &info) {
  if (unknown58 != nullptr) {
    u32 combo = unknown58->getElementComboId();
    if (unknown50 != combo) {
      unknown50 = combo;
      setChange();
    }
  }

  if (unknown30.isValid() && (unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0 && (GfMenuManager::isBattleState(BATTLE_STATE_NORMAL) || GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_1))) {
    if (unknown50 != 0) {
      setDisp(unknown30());
    } else {
      setDisp(false);
    }
    unknown20 &= ~FLAG_CHANGED;
  }
}

} // namespace gf
