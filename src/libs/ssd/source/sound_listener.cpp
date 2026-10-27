#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_sound_listener.h"
#include "types.h"

namespace ssd {

SoundListener::SoundListener() : Object(ObjectType::SOUND_LISTENER), unknown78(false), unknown79(false), unknown7a(false), unknown7b(false), m_enableDoppler(true), m_dopplerFactor(1.0f) { Connect(); }

void SoundListener::Connect() {
  if (SoundCore::instance_ != nullptr) {
    SoundCore::instance_->AddSoundListener(this);
    unknown78 = true;
  }
}

SoundListener::~SoundListener() { Disconnect(); }

void SoundListener::Disconnect() {
  if (unknown78) {
    unknown78 = false;
    SoundCore::instance_->RemoveSoundListener(this);
  }
}

void SoundListener::Init() { Connect(); }

void SoundListener::Quit() { Disconnect(); }

void SoundListener::SetParam(const Vec3 &position, const Vec3 &look, const Vec3 &up) {
  unknown18.unknown00 = position;
  unknown18.unknown0c = look;
  unknown18.unknown18 = up;
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::SetPosition(const Vec3 &position) {
  unknown18.unknown00 = position;
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::SetPosition(const f32 *position) {
  unknown18.unknown00.x = position[0];
  unknown18.unknown00.y = position[1];
  unknown18.unknown00.z = position[2];
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::SetPosition(f32 x, f32 y, f32 z) {
  unknown18.unknown00.x = x;
  unknown18.unknown00.y = y;
  unknown18.unknown00.z = z;
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::SetLook(const Vec3 &look) {
  unknown18.unknown0c = look;
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::SetLook(const f32 *look) {
  unknown18.unknown0c.x = look[0];
  unknown18.unknown0c.y = look[1];
  unknown18.unknown0c.z = look[2];
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::SetLook(f32 x, f32 y, f32 z) {
  unknown18.unknown0c.x = x;
  unknown18.unknown0c.y = y;
  unknown18.unknown0c.z = z;
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::SetUp(const Vec3 &up) {
  unknown18.unknown18 = up;
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::SetUp(const f32 *up) {
  unknown18.unknown18.x = up[0];
  unknown18.unknown18.y = up[1];
  unknown18.unknown18.z = up[2];
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::SetUp(f32 x, f32 y, f32 z) {
  unknown18.unknown18.x = x;
  unknown18.unknown18.y = y;
  unknown18.unknown18.z = z;
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::SetOrientation(const Vec3 &look, const Vec3 &up) {
  unknown18.unknown0c = look;
  unknown18.unknown18 = up;
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::SetOrientation(f32 lookX, f32 lookY, f32 lookZ, f32 upX, f32 upY, f32 upZ) {
  unknown18.unknown0c.x = lookX;
  unknown18.unknown0c.y = lookY;
  unknown18.unknown0c.z = lookZ;
  unknown18.unknown18.x = upX;
  unknown18.unknown18.y = upY;
  unknown18.unknown18.z = upZ;
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::LookAt(const Vec3 &position, const Vec3 &look, const Vec3 &up) {
  unknown18.unknown00 = position;
  unknown18.unknown0c = look;
  unknown18.unknown18 = up;
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::LookAt(const f32 *position, const f32 *look, const f32 *up) {
  unknown18.unknown00.x = position[0];
  unknown18.unknown00.y = position[1];
  unknown18.unknown00.z = position[2];
  unknown18.unknown0c.x = look[0];
  unknown18.unknown0c.y = look[1];
  unknown18.unknown0c.z = look[2];
  unknown18.unknown18.x = up[0];
  unknown18.unknown18.y = up[1];
  unknown18.unknown18.z = up[2];
  unknown79 = true;
  unknown7a = true;
}

void SoundListener::SetVelocity(const Vec3 &velocity) {
  unknown18.unknown24 = velocity;
  unknown79 = false;
  unknown7b = true;
}

void SoundListener::SetVelocity(f32 x, f32 y, f32 z) {
  unknown18.unknown24.x = x;
  unknown18.unknown24.y = y;
  unknown18.unknown24.z = z;
  unknown79 = false;
  unknown7b = true;
}

f32 SoundListener::GetInteriorSize() const { return m_interiorSize; }

void SoundListener::SetInteriorSize(f32 size) { m_interiorSize = size; }

f32 SoundListener::GetDopplerFactor() const { return m_dopplerFactor; }

void SoundListener::SetDopplerFactor(f32 factor) {
  m_dopplerFactor = factor;
  m_enableDoppler = factor != 0.0f;
}

bool SoundListener::IsEnableDoppler() const { return m_enableDoppler; }

void SoundListener::UpdateGameFrame(f32 deltaTime) {
  if (unknown79) {
    unknown18.unknown24.x = unknown48.unknown00.x - unknown18.unknown00.x;
    unknown18.unknown24.y = unknown48.unknown00.y - unknown18.unknown00.y;
    unknown18.unknown24.z = unknown48.unknown00.z - unknown18.unknown00.z;
    unknown7b = true;
  }
  if (!unknown7a && !unknown7b) {
    return;
  }
  unknown79 = false;
  unknown7a = false;
  unknown7b = false;
  __builtin_memcpy(&unknown48, &unknown18, sizeof(Param));
  unknown7c = true;
  UpdateMatrix();
}

void SoundListener::UpdateMatrix() { Mat34LookAt(&unknown88, &unknown48.unknown00, &unknown48.unknown0c, &unknown48.unknown18); }

void SoundListener::Vec3Transform(const Vec3 *in, Vec3 *out) { ssd::Vec3Transform(&unknown88, in, out); }

} // namespace ssd
