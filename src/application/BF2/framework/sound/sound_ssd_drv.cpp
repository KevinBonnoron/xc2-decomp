#include "framework/sound/sound_ssd_drv.h"
#include "mm_mtl/map.h" // IWYU pragma: keep

#include <math.h>
#include <string.h>

#include "framework/sound/sound_driver.h"
#include "framework/sound/sound_pack.h"
#include "ml/critical_section.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/hash.h"
#include "mtl/mem_manager.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_sound_listener.h"

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

unknown126 *SoundSsdDriver::findCategory(SoundCategory category) {
  unknown126 *found = &unknowne8[static_cast<u32>(category)];
  if (found->unknown08 != static_cast<u32>(category)) {
    found = &unknowne8[CATEGORY_COUNT];
  }

  return found;
}

const unknown126 *SoundSsdDriver::findCategory(SoundCategory category) const {
  const unknown126 *found = &unknowne8[static_cast<u32>(category)];
  if (found->unknown08 != static_cast<u32>(category)) {
    found = &unknowne8[CATEGORY_COUNT];
  }

  return found;
}

void SoundSsdDriver::removeCategory(SoundCategory category) {
  unknown126 *found = findCategory(category);
  if (found != &unknowne8[CATEGORY_COUNT]) {
    unknown126 &data = unknowne8[static_cast<u32>(category)];
    data.unknown08 = 0;
    data.unknown0c = 1.0f;
    data.unknown48 = 0;
    unknown10->ResetCategory(category);
  }
}

u32 SoundSsdDriver::registPlayer(SoundSsdPlayer *player, SoundType type) { return unknown8b8.regist(player) | (static_cast<u32>(type) << 24); }

