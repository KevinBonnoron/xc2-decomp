#include "gf/menu/adapter/gf_menu_element_combo_adapter.h"

#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "ui/ui_str.h"

namespace gf {

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
