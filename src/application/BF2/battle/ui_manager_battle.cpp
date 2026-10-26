#include "battle/ui_manager_battle.h"

#include "bdat.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/menu/call/gf_menu_call_context.h"
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
  if (id != 0 && !unknown15 && unknown10 == id) {
    gf::GfMenuObjElementEff::cancel(unknown08);
    unknown15 = true;
  }
}

void UIManager::SetKakuseiData(bool isEnableKakusei, bool isKakusei, f32 kakuseiRestTimeRatio) {
  this->unknown1c = isEnableKakusei;
  this->unknown18 = kakuseiRestTimeRatio;
  this->unknown1d = isKakusei;
}

void UIManager::RegisterRescueUI(gf::GF_OBJ_HANDLE *handle) { unknown20 = handle; }

u32 UIManager::StartElementalComboDirectionUI(int attribute) {
  if (unknown08 == nullptr) {
    unknown08 = gf::GfMenuCallContext::create();
  } else {
    unknown08->reset();
  }

  u32 id = 0;
  if (unknown08 != nullptr) {
    id = unknown38;
    unknown38 = id < 0xfffffffe ? id + 1 : 1;
    gf::GfMenuObjElementEff::StartParam param;
    param.attribute = attribute;
    gf::GfMenuObjElementEff::start(unknown08, param);
  }

  unknown10 = id;
  unknown14 = attribute;
  unknown15 = false;
  return id;
}

void UIManager::DispChainUI(gf::GF_OBJ_HANDLE *handle) {
  gf::GfMenuObjChainIcon::OpenParam param;
  param.unknown00 = handle;
  gf::GfMenuObjChainIcon::open(param);
}

void UIManager::NotifyMapChange() {
  u8 *bdat = gf::GfDataBdat::getFP(0xe4);
  int top = Bdat::getIdTop(bdat);
  int base = 0xc710 - top;
  if (gf::GfGameFlag::getLocal(1, base + 0xc) != 0) {
    gf::GfGameFlag::setLocal(1, base + 0xd, 1);
  }
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
    unknown44_3 = true;
    break;
  case INPUT_TYPE_REVERSE_PALETTE_1:
    unknown44_4 = true;
    break;
  case INPUT_TYPE_REVERSE_PALETTE_2:
    unknown44_5 = true;
    break;
  case INPUT_TYPE_REVERSE_PALETTE_3:
    unknown44_6 = true;
    break;
  }
}

} // namespace btl
