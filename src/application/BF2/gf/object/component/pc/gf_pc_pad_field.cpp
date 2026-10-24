#include "gf/object/component/pc/gf_pc_pad_field.h"

#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/bitflag.h"

namespace gf {

namespace pc {

constexpr int PAD_TYPE_FIELD = 0;

PadField::PadField() : unknown40(nullptr) {}

void PadField::setup(int padNo, GfComPropertyPc &property) {
  unknown08.bind(padNo, PAD_TYPE_FIELD, getAllocator(ALLOCATOR_DEFAULT));
  unknown08.bindAction("decide", this, &PadField::decideAction);
  unknown08.bindAction("jump", this, &PadField::jumpAction);
  unknown08.bindAction("lock", this, &PadField::lockAction);
  unknown08.bindAction("wall_release", this, &PadField::wallReleaseAction);
  unknown08.bindAction("lure", this, &PadField::lureAction);
  unknown08.bindAxis("move_front", this, &PadField::moveFront);
  unknown08.bindAxis("move_side", this, &PadField::moveSide);
}

void PadField::decideAction() const { setInput(INPUT_ID_DECIDE); }

void PadField::jumpAction() const {
  if (!GfGameManager::isDisableJumpForRide()) {
    setInput(INPUT_ID_JUMP);
  }
}

void PadField::lockAction() const {
  if (!GfGameManager::isDisableAutoRun()) {
    setInput(INPUT_ID_LOCK);
  }
}

void PadField::wallReleaseAction() const { setInput(INPUT_ID_WALL_RELEASE); }

void PadField::lureAction() const { setInput(INPUT_ID_LURE); }

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
