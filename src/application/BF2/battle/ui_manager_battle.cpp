#include "battle/ui_manager_battle.h"

#include "gf/menu/object/gf_menu_obj_arts_palette.h"
#include "gf/menu/object/gf_menu_obj_blade_change.h"
#include "gf/menu/object/gf_menu_obj_chain_icon.h"
#include "gf/menu/object/gf_menu_obj_element_eff.h"
#include "gf/menu/object/gf_menu_obj_special_gauge.h"

namespace btl {

UIManager::~UIManager() {}

void UIManager::Initialize() {}

void UIManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void UIManager::Finalize() {}

void UIManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void UIManager::PreUpdateProc(const fw::UpdateInfo &) {}

void UIManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

void UIManager::ExitElementalComboDirectionUI(u32 id) {
  if (id != 0 && !isElementEffectCanceled && elementEffectId == id) {
    gf::GfMenuObjElementEff::cancel(elementEffectContext);
    isElementEffectCanceled = true;
  }
}

void UIManager::SetKakuseiData(bool isEnableKakusei, bool isKakusei, f32 kakuseiRestTimeRatio) {
  this->isEnableKakusei = isEnableKakusei;
  this->kakuseiRestTimeRatio = kakuseiRestTimeRatio;
  this->isKakusei = isKakusei;
}

void UIManager::RegisterRescueUI(gf::GF_OBJ_HANDLE *handle) { rescueTarget = handle; }

void UIManager::DispChainUI(gf::GF_OBJ_HANDLE *handle) {
  gf::GfMenuObjChainIcon::OpenParam param;
  param.handle = handle;
  gf::GfMenuObjChainIcon::open(param);
}

void UIManager::NotifyInput(INPUT_TYPE type, int value) {
  switch (type) {
  case INPUT_TYPE_ARTS_PALETTE:
    gf::GfMenuObjArtsPalette::push(value);
    break;
  case INPUT_TYPE_BLADE_CHANGE:
    gf::GfMenuObjBladeChange::pushBladeChange(value);
    break;
  case INPUT_TYPE_SPECIAL_GAUGE:
    gf::GfMenuObjSpecialGauge::push();
    break;
  case INPUT_TYPE_REVERSE_PALETTE_0:
    isPushReversePalette0 = true;
    break;
  case INPUT_TYPE_REVERSE_PALETTE_1:
    isPushReversePalette1 = true;
    break;
  case INPUT_TYPE_REVERSE_PALETTE_2:
    isPushReversePalette2 = true;
    break;
  case INPUT_TYPE_REVERSE_PALETTE_3:
    isPushReversePalette3 = true;
    break;
  }
}

} // namespace btl
