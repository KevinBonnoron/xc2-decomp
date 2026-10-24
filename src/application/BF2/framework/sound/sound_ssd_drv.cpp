#include "framework/sound/sound_ssd_drv.h"

#include "framework/sound/sound_driver.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/allocator.h"
#include "mtl/mem_manager.h"

namespace ssd {
class SoundListener;
} // namespace ssd

namespace fw {
enum SoundCategory : int;

void *SoundSsdDriver::SoundAllocator::AllocInstance(size_t size) { return unknown08->allocate(size, 16); }

void SoundSsdDriver::SoundAllocator::FreeInstance(void *pointer) {
  if (pointer != nullptr) {
    unknown08->deallocate(pointer);
  }
}

void *SoundSsdDriver::SoundAllocator::AllocBuffer(size_t size, size_t alignment) { return unknown08->allocate(size, alignment); }

void SoundSsdDriver::SoundAllocator::FreeBuffer(void *pointer) {
  if (pointer != nullptr) {
    unknown08->deallocate(pointer);
  }
}

void *SoundSsdDriver::SoundAllocator::AllocStream(size_t size, size_t alignment) { return unknown08->allocate(size, alignment); }

void SoundSsdDriver::SoundAllocator::FreeStream(void *pointer) {
  if (pointer != nullptr) {
    unknown08->deallocate(pointer);
  }
}

int SoundReferenceObject::release() {
  // __LINE__ of the game: it is the line argument of the assert.
#line 274
  MM_ASSERT(m_RefCount > 0);
  int count = --m_RefCount;
  if (count == 0) {
    this->~SoundReferenceObject();
    mtl::MemManager::deallocate(this, 0, false);
  }

  return count;
}

void SoundSsdBank::addEntry(ssd::SoundEntry *entry) {
  if (entry != nullptr) {
    unknown10.AddSoundEntry(entry);
  }
}

void SoundSsdBank::addSource(SoundSsdSource *source) {
  source->addRef();
  unknown270.push_back(source);
}

SoundSsdBank *SoundSsdDriver::findBank(u32 id) {
  for (mm::mtl::List<SoundSsdBank *>::iterator it = unknown838.begin(); it != unknown838.end(); ++it) {
    if ((*it)->unknown25c == id) {
      return *it;
    }
  }

  return nullptr;
}

void SoundSsdBank::removeEntry(ssd::SoundEntry *entry) {
  if (entry != nullptr) {
    unknown10.RemoveSoundEntry(entry);
  }
}

bool SoundSsdSource::isLoop() const {
  if (unknown10 != nullptr) {
    return unknown10->isLoop;
  }

  return false;
}

int SoundSsdSource::getSourceRefCount() const {
  if (unknown10 != nullptr) {
    return unknown10->refCount;
  }

  return 0;
}

bool SoundSsdPlayer::getTotalTime(f32 &time) const {
  time = 0.0f;
  if ((unknownc4 & FLAG_STREAM) != 0 && isValid()) {
    return unknown88->GetDataTime(&time) >= 0;
  }

  return false;
}

bool SoundSsdPlayer::isValid() const { return unknown88 != nullptr && unknown88->IsValidHandle(); }

bool SoundSsdPlayer::setPlayTime(f32 time) {
  if ((unknownc4 & FLAG_STREAM) != 0 && isValid()) {
    return unknown88->SetPlayTime(time) >= 0;
  }

  return false;
}

bool SoundSsdPlayer::getPlayTime(f32 &time) const {
  time = 0.0f;
  if ((unknownc4 & FLAG_STREAM) != 0 && isValid()) {
    return unknown88->GetPlayTime(&time) >= 0;
  }

  return false;
}

bool SoundSsdPlayer::is3DSource() const {
  if (isValid()) {
    return (unknown80->unknown240 & SoundSsdSource::FLAG_3D) != 0;
  }

  return false;
}

bool SoundSsdPlayer::is3D() const {
  if (!isValid()) {
    return false;
  }

  bool isSource3D = is3DSource();
  bool hasListener = (unknownc4 & FLAG_LISTENER) != 0;
  return isSource3D && hasListener;
}

bool SoundSsdPlayer::isLoop() const {
  if (isValid()) {
    SoundSsdSourceData *data = unknown80->unknown10;
    if (data != nullptr) {
      return data->isLoop;
    }
  }

  return false;
}

bool SoundSsdPlayer::setRemainLoopCount(int count) {
  if ((unknownc4 & FLAG_STREAM) != 0 && isValid()) {
    return unknown88->SetRemainLoopCount(count) >= 0;
  }

  return false;
}

bool SoundSsdPlayer::getRemainLoopCount(int &count) const {
  count = 0;
  if ((unknownc4 & FLAG_STREAM) != 0 && isValid()) {
    return unknown88->GetRemainLoopCount(&count) >= 0;
  }

  return false;
}

void SoundSsdPlayer::pause(bool isPause, f32 time) {
  if (!isValid()) {
    return;
  }

  if (isPause) {
    if (unknownc8 == 0) {
      unknown88->Pause(true, time);
    }

    unknownc8++;
  } else if (unknownc8 > 0) {
    unknownc8--;
    if (unknownc8 == 0) {
      unknown88->Pause(false, time);
    }
  }
}

bool SoundSsdPlayer::isPause() const { return unknownc8 > 0; }

void SoundSsdPlayer::setCategory(SoundCategory category) {
  this->unknown98 = category;
  if (isValid()) {
    unknown88->SetCategoryId(this->unknown98);
  }
}

void SoundSsdPlayer::setListener(ssd::SoundListener *listener) {
  if (listener != nullptr && unknown88 != nullptr && !is3DSource()) {
    return;
  }

  if (listener != nullptr) {
    unknownc4 |= FLAG_LISTENER;
  } else {
    unknownc4 &= ~FLAG_LISTENER;
  }

  this->unknown90 = listener;
  SetListener(listener);
}

bool SoundSsdPlayer::play() {
  long result = ssd::SoundActor3D::Play(unknown88, unknown80->unknown18, unknown9c, 0.0f);
  if (isValid()) {
    unknown88->SetCategoryId(unknown98);
  }

  return result >= 0;
}

bool SoundSsdPlayer::prepare() {
  if (unknown80->unknown18 == nullptr) {
    return false;
  }

  long result = unknown88->Prepare(unknown80->unknown18);
  unknown88->SetCategoryId(unknown98);
  return result >= 0;
}

bool SoundSsdPlayer::start() {
  if (unknown88->GetState() == 8) {
    return unknown88->Start(this, unknown9c, unknowna0) >= 0;
  }

  return false;
}

void SoundSsdPlayer::setVolume(f32 volume, f32 time) {
  if (isValid()) {
    this->unknown9c = volume;
    unknown88->SetCategoryId(unknown98);
    unknown88->SetVolume(volume, time);
  }
}

f32 SoundSsdPlayer::getVolume(SoundVolumeType type) const {
  f32 result = 0.0f;
  if (isValid()) {
    switch (type) {
    case SOUND_VOLUME_TYPE_HANDLE:
      result = unknown88->volume;
      break;
    case SOUND_VOLUME_TYPE_DISTANCE:
      result = unknown88->GetDistanceVolume();
      break;
    case SOUND_VOLUME_TYPE_CATEGORY:
      result = unknown88->categoryVolume;
      break;
    }
  }

  return result;
}

void SoundSsdPlayer::setPitch(f32 pitch, f32 time) {
  if (isValid()) {
    this->unknowna4 = pitch;
    unknown88->SetPitch(pitch, time);
  }
}

void SoundSsdPlayer::setPan(f32 pan, f32 time) {
  if (isValid()) {
    this->unknowna8 = pan;
    unknown88->SetPan(pan, time);
  }
}

void SoundSsdPlayer::setPos(const mm::Vec3 &position) {
  ssd::Vec3 actorPosition(position.x, position.y, position.z);
  SetPosition(actorPosition);
}

void SoundSsdPlayer::setPos(f32 x, f32 y, f32 z) {
  ssd::Vec3 actorPosition(x, y, z);
  SetPosition(actorPosition);
}

void SoundSsdPlayer::getPos(mm::Vec3 &position) const {
  position.x = this->position.x;
  position.y = this->position.y;
  position.z = this->position.z;
}

int SoundSsdPlayer::getState() const {
  if (unknown88 != nullptr) {
    return unknown88->GetState();
  }

  return -1;
}

bool SoundSsdPlayer::isReady() const { return unknown88 != nullptr && unknown88->GetState() == 8; }

bool SoundSsdPlayer::isPreparing() const {
  if (unknown88 == nullptr) {
    return false;
  }

  int state = unknown88->GetState();
  return state == 6 || state == 7 || state == 5;
}

bool SoundSsdPlayer::isPlaying() const { return unknown88 != nullptr && unknown88->IsPlay(); }

void SoundSsdPlayer::progress(f32 deltaTime) {}

bool SoundSsdPlayer::canDestroy() const {
  if ((unknownc4 & FLAG_RELEASED) != 0) {
    return true;
  }

  if (unknown88 == nullptr) {
    return false;
  }

  int state = unknown88->GetState();
  return state == 0 || state == 4;
}

void SoundSsdPlayer::setHandle(u32 handle) { m_handle = handle; }

void SoundSsdPlayer::stop(f32 time) {
  if (isValid()) {
    unknown9c = 0.0f;
    unknownc8 = 0;
    unknown88->Stop(time);
    Stop(time);
  }
}

void SoundSsdBank::setMaxSound(int maxSound) {
  unknown130.id = unknown25c;
  unknown130.maxSound = maxSound;
  this->unknown260 = maxSound;
}

bool SoundSsdBank::canRelease() const {
  if (unknown10.GetReferenceCounter() != 0) {
    return false;
  }

  return unknown10.NumSoundEntry() == 0;
}

void SoundSsdBank::stopAll() { unknown10.Stop(0.0f); }

} // namespace fw