f32 SoundSsdDriver::getCategoryVolume(SoundCategory category) const {
  f32 volume = 0.0f;
  if (unknown10 != nullptr) {
    const unknown126 *found = findCategory(category);
    if (found != &unknowne8[CATEGORY_COUNT]) {
      volume = found->unknown14;
    }
  }

  return volume;
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

mm::mtl::List<SoundSsdSource *>::iterator SoundSsdBank::findSource(const char *name) {
  for (mm::mtl::List<SoundSsdSource *>::iterator it = unknown270.begin(); it != unknown270.end(); ++it) {
    if (strcmp((*it)->unknown134.c_str(), name) == 0) {
      return it;
    }
  }

  return unknown270.end();
}

void SoundSsdBank::update() {
  for (mm::mtl::List<SoundSsdSource *>::iterator it = unknown270.begin(); it != unknown270.end();) {
    SoundSsdSource *source = *it;
    if (source->m_RefCount == 1 && source->getSourceRefCount() == 0) {
      it = unknown270.erase(it);
      source->release();
    } else {
      ++it;
    }
  }
}

void SoundSsdDriver::updateBank() {
  ml::CS lock(unknown70);
  for (mm::mtl::List<SoundSsdBank *>::iterator it = unknown838.begin(); it != unknown838.end();) {
    SoundSsdBank *bank = *it;
    bank->update();
    if (bank->m_RefCount == 1 && bank->unknown10.GetReferenceCounter() == 0 && bank->unknown10.NumSoundEntry() == 0) {
      it = unknown838.erase(it);
      if (bank != nullptr) {
        bank->release();
      }
    } else {
      ++it;
    }
  }
}

SoundSsdBank *SoundSsdDriver::findBank(u32 id) {
  for (mm::mtl::List<SoundSsdBank *>::iterator it = unknown838.begin(); it != unknown838.end(); ++it) {
    if ((*it)->unknown25c == id) {
      return *it;
    }
  }

  return nullptr;
}

SoundSsdBank *SoundSsdDriver::findBank(const char *name) {
  u32 hash = mm::mtl::hashStrCrc(name);
  for (mm::mtl::List<SoundSsdBank *>::iterator it = unknown838.begin(); it != unknown838.end(); ++it) {
    SoundSsdBank *bank = *it;
    if (bank->unknown258 == hash && strcmp(bank->unknown154.c_str(), name) == 0) {
      return bank;
    }
  }

  return nullptr;
}

SoundSsdBank *SoundSsdDriver::findBank(const char *name) const {
  u32 hash = mm::mtl::hashStrCrc(name);
  for (mm::mtl::List<SoundSsdBank *>::const_iterator it = unknown838.begin(); it != unknown838.end(); ++it) {
    SoundSsdBank *bank = *it;
    if (bank->unknown258 == hash && strcmp(bank->unknown154.c_str(), name) == 0) {
      return bank;
    }
  }

  return nullptr;
}

SoundSsdBank *SoundSsdDriver::findBank(u32 id) const {
  for (mm::mtl::List<SoundSsdBank *>::const_iterator it = unknown838.begin(); it != unknown838.end(); ++it) {
    if ((*it)->unknown25c == id) {
      return *it;
    }
  }

  return nullptr;
}

SoundSsdPlayer *SoundSsdDriver::getPlayer(u32 id) {
  if (!unknown8b8.isValid(id)) {
    return nullptr;
  }

  return static_cast<SoundSsdPlayer *>(unknown8b8.getPtr(id));
}

SoundSsdPlayer *SoundSsdDriver::getPlayer(u32 id) const {
  if (!unknown8b8.isValid(id)) {
    return nullptr;
  }

  return static_cast<SoundSsdPlayer *>(unknown8b8.getPtr(id));
}

u32 SoundSsdBank::getActivityRatio() const {
  int count = unknown10.NumSoundEntry();
  return static_cast<u32>(count * 100) / static_cast<u32>(unknown260);
}

void SoundSsdBank::removeEntry(ssd::SoundEntry *entry) {
  if (entry != nullptr) {
    unknown10.RemoveSoundEntry(entry);
  }
}

void SoundSsdDriver::applyCategoryVolume(SoundCategory category, f32 volume) {}

bool SoundSsdDriver::isValid() const { return unknown10 != nullptr; }

const mm::Mat44 &SoundSsdDriver::getListeningPoint() const { return unknown30; }

SoundPoolMemory *SoundSsdDriver::findPoolMemory(void *pointer, u32 size) const {
  for (mm::mtl::FixedList<SoundPoolMemory *, 256>::const_iterator it = unknown8f0.begin(); it != unknown8f0.end(); ++it) {
    SoundPoolMemory *memory = *it;
    if (memory->unknown00 == pointer && memory->unknown10 == size) {
      return memory;
    }
  }

  return nullptr;
}

void SoundSsdDriver::setListeningPoint(const mm::Mat44 &matrix) {
  if (unknown10 != nullptr && unknown28 != nullptr) {
    unknown28->SetPosition(ssd::Vec3(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]));
    mm::Vec3 forward(matrix.rows[0][0] * 0.0f + matrix.rows[1][0] * 0.0f - matrix.rows[2][0],
                     matrix.rows[0][1] * 0.0f + matrix.rows[1][1] * 0.0f - matrix.rows[2][1],
                     matrix.rows[0][2] * 0.0f + matrix.rows[1][2] * 0.0f - matrix.rows[2][2]);
    f32 length = sqrtf(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z);
    if (length <= 0.000001f) {
      forward = mm::Vec3::zero;
    } else {
      f32 scale = 1.0f / length;
      forward.x = forward.x * scale;
      forward.y = forward.y * scale;
      forward.z = scale * forward.z;
    }
    unknown28->SetOrientation(ssd::Vec3(forward.x, forward.y, forward.z), ssd::Vec3(0.0f, 1.0f, 0.0f));
    unknown30 = matrix;
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
    unknown127 *data = unknown80->unknown10;
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
      result = unknown88->unknown84;
      break;
    case SOUND_VOLUME_TYPE_DISTANCE:
      result = unknown88->GetDistanceVolume();
      break;
    case SOUND_VOLUME_TYPE_CATEGORY:
      result = unknown88->unknownb8;
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
  position.x = this->unknown44.x;
  position.y = this->unknown44.y;
  position.z = this->unknown44.z;
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

bool SoundSsdDriver::isValid(u32 handle) const {
  ml::CS lock(unknown70);
  return unknown8b8.isValid(handle);
}

bool SoundSsdDriver::isPlaying(u32 handle) const {
  ml::CS lock(unknown70);
  const SoundSsdPlayer *player = getPlayer(handle);
  return player != nullptr && player->isPlaying();
}

bool SoundSsdDriver::isReady(u32 handle) const {
  ml::CS lock(unknown70);
  const SoundSsdPlayer *player = getPlayer(handle);
  return player != nullptr && player->isReady();
}

bool SoundSsdDriver::isPreparing(u32 handle) const {
  ml::CS lock(unknown70);
  const SoundSsdPlayer *player = getPlayer(handle);
  return player != nullptr && player->isPreparing();
}

bool SoundSsdDriver::isPause(u32 handle) const {
  ml::CS lock(unknown70);
  const SoundSsdPlayer *player = getPlayer(handle);
  return player != nullptr && player->isPause();
}

bool SoundSsdDriver::isLoop(u32 handle) {
  unknown001 access(*this, handle);
  return access.unknown08 != nullptr && access.unknown08->isLoop();
}

void SoundSsdDriver::setCategory(u32 handle, SoundCategory category) {
  unknown001 access(*this, handle);
  if (access.unknown08 != nullptr) {
    access.unknown08->setCategory(category);
  }
}

SoundCategory SoundSsdDriver::getCategory(u32 handle) {
  unknown001 access(*this, handle);
  SoundCategory category = static_cast<SoundCategory>(0);
  if (access.unknown08 != nullptr) {
    category = access.unknown08->unknown98;
  }

  return category;
}

void SoundSsdDriver::setVolume(u32 handle, f32 volume, f32 time) {
  unknown001 access(*this, handle);
  if (access.unknown08 != nullptr) {
    access.unknown08->setVolume(volume, time);
  }
}

f32 SoundSsdDriver::getVolume(u32 handle, SoundVolumeType type) {
  unknown001 access(*this, handle);
  f32 volume = 0.0f;
  if (access.unknown08 != nullptr) {
    volume = access.unknown08->getVolume(type);
  }

  return volume;
}

void SoundSsdDriver::setPitch(u32 handle, f32 pitch, f32 time) {
  unknown001 access(*this, handle);
  if (access.unknown08 != nullptr) {
    access.unknown08->setPitch(mm::clamp(pitch, 0.0f, 8.0f), time);
  }
}

void SoundSsdDriver::setPan(u32 handle, f32 pan, f32 time) {
  unknown001 access(*this, handle);
  if (access.unknown08 != nullptr) {
    access.unknown08->setPan(mm::clamp(pan, -1.0f, 1.0f), time);
  }
}

void SoundSsdDriver::setPos(u32 handle, const mm::Vec3 &position) {
  unknown001 access(*this, handle);
  if (access.unknown08 != nullptr && access.unknown08->is3DSource()) {
    access.unknown08->setListener(unknown28);
    access.unknown08->setPos(position);
  }
}

bool SoundSsdDriver::setPlayTime(u32 handle, f32 time) {
  unknown001 access(*this, handle);
  return access.unknown08 != nullptr && access.unknown08->setPlayTime(time);
}

bool SoundSsdDriver::getPlayTime(u32 handle, f32 &time) {
  ml::CS lock(unknown70);
  time = 0.0f;
  SoundSsdPlayer *player = unknown8b8.isValid(handle) ? getPlayer(handle) : nullptr;
  return player != nullptr && player->getPlayTime(time);
}

bool SoundSsdDriver::getTotalTime(u32 handle, f32 &time) {
  ml::CS lock(unknown70);
  time = 0.0f;
  SoundSsdPlayer *player = unknown8b8.isValid(handle) ? getPlayer(handle) : nullptr;
  return player != nullptr && player->getTotalTime(time);
}

bool SoundSsdDriver::setRemainLoopCount(u32 handle, int count) {
  unknown001 access(*this, handle);
  return access.unknown08 != nullptr && access.unknown08->setRemainLoopCount(count);
}

bool SoundSsdDriver::getRemainLoopCount(u32 handle, int &count) {
  ml::CS lock(unknown70);
  count = 0;
  SoundSsdPlayer *player = unknown8b8.isValid(handle) ? getPlayer(handle) : nullptr;
  return player != nullptr && player->getRemainLoopCount(count);
}

void SoundSsdDriver::pause(u32 handle, bool isPause, f32 time) {
  unknown001 access(*this, handle);
  if (access.unknown08 != nullptr) {
    access.unknown08->pause(isPause, time);
  }
}

bool SoundSsdDriver::startBgm(u32 handle) {
  ml::CS lock(unknown70);
  SoundSsdPlayer *player = static_cast<SoundSsdPlayer *>(unknown8b8.getPtr(handle));
  return player != nullptr && player->isReady() && player->start();
}

bool SoundSsdDriver::startVoice(u32 handle) {
  ml::CS lock(unknown70);
  SoundSsdPlayer *player = static_cast<SoundSsdPlayer *>(unknown8b8.getPtr(handle));
  return player != nullptr && player->isReady() && player->start();
}

bool SoundSsdDriver::stopSound(u32 handle, f32 time) {
  SoundSsdPlayer *player = getPlayer(handle);
  if (player == nullptr) {
    return false;
  }

  player->stop(time);
  return true;
}

void SoundSsdDriver::stopSoundAll(SoundType type, f32 time) {
  for (PtrMapIterator it = unknown8b8.begin(); it != unknown8b8.end(); ++it) {
    const SoundSsdPlayer *player = static_cast<const SoundSsdPlayer *>(*it);
    if (player != nullptr && (player->m_handle >> 24) == static_cast<u32>(type)) {
      stopSound(player->m_handle, time);
    }
  }
}

void SoundSsdDriver::pauseAll(bool isPause, f32 time) {
  ml::CS lock(unknown70);
  for (PtrMapIterator it = unknown8b8.begin(); it != unknown8b8.end(); ++it) {
    SoundSsdPlayer *player = static_cast<SoundSsdPlayer *>(*it);
    if (player != nullptr) {
      player->pause(isPause, time);
    }
  }
}

u32 SoundSsdDriver::findSe(const char *name) const {
  ml::CS lock(unknown70);
  for (PtrMapIterator it = unknown8b8.begin(); it != unknown8b8.end();) {
    const SoundSsdPlayer *player = static_cast<const SoundSsdPlayer *>(*it);
    ++it;
    if (player != nullptr && player->unknownb0 == SOUND_TYPE_SE && strcmp(player->unknown80->unknown134.c_str(), name) == 0) {
      return 1;
    }
  }

  return 0;
}

bool SoundSsdDriver::isLoop(u32 id, SoundPack *pack) {
  if (pack == nullptr) {
    return false;
  }

  ml::CS lock(unknown70);
  mm::mtl::IntrusivePtr<SoundSsdSource> source = pack->findSourceFromID(id);
  if (source.get() == nullptr) {
    return false;
  }

  return source->isLoop();
}

void SoundSsdDriver::pauseCategory(SoundCategory category, bool isPause, f32 time) {
  ml::CS lock(unknown70);
  for (PtrMapIterator it = unknown8b8.begin(); it != unknown8b8.end(); ++it) {
    SoundSsdPlayer *player = static_cast<SoundSsdPlayer *>(*it);
    if (player != nullptr && player->unknown98 == category) {
      player->pause(isPause, time);
    }
  }
}

void SoundSsdDriver::setCategoryPitch(SoundCategory category, f32 pitch, f32 time) {
  if (unknown10 != nullptr) {
    ml::CS lock(unknown70);
    for (PtrMapIterator it = unknown8b8.begin(); it != unknown8b8.end(); ++it) {
      SoundSsdPlayer *player = static_cast<SoundSsdPlayer *>(*it);
      if (player != nullptr && player->unknown98 == category && player->isValid()) {
        player->unknowna4 = pitch;
        player->unknown88->SetPitch(pitch, time);
      }
    }

    unknown126 *found = findCategory(category);
    if (found != &unknowne8[CATEGORY_COUNT]) {
      found->unknown44 = pitch;
    }
  }
}

void SoundSsdDriver::updateDebugInfoLocal(mm::mtl::FixedVector<SoundHandleDebugInfo, 128> &handles) {}

void SoundSsdDriver::updateDebugInfoLocal(mm::mtl::FixedVector<SoundCategoryDebugInfo, 18> &categories) {}

void SoundSsdDriver::updateDebugInfo(mm::mtl::FixedVector<SoundHandleDebugInfo, 128> &handles, mm::mtl::FixedVector<SoundCategoryDebugInfo, 18> &categories) {}

void SoundSsdDriver::stopBgmAll() {
  ml::CS lock(unknown70);
  stopSoundAll(SOUND_TYPE_BGM, 0.0f);
}

void SoundSsdDriver::stopVoiceAll() {
  ml::CS lock(unknown70);
  stopSoundAll(SOUND_TYPE_VOICE, 0.0f);
}

void SoundSsdDriver::stopSeAll() {
  ml::CS lock(unknown70);
  stopSoundAll(SOUND_TYPE_SE, 0.0f);
}

void SoundSsdDriver::stopAll() {
  for (mm::mtl::List<SoundSsdBank *>::iterator it = unknown838.begin(); it != unknown838.end(); ++it) {
    (*it)->stopAll();
  }

  if (unknown10 != nullptr) {
    unknown10->StopSound(0.0f);
  }
}

bool SoundSsdDriver::stopBgm(u32 handle, f32 time) {
  ml::CS lock(unknown70);
  return stopSound(handle, time);
}

bool SoundSsdDriver::stopVoice(u32 handle, f32 time) {
  ml::CS lock(unknown70);
  return stopSound(handle, time);
}

bool SoundSsdDriver::stopSe(u32 handle, f32 time) {
  ml::CS lock(unknown70);
  return stopSound(handle, time);
}

void SoundSsdBank::setMaxSound(int maxSound) {
  unknown130.unknown18 = unknown25c;
  unknown130.unknown1c = maxSound;
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

template mm::mtl::FixedList<fw::SoundPoolMemory *, 256>::iterator mm::mtl::FixedList<fw::SoundPoolMemory *, 256>::erase(mm::mtl::FixedList<fw::SoundPoolMemory *, 256>::iterator);

template mm::mtl::PtrSingleton<fw::SoundSsdDriver>::~PtrSingleton();

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<ssd::SoundHandle *, fw::SoundSsdPlayer *>::MapTraits<ssd::SoundHandle *, fw::SoundSsdPlayer *>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<ssd::SoundHandle *, fw::SoundSsdPlayer *> &);
template void unknown101::rebalance(unknown101::node *);
