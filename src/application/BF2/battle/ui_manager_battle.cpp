#include "battle/ui_manager_battle.h"

#include "battle/battle_global.h"
#include "battle/btl_system_balance_access.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "bdat.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/object/gf_menu_obj_action_window.h"
#include "gf/menu/object/gf_menu_obj_arts_palette.h"
#include "gf/menu/object/gf_menu_obj_blade_change.h"
#include "gf/menu/object/gf_menu_obj_chain_icon.h"
#include "gf/menu/object/gf_menu_obj_damage_buff.h"
#include "gf/menu/object/gf_menu_obj_element_eff.h"
#include "gf/menu/object/gf_menu_obj_special_gauge.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_vec3.h"

namespace btl {

constexpr int TUTORIAL_COUNT = 32;

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

void UIManager::RegisterTutorial(u32 tutorial, f32 time, bool isRequest) {
  u8 *bdat = gf::GfDataBdat::getFP(0xe4);
  int top = Bdat::getIdTop(bdat);
  if (gf::GfGameFlag::getLocal(1, tutorial + 0xc710 - top) == 0) {
    unknown30 |= 1 << (tutorial - 1);
    unknown34 = unknown34 > time ? unknown34 : time;
    if (isRequest) {
      unknown45_1 = true;
      unknown45_2 = tutorial != 1;
    }
  }
}

void UIManager::DispSystemMessageUI(const BattleCharacter *character, int message, bool flag) {
  gf::GfMenuObjDamageBuff::OpenParam param;
  param.unknown00 = !flag;
  param.unknown10 = gf::GfDataBdat::getFP(0x158);
  param.unknown18 = BtlSystemBalanceAccess::get()->unknownc6[message];
  param.unknown20 = character->unknown10;
  param.unknown20.y += character->GetCharacterParameterConst(true)->unknown38;
  gf::GfMenuObjDamageBuff::open(param);
}

void UIManager::DispUniteComboUI(const mm::Vec3 &position, int attribute, int combo) {
  gf::GfMenuObjDamageBuff::OpenUniteParam param;
  param.unknown10 = position;
  param.unknown00 = attribute;
  param.unknown04 = combo;
  gf::GfMenuObjDamageBuff::openUniteCombo(param);
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

void UIManager::UpdateRescueUI() {
  if (unknown20 == gf::INVALID_HANDLE) {
    if (unknown28) {
      gf::GfMenuObjActionWindow::closeBattle();
      unknown28 = false;
    }
  } else if (!unknown28) {
    static u32 padKey = gf::pc::StateUtil::getFwPadKey("battle_rescue");
    gf::GfMenuObjActionWindow::OpenParam param;
    param.unknown00 = unknown20;
    param.unknown08 = padKey;
    gf::GfMenuObjActionWindow::openBattle(param);
    unknown28 = true;
  }
  unknown20 = gf::INVALID_HANDLE;
}

void UIManager::UpdateTutorial(const fw::UpdateInfo &updateInfo) {
  u32 tutorials = unknown30;
  if (tutorials != 0) {
    if (BattleGlobal::get()->unknown65de_0 && CharacterManager::get()->IsExistBattleEnemy(nullptr, gf::INVALID_HANDLE, false) && BattleGlobal::get()->IsEnableBattle()) {
      unknown34 -= updateInfo.unknown00;
      if (unknown34 > 0.0f) {
        return;
      }
      if (unknown45_2 && !unknown44_7) {
        return;
      }
      for (int tutorial = 1;; tutorial++) {
        if ((tutorials & 1) != 0) {
          gf::GfMenuManager::startTutorial(tutorial);
        }
        tutorials >>= 1;
        if (tutorials == 0 || tutorial >= TUTORIAL_COUNT) {
          break;
        }
      }
    }
    unknown30 = 0;
    unknown34 = -1.0f;
    unknown45_1 = false;
    unknown45_2 = false;
  }
}

} // namespace btl
