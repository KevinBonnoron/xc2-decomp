#include "gf/object/component/pc/gf_pc_pad_field.h"

#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/bitflag.h"

namespace gf {

namespace pc {

constexpr int PAD_TYPE_FIELD = 0;

PadField::PadField() : property(nullptr) {}

void PadField::setup(int padNo, GfComPropertyPc &property) {
  relay.bind(padNo, PAD_TYPE_FIELD, getAllocator(ALLOCATOR_DEFAULT));
  relay.bindAction("decide", this, &PadField::decideAction);
  relay.bindAction("jump", this, &PadField::jumpAction);
  relay.bindAction("lock", this, &PadField::lockAction);
  relay.bindAction("wall_release", this, &PadField::wallReleaseAction);
  relay.bindAction("lure", this, &PadField::lureAction);
  relay.bindAxis("move_front", this, &PadField::moveFront);
  relay.bindAxis("move_side", this, &PadField::moveSide);
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
  if (property != nullptr && property->isFieldControl) {
    property->input.y = value;
  }
}

void PadField::moveSide(f32 value) {
  if (property != nullptr && property->isFieldControl) {
    property->input.x = value;
  }
}

void PadField::cleanup(GfComPropertyPc &property) { relay.unbind(); }

void PadField::update(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  this->property = &property;
  relay.update();
  this->property = nullptr;
}

void PadField::setInput(InputID id) const {
  if (property != nullptr) {
    property->input.flags.set(id);
  }
}

} // namespace pc
} // namespace gf
