#include "gf/object/component/pc/gf_pc_pad_field.h"

#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/bitflag.h"

namespace gf {

namespace pc {

constexpr int PAD_TYPE_UNKNOWN_0 = 0; // Inferred role: pad type field; original name unknown.

PadField::PadField() : unknown40(nullptr) {}

void PadField::setup(int padNo, GfComPropertyPc &property) {
  unknown08.bind(padNo, PAD_TYPE_UNKNOWN_0, getAllocator(ALLOCATOR_UNKNOWN_0));
  unknown08.bindAction("decide", this, &PadField::decideAction);
  unknown08.bindAction("jump", this, &PadField::jumpAction);
  unknown08.bindAction("lock", this, &PadField::lockAction);
  unknown08.bindAction("wall_release", this, &PadField::wallReleaseAction);
  unknown08.bindAction("lure", this, &PadField::lureAction);
  unknown08.bindAxis("move_front", this, &PadField::moveFront);
  unknown08.bindAxis("move_side", this, &PadField::moveSide);
}

void PadField::decideAction() const { setInput(INPUT_ID_UNKNOWN_0); }

void PadField::jumpAction() const {
  if (!GfGameManager::isDisableJumpForRide()) {
    setInput(INPUT_ID_UNKNOWN_2);
  }
}

void PadField::lockAction() const {
  if (!GfGameManager::isDisableAutoRun()) {
    setInput(INPUT_ID_UNKNOWN_1);
  }
}

void PadField::wallReleaseAction() const { setInput(INPUT_ID_UNKNOWN_3); }

void PadField::lureAction() const { setInput(INPUT_ID_UNKNOWN_4); }

void PadField::moveFront(f32 value) {
  if (unknown40 != nullptr && unknown40->unknown110_0) {
    unknown40->unknown60.unknown04 = value;
  }
}

void PadField::moveSide(f32 value) {
  if (unknown40 != nullptr && unknown40->unknown110_0) {
    unknown40->unknown60.unknown00 = value;
  }
}

void PadField::cleanup(GfComPropertyPc &property) { unknown08.unbind(); }

void PadField::update(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  this->unknown40 = &property;
  unknown08.update();
  this->unknown40 = nullptr;
}

void PadField::setInput(InputID id) const {
  if (unknown40 != nullptr) {
    unknown40->unknown60.unknown08.set(id);
  }
}

} // namespace pc
} // namespace gf

template void mm::mtl::Delegate<void()>::memberFuncInvoker<gf::pc::PadField>(const mm::mtl::Delegate<void()> *);
template void mm::mtl::Delegate<void(float)>::memberFuncInvoker<gf::pc::PadField>(const mm::mtl::Delegate<void(float)> *, float);
