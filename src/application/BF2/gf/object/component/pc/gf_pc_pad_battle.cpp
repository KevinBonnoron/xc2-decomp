#include "gf/object/component/pc/gf_pc_pad_battle.h"

#include "battle/battle_global.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/pc/gf_pc_asm_callback.h"
#include "mm_mtl/bitflag.h"

namespace anm {
class ResASM;
} // namespace anm

namespace gf {
struct GF_OBJ_HANDLE;

namespace pc {

constexpr int PAD_TYPE_UNKNOWN_1 = 1; // Inferred role: pad type battle; original name unknown.
constexpr int PAD_TYPE_UNKNOWN_3 = 3; // Inferred role: pad type battle target; original name unknown.

bool registerAsmCallbackBattle(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm) { return false; }

PadBattle::PadBattle() : unknown78(nullptr) {}

void PadBattle::setup(int padNo, GfComPropertyPc &property) {
  unknown08.bind(padNo, PAD_TYPE_UNKNOWN_1, getAllocator(ALLOCATOR_UNKNOWN_0));
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
  unknown40.bind(padNo, PAD_TYPE_UNKNOWN_3, getAllocator(ALLOCATOR_UNKNOWN_0));
  unknown40.bindAction("select_right", this, &PadBattle::changeTargetR);
  unknown40.bindAction("select_left", this, &PadBattle::changeTargetL);
}

void PadBattle::battleStart() const { setInput(INPUT_ID_UNKNOWN_5); }

void PadBattle::battleEnd() const { setInput(INPUT_ID_UNKNOWN_9); }

void PadBattle::art01() const { setInput(INPUT_ID_UNKNOWN_7); }

void PadBattle::art02() const { setInput(INPUT_ID_UNKNOWN_8); }

void PadBattle::art03() const { setInput(INPUT_ID_UNKNOWN_9); }

void PadBattle::bladeChange00() const { setInput(INPUT_ID_UNKNOWN_10); }

void PadBattle::bladeChange01() const { setInput(INPUT_ID_UNKNOWN_11); }

void PadBattle::bladeChange02() const { setInput(INPUT_ID_UNKNOWN_12); }

void PadBattle::kakusei() const { setInput(INPUT_ID_UNKNOWN_13); }

void PadBattle::requestPermit01() const { setInput(INPUT_ID_UNKNOWN_14); }

void PadBattle::requestPermit02() const { setInput(INPUT_ID_UNKNOWN_15); }

void PadBattle::spAttack() const { setInput(INPUT_ID_UNKNOWN_16); }

void PadBattle::chainAttack() const { setInput(INPUT_ID_UNKNOWN_17); }

void PadBattle::battlRescue() const { setInput(INPUT_ID_UNKNOWN_18); }

void PadBattle::changeCameraMode() const { setInput(INPUT_ID_UNKNOWN_19); }

void PadBattle::orderRally() const { setInput(INPUT_ID_UNKNOWN_20); }

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

void PadBattle::changeTargetR() const { setInput(INPUT_ID_UNKNOWN_21); }

void PadBattle::changeTargetL() const { setInput(INPUT_ID_UNKNOWN_22); }

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
  case INPUT_ID_UNKNOWN_6:
  case INPUT_ID_UNKNOWN_9:
    id = btl::BattleGlobal::get()->unknown65e1_6 ? INPUT_ID_UNKNOWN_6 : INPUT_ID_UNKNOWN_9;
    break;
  case INPUT_ID_UNKNOWN_7:
  case INPUT_ID_UNKNOWN_13:
    id = btl::BattleGlobal::get()->unknown65e1_6 ? INPUT_ID_UNKNOWN_13 : INPUT_ID_UNKNOWN_7;
    break;
  case INPUT_ID_UNKNOWN_8:
  case INPUT_ID_UNKNOWN_22:
    id = btl::BattleGlobal::get()->unknown65e1_6 ? INPUT_ID_UNKNOWN_22 : INPUT_ID_UNKNOWN_8;
    break;
  case INPUT_ID_UNKNOWN_16:
  case INPUT_ID_UNKNOWN_21:
    id = btl::BattleGlobal::get()->unknown65e1_6 ? INPUT_ID_UNKNOWN_21 : INPUT_ID_UNKNOWN_16;
    break;
  default:
    break;
  }
  unknown78->unknown60.unknown08.set(id);
}

} // namespace pc
} // namespace gf

template void mm::mtl::Delegate<void()>::memberFuncInvoker<gf::pc::PadBattle>(const mm::mtl::Delegate<void()> *);
template void mm::mtl::Delegate<void(float)>::memberFuncInvoker<gf::pc::PadBattle>(const mm::mtl::Delegate<void(float)> *, float);
