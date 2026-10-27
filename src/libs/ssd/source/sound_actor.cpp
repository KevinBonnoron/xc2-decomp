#include "ssd/ssd_array.h"
#include "ssd/ssd_array_impl.h"    // IWYU pragma: keep
#include "ssd/ssd_behavior_impl.h" // IWYU pragma: keep
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"
#include "types.h"

namespace ssd {
class SoundListener;

SoundActor::~SoundActor() { Quit(); }

Result SoundActor::Init() {
  if (unknown30) {
    return static_cast<Result>(-15);
  }
  static_cast<SystemCore *>(SoundCore::instance_)->ConnectActor(this);
  unknown30 = true;
  return set_result(static_cast<Result>(0));
}

Result SoundActor::Quit() {
  if (unknown30) {
    unknown30 = false;
    static_cast<SystemCore *>(SoundCore::instance_)->DisconnectActor(this);
    return set_result(static_cast<Result>(0));
  }
  return static_cast<Result>(-15);
}

bool SoundActor::IsPlay() const {
  if (SoundCore::instance_ != nullptr) {
    return static_cast<SystemCore *>(SoundCore::instance_)->IsPlayActor(this);
  }
  return false;
}

long SoundActor::Play(SoundHandle *handle, const SoundEntry *entry, f32 volume, f32 fadeTime) {
  if (!unknown30) {
    Init();
    if (!unknown30) {
      return -12;
    }
  }
  return handle->Play(entry, this, volume, fadeTime);
}

Result SoundActor::Stop(f32 fadeTime) {
  static_cast<SystemCore *>(SoundCore::instance_)->StopActor(this, fadeTime);
  return static_cast<Result>(0);
}

Result SoundActor::Pause(bool isPause, f32 fadeTime) {
  static_cast<SystemCore *>(SoundCore::instance_)->PauseActor(this, isPause, fadeTime);
  return static_cast<Result>(0);
}

void SoundActor::SetPitch(f32 pitch, f32 fadeTime) { this->m_pitch = pitch; }

void SoundActor::SetVolume(f32 volume, f32 fadeTime) { this->m_volume = volume; }

void SoundActor::SetPan(f32 pan, f32 fadeTime) {}

void SoundActor::SetCategoryId(int category) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  Array<SoundHandle *> handles;
  core->LockAudio();
  core->GetPlaySoundHandleFromActor(this, &handles);
  SoundHandle **end = handles.unknown10 + handles.unknown08;
  for (SoundHandle **it = handles.unknown10; it != end; it++) {
    (*it)->SetCategoryId(category);
  }
  core->UnlockAudio();
}

int SoundActor::CountPlaySoundHandle() const { return static_cast<SystemCore *>(SoundCore::instance_)->CountPlaySoundHandleActor(this); }

SoundHandle *SoundActor::GetPlaySoundHandle(int index) const { return static_cast<SystemCore *>(SoundCore::instance_)->GetPlaySoundHandle(this, index); }

void SoundActor::UpdateGameFrame(f32 deltaTime) {}

SoundActor3D::SoundActor3D() : SoundActor(ObjectType::SOUND_ACTOR_3D), unknown50(0.0f, 0.0f, 0.0f), unknown68(true), unknown69(false), unknown6a(false), unknown6b(false), m_listener(nullptr) {
  unknown32 = true;
}

SoundActor3D::~SoundActor3D() {}

Result SoundActor3D::Init() {
  if (!unknown30) {
    static_cast<SystemCore *>(SoundCore::instance_)->ConnectActor(this);
    unknown30 = true;
    set_result(static_cast<Result>(0));
  }
  unknown69 = false;
  unknown6b = false;
  m_listener = nullptr;
  return static_cast<Result>(0);
}

long SoundActor3D::Play(SoundHandle *handle, const SoundEntry *entry, f32 volume, f32 fadeTime) {
  if (!unknown30) {
    Init();
    if (!unknown30) {
      return -12;
    }
  }
  return handle->Play(entry, this, volume, fadeTime);
}

void SoundActor3D::SetListener(const SoundListener *listener) { this->m_listener = listener; }

void SoundActor3D::SetPosition(const Vec3 &position) {
  this->unknown44 = position;
  unknown69 = true;
}

void SoundActor3D::SetPosition(f32 x, f32 y, f32 z) {
  unknown44.x = x;
  unknown44.y = y;
  unknown44.z = z;
  unknown69 = true;
}

void SoundActor3D::SetVelocity(const Vec3 &velocity) {
  this->unknown50 = velocity;
  unknown6b = true;
}

void SoundActor3D::SetVelocity(f32 x, f32 y, f32 z) {
  unknown50.x = x;
  unknown50.y = y;
  unknown50.z = z;
  unknown6b = true;
}

Result SoundActor3D::Quit() {
  if (unknown30) {
    unknown30 = false;
    static_cast<SystemCore *>(SoundCore::instance_)->DisconnectActor(this);
    return set_result(static_cast<Result>(0));
  }
  return static_cast<Result>(-15);
}

template class Array<SoundActor *>;

template class Array<SoundHandle *>;

template List<SoundActor> *List<SoundActor>::Delete();
template List<SoundActor>::Node::~Node();

} // namespace ssd
