#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_sound_listener.h"
#include "types.h"

namespace ssd {

void SoundListener::Connect() {
  if (SoundCore::instance_ != nullptr) {
    SoundCore::instance_->AddSoundListener(this);
    isConnect = true;
  }
}

SoundListener::~SoundListener() { Disconnect(); }

void SoundListener::Disconnect() {
  if (isConnect) {
    isConnect = false;
    SoundCore::instance_->RemoveSoundListener(this);
  }
}

void SoundListener::Init() { Connect(); }

void SoundListener::Quit() { Disconnect(); }

void SoundListener::SetParam(const Vec3 &position, const Vec3 &look, const Vec3 &up) {
  param.position = position;
  param.look = look;
  param.up = up;
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::SetPosition(const Vec3 &position) {
  param.position = position;
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::SetPosition(const f32 *position) {
  param.position.x = position[0];
  param.position.y = position[1];
  param.position.z = position[2];
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::SetPosition(f32 x, f32 y, f32 z) {
  param.position.x = x;
  param.position.y = y;
  param.position.z = z;
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::SetLook(const Vec3 &look) {
  param.look = look;
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::SetLook(const f32 *look) {
  param.look.x = look[0];
  param.look.y = look[1];
  param.look.z = look[2];
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::SetLook(f32 x, f32 y, f32 z) {
  param.look.x = x;
  param.look.y = y;
  param.look.z = z;
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::SetUp(const Vec3 &up) {
  param.up = up;
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::SetUp(const f32 *up) {
  param.up.x = up[0];
  param.up.y = up[1];
  param.up.z = up[2];
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::SetUp(f32 x, f32 y, f32 z) {
  param.up.x = x;
  param.up.y = y;
  param.up.z = z;
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::SetOrientation(const Vec3 &look, const Vec3 &up) {
  param.look = look;
  param.up = up;
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::SetOrientation(f32 lookX, f32 lookY, f32 lookZ, f32 upX, f32 upY, f32 upZ) {
  param.look.x = lookX;
  param.look.y = lookY;
  param.look.z = lookZ;
  param.up.x = upX;
  param.up.y = upY;
  param.up.z = upZ;
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::LookAt(const Vec3 &position, const Vec3 &look, const Vec3 &up) {
  param.position = position;
  param.look = look;
  param.up = up;
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::LookAt(const f32 *position, const f32 *look, const f32 *up) {
  param.position.x = position[0];
  param.position.y = position[1];
  param.position.z = position[2];
  param.look.x = look[0];
  param.look.y = look[1];
  param.look.z = look[2];
  param.up.x = up[0];
  param.up.y = up[1];
  param.up.z = up[2];
  isCalcVelocity = true;
  isUpdate = true;
}

void SoundListener::SetVelocity(const Vec3 &velocity) {
  param.velocity = velocity;
  isCalcVelocity = false;
  isUpdateVelocity = true;
}

void SoundListener::SetVelocity(f32 x, f32 y, f32 z) {
  param.velocity.x = x;
  param.velocity.y = y;
  param.velocity.z = z;
  isCalcVelocity = false;
  isUpdateVelocity = true;
}

f32 SoundListener::GetInteriorSize() const { return interiorSize; }

void SoundListener::SetInteriorSize(f32 size) { interiorSize = size; }

f32 SoundListener::GetDopplerFactor() const { return dopplerFactor; }

void SoundListener::SetDopplerFactor(f32 factor) {
  dopplerFactor = factor;
  isEnableDoppler = factor != 0.0f;
}

bool SoundListener::IsEnableDoppler() const { return isEnableDoppler; }

void SoundListener::UpdateGameFrame(f32 deltaTime) {
  if (isCalcVelocity) {
    param.velocity.x = applyParam.position.x - param.position.x;
    param.velocity.y = applyParam.position.y - param.position.y;
    param.velocity.z = applyParam.position.z - param.position.z;
    isUpdateVelocity = true;
  }
  if (!isUpdate && !isUpdateVelocity) {
    return;
  }
  isCalcVelocity = false;
  isUpdate = false;
  isUpdateVelocity = false;
  __builtin_memcpy(&applyParam, &param, sizeof(Param));
  isValidMatrix = true;
  UpdateMatrix();
}

void SoundListener::UpdateMatrix() { Mat34LookAt(&matrix, &applyParam.position, &applyParam.look, &applyParam.up); }

void SoundListener::Vec3Transform(const Vec3 *in, Vec3 *out) { ssd::Vec3Transform(&matrix, in, out); }

} // namespace ssd
