#include "framework/sound/sound_ssd_drv.h"

#include "framework/sound/sound_driver.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/allocator.h"

namespace ssd {
class SoundListener;
} // namespace ssd

namespace fw {
enum SoundCategory : int;

void *SoundSsdDriver::SoundAllocator::AllocInstance(size_t size) { return allocator->allocate(size, 16); }

void SoundSsdDriver::SoundAllocator::FreeInstance(void *pointer) {
  if (pointer != nullptr) {
    allocator->deallocate(pointer);
  }
}

void *SoundSsdDriver::SoundAllocator::AllocBuffer(size_t size, size_t alignment) { return allocator->allocate(size, alignment); }

void SoundSsdDriver::SoundAllocator::FreeBuffer(void *pointer) {
  if (pointer != nullptr) {
    allocator->deallocate(pointer);
  }
}

void *SoundSsdDriver::SoundAllocator::AllocStream(size_t size, size_t alignment) { return allocator->allocate(size, alignment); }

void SoundSsdDriver::SoundAllocator::FreeStream(void *pointer) {
  if (pointer != nullptr) {
    allocator->deallocate(pointer);
  }
}

bool SoundSsdPlayer::getTotalTime(f32 &time) const {
  time = 0.0f;
  if ((flags & FLAG_STREAM) != 0 && isValid()) {
    return handle->GetDataTime(&time) >= 0;
  }

  return false;
}

bool SoundSsdPlayer::isValid() const { return handle != nullptr && handle->IsValidHandle(); }

bool SoundSsdPlayer::setPlayTime(f32 time) {
  if ((flags & FLAG_STREAM) != 0 && isValid()) {
    return handle->SetPlayTime(time) >= 0;
  }

  return false;
}

bool SoundSsdPlayer::getPlayTime(f32 &time) const {
  time = 0.0f;
  if ((flags & FLAG_STREAM) != 0 && isValid()) {
    return handle->GetPlayTime(&time) >= 0;
  }

  return false;
}

bool SoundSsdPlayer::is3DSource() const {
  if (isValid()) {
    return (source->flags & SoundSsdSource::FLAG_3D) != 0;
  }

  return false;
}

bool SoundSsdPlayer::is3D() const {
  if (!isValid()) {
    return false;
  }

  bool isSource3D = is3DSource();
  bool hasListener = (flags & FLAG_LISTENER) != 0;
  return isSource3D && hasListener;
}

bool SoundSsdPlayer::isLoop() const {
  if (isValid()) {
    SoundSsdSourceData *data = source->data;
    if (data != nullptr) {
      return data->isLoop;
    }
  }

  return false;
}

bool SoundSsdPlayer::setRemainLoopCount(int count) {
  if ((flags & FLAG_STREAM) != 0 && isValid()) {
    return handle->SetRemainLoopCount(count) >= 0;
  }

  return false;
}

bool SoundSsdPlayer::getRemainLoopCount(int &count) const {
  count = 0;
  if ((flags & FLAG_STREAM) != 0 && isValid()) {
    return handle->GetRemainLoopCount(&count) >= 0;
  }

  return false;
}

void SoundSsdPlayer::pause(bool isPause, f32 time) {
  if (!isValid()) {
    return;
  }

  if (isPause) {
    if (pauseCount == 0) {
      handle->Pause(true, time);
    }

    pauseCount++;
  } else if (pauseCount > 0) {
    pauseCount--;
    if (pauseCount == 0) {
      handle->Pause(false, time);
    }
  }
}

bool SoundSsdPlayer::isPause() const { return pauseCount > 0; }

void SoundSsdPlayer::setCategory(SoundCategory category) {
  this->category = category;
  if (isValid()) {
    handle->SetCategoryId(this->category);
  }
}

void SoundSsdPlayer::setListener(ssd::SoundListener *listener) {
  if (listener != nullptr && handle != nullptr && !is3DSource()) {
    return;
  }

  if (listener != nullptr) {
    flags |= FLAG_LISTENER;
  } else {
    flags &= ~FLAG_LISTENER;
  }

  this->listener = listener;
  SetListener(listener);
}

bool SoundSsdPlayer::play() {
  long result = ssd::SoundActor3D::Play(handle, source->entry, volume, 0.0f);
  if (isValid()) {
    handle->SetCategoryId(category);
  }

  return result >= 0;
}

bool SoundSsdPlayer::prepare() {
  if (source->entry == nullptr) {
    return false;
  }

  long result = handle->Prepare(source->entry);
  handle->SetCategoryId(category);
  return result >= 0;
}

bool SoundSsdPlayer::start() {
  if (handle->GetState() == 8) {
    return handle->Start(this, volume, fadeTime) >= 0;
  }

  return false;
}

void SoundSsdPlayer::setVolume(f32 volume, f32 time) {
  if (isValid()) {
    this->volume = volume;
    handle->SetCategoryId(category);
    handle->SetVolume(volume, time);
  }
}

f32 SoundSsdPlayer::getVolume(SoundVolumeType type) const {
  f32 result = 0.0f;
  if (isValid()) {
    switch (type) {
    case SOUND_VOLUME_TYPE_HANDLE:
      result = handle->volume;
      break;
    case SOUND_VOLUME_TYPE_DISTANCE:
      result = handle->GetDistanceVolume();
      break;
    case SOUND_VOLUME_TYPE_CATEGORY:
      result = handle->categoryVolume;
      break;
    }
  }

  return result;
}

void SoundSsdPlayer::setPitch(f32 pitch, f32 time) {
  if (isValid()) {
    this->pitch = pitch;
    handle->SetPitch(pitch, time);
  }
}

void SoundSsdPlayer::setPan(f32 pan, f32 time) {
  if (isValid()) {
    this->pan = pan;
    handle->SetPan(pan, time);
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
  if (handle != nullptr) {
    return handle->GetState();
  }

  return -1;
}

bool SoundSsdPlayer::isReady() const { return handle != nullptr && handle->GetState() == 8; }

bool SoundSsdPlayer::isPreparing() const {
  if (handle == nullptr) {
    return false;
  }

  int state = handle->GetState();
  return state == 6 || state == 7 || state == 5;
}

bool SoundSsdPlayer::isPlaying() const { return handle != nullptr && handle->IsPlay(); }

void SoundSsdPlayer::progress(f32 deltaTime) {}

bool SoundSsdPlayer::canDestroy() const {
  if ((flags & FLAG_RELEASED) != 0) {
    return true;
  }

  if (handle == nullptr) {
    return false;
  }

  int state = handle->GetState();
  return state == 0 || state == 4;
}

void SoundSsdPlayer::setHandle(u32 handle) { fwHandle = handle; }

void SoundSsdPlayer::stop(f32 time) {
  if (isValid()) {
    volume = 0.0f;
    pauseCount = 0;
    handle->Stop(time);
    Stop(time);
  }
}

} // namespace fw
