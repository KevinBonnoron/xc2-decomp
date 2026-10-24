#include "gf/object/component/pc/gf_pc_pad_battle.h"

#include "battle/battle_global.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/bitflag.h"

namespace gf {

namespace pc {

constexpr int PAD_TYPE_BATTLE = 1;
constexpr int PAD_TYPE_BATTLE_TARGET = 3;

PadBattle::PadBattle() : unknown78(nullptr) {}

void PadBattle::setup(int padNo, GfComPropertyPc &property) {
  unknown08.bind(padNo, PAD_TYPE_BATTLE, getAllocator(ALLOCATOR_DEFAULT));
  unknown08.bindAction("btl_start", this, &PadBattle::battleStart);
  unknown08.bindAction("btl_end", this, &PadBattle::battleEnd);
  unknown08.bindAction("art_01", this, &PadBattle::art01);
  unknown08.bindAction("art_02", this, &PadBattle::art02);
  unknown08.bindAction("art_03", this, &PadBattle::art03);
  unknown08.bindAction("blade_change_00", this, &PadBattle::bladeChange00);
  unknown08.bindAction("blade_change_01", this, &PadBattle::bladeChange01);
  unknown08.bindAction("blade_change_02", this, &PadBattle::bladeChange02);
  unknown08.bindAction("kakusei", this, &PadBattle::kakusei);
  unknown08.bindAction("request_permit_01", this, &PadBattle::requestPermit01);
  unknown08.bindAction("request_permit_02", this, &PadBattle::requestPermit02);
  unknown08.bindAction("sp_attack", this, &PadBattle::spAttack);
  unknown08.bindAction("chain_attack", this, &PadBattle::chainAttack);
  unknown08.bindAction("battle_rescue", this, &PadBattle::battlRescue);
  unknown08.bindAction("change_camera_mode", this, &PadBattle::changeCameraMode);
  unknown08.bindAction("tactics", this, &PadBattle::orderRally);
  unknown08.bindAxis("move_front", this, &PadBattle::moveFront);
  unknown08.bindAxis("move_side", this, &PadBattle::moveSide);
  unknown40.bind(padNo, PAD_TYPE_BATTLE_TARGET, getAllocator(ALLOCATOR_DEFAULT));
  unknown40.bindAction("select_right", this, &PadBattle::changeTargetR);
  unknown40.bindAction("select_left", this, &PadBattle::changeTargetL);
}

void PadBattle::battleStart() const { setInput(INPUT_ID_BATTLE_START); }

void PadBattle::battleEnd() const { setInput(INPUT_ID_ART_03); }

void PadBattle::art01() const { setInput(INPUT_ID_ART_01); }

void PadBattle::art02() const { setInput(INPUT_ID_ART_02); }

void PadBattle::art03() const { setInput(INPUT_ID_ART_03); }

void PadBattle::bladeChange00() const { setInput(INPUT_ID_BLADE_CHANGE_00); }

void PadBattle::bladeChange01() const { setInput(INPUT_ID_BLADE_CHANGE_01); }

void PadBattle::bladeChange02() const { setInput(INPUT_ID_BLADE_CHANGE_02); }

void PadBattle::kakusei() const { setInput(INPUT_ID_KAKUSEI); }

void PadBattle::requestPermit01() const { setInput(INPUT_ID_REQUEST_PERMIT_01); }

void PadBattle::requestPermit02() const { setInput(INPUT_ID_REQUEST_PERMIT_02); }

void PadBattle::spAttack() const { setInput(INPUT_ID_SP_ATTACK); }

void PadBattle::chainAttack() const { setInput(INPUT_ID_CHAIN_ATTACK); }

void PadBattle::battlRescue() const { setInput(INPUT_ID_BATTLE_RESCUE); }

void PadBattle::changeCameraMode() const { setInput(INPUT_ID_CHANGE_CAMERA_MODE); }

void PadBattle::orderRally() const { setInput(INPUT_ID_ORDER_RALLY); }

void PadBattle::moveFront(f32 value) {
  if (unknown78 != nullptr && unknown78->unknown110_1) {
    unknown78->unknown60.unknown04 = value;
  }
}

void PadBattle::moveSide(f32 value) {
  if (unknown78 != nullptr && unknown78->unknown110_1) {
    unknown78->unknown60.unknown00 = value;
  }
}

void PadBattle::changeTargetR() const { setInput(INPUT_ID_CHANGE_TARGET_R); }

void PadBattle::changeTargetL() const { setInput(INPUT_ID_CHANGE_TARGET_L); }

void PadBattle::cleanup(GfComPropertyPc &property) {
  unknown08.unbind();
  unknown40.unbind();
}

void PadBattle::update(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  this->unknown78 = &property;
  unknown08.update();
  unknown40.update();
  this->unknown78 = nullptr;
}

void PadBattle::setInput(InputID id) const {
  if (unknown78 == nullptr) {
    return;
  }

  switch (id) {
  case INPUT_ID_BATTLE_END:
  case INPUT_ID_ART_03:
    id = btl::BattleGlobal::get()->unknown65e1_6 ? INPUT_ID_BATTLE_END : INPUT_ID_ART_03;
    break;
  case INPUT_ID_ART_01:
  case INPUT_ID_KAKUSEI:
    id = btl::BattleGlobal::get()->unknown65e1_6 ? INPUT_ID_KAKUSEI : INPUT_ID_ART_01;
    break;
  case INPUT_ID_ART_02:
  case INPUT_ID_CHANGE_TARGET_L:
    id = btl::BattleGlobal::get()->unknown65e1_6 ? INPUT_ID_CHANGE_TARGET_L : INPUT_ID_ART_02;
    break;
  case INPUT_ID_SP_ATTACK:
  case INPUT_ID_CHANGE_TARGET_R:
    id = btl::BattleGlobal::get()->unknown65e1_6 ? INPUT_ID_CHANGE_TARGET_R : INPUT_ID_SP_ATTACK;
    break;
  default:
    break;
  }
  unknown78->unknown60.unknown08.set(id);
}

} // namespace pc
} // namespace gf
