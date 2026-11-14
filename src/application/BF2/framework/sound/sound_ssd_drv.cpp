#include "framework/sound/sound_ssd_drv.h"
#include "mm_mtl/map.h" // IWYU pragma: keep

#include <math.h>
#include <string.h>

#include "csvb/csvb_data.h"
#include "framework/memory/framework_memory.h"
#include "framework/sound/sound_driver.h"
#include "framework/sound/sound_pack.h"
#include "ml/critical_section.h"
#include "ml/micro_thread.h"
#include "ml/path_util.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/hash.h"
#include "mm_mtl/internal/object_allocator.h"
#include "mm_mtl/str_util.h" // IWYU pragma: keep
#include "mtl/mem_manager.h"
#include "nn/diag.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_sound_listener.h"
#include "ssd/ssd_text.h"
#include "ssd/ssd_wave_source.h"

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
  if (found->unknown00.unknown08.unknown00 != static_cast<int>(category)) {
    found = &unknowne8[CATEGORY_UNKNOWN_18];
  }

  return found;
}

const unknown126 *SoundSsdDriver::findCategory(SoundCategory category) const {
  const unknown126 *found = &unknowne8[static_cast<u32>(category)];
  if (found->unknown00.unknown08.unknown00 != static_cast<int>(category)) {
    found = &unknowne8[CATEGORY_UNKNOWN_18];
  }

  return found;
}

void SoundSsdDriver::addCategory(SoundCategory category, f32 volume, const char *name) {
  unknown126 &data = unknowne8[static_cast<u32>(category)];
  data.unknown10 = volume;
  data.unknown48 = 1;
  data.unknown4c = name;
  data.unknown40 = 0;
  data.unknown00.unknown08.unknown00 = category;
  data.unknown44 = 1.0f;
  data.unknown00.unknown08.unknown04 = volume;
  unknown10->SetCategory(data.unknown00);
}

void SoundSsdDriver::removeCategory(SoundCategory category) {
  unknown126 *found = findCategory(category);
  if (found != &unknowne8[CATEGORY_UNKNOWN_18]) {
    unknown126 &data = unknowne8[static_cast<u32>(category)];
    data.unknown00.unknown08.unknown00 = 0;
    data.unknown00.unknown08.unknown04 = 1.0f;
    data.unknown48 = 0;
    unknown10->ResetCategory(category);
  }
}

u32 SoundSsdDriver::registPlayer(SoundSsdPlayer *player, SoundType type) { return unknown8b8.regist(player) | (static_cast<u32>(type) << 24); }

f32 SoundSsdDriver::getCategoryVolume(SoundCategory category) const {
  f32 volume = 0.0f;
  if (unknown10 != nullptr) {
    const unknown126 *found = findCategory(category);
    if (found != &unknowne8[CATEGORY_UNKNOWN_18]) {
      volume = found->unknown14.unknown00;
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

SoundSsdSource *SoundSsdSource::createWave(const SetupWaveInfo &info) {
  // __LINE__ must be 487, 493 and 503 as in the original file: they are the line arguments of operator new.
#line 487
  SoundSsdSource *source = new (FrameworkMemory::getAllocator(5), 8, __FILE__, __LINE__) SoundSsdSource(info);
  if (source != nullptr) {
    source->unknown23c = info.unknown00.unknown48;
#line 493
    source->unknown10 = new (FrameworkMemory::getAllocator(5), 8, __FILE__, __LINE__) ssd::WaveSource;
    source->unknown10->Init(info.unknownb0, info.unknownb8);
#line 503
    ssd::SoundEntry *entry = new (FrameworkMemory::getAllocator(5), 8, __FILE__, __LINE__) ssd::SoundEntry;
    source->unknown18 = entry;
    entry->unknownc8 = source->unknown10;
    entry->unknown30 = info.unknown00;
    source->unknown20->addEntry(source->unknown18);
    source->unknown20->addSource(source);
    if (info.unknown00.unknown68.unknown01) {
      source->unknown240 |= FLAG_UNKNOWN_1;
    }
  }

  return source;
}

SoundSsdSource::SoundSsdSource(const SetupInfo &info)
    : unknown10(nullptr), unknown18(nullptr), unknown28(info.unknown9c), unknown2c(info.unknowna0), unknown238(0), unknown23c(0), unknown240(0), unknown244(6) {
  unknown130 = mm::mtl::hashStrCrc(unknown2c.c_str());
  unknown134 = ml::PathUtil::getFilePtrFromPath(info.unknowna0);
  unknown238 = mm::mtl::hashStrCrc(unknown134.c_str());
  unknown20 = SoundSsdDriver::get()->findBank(unknown28);
}

SoundSsdSource::SoundSsdSource(const SetupWaveInfo &info)
    : unknown10(nullptr), unknown18(nullptr), unknown28(info.unknown9c), unknown2c(info.unknowna0), unknown238(0), unknown23c(0), unknown240(0), unknown244(6) {
  unknown130 = mm::mtl::hashStrCrc(unknown2c.c_str());
  const char *name = info.unknowna8;
  if (name != nullptr && name[0] != '\0') {
    unknown134 = name;
    unknown238 = mm::mtl::hashStrCrc(unknown134.c_str());
  }

  unknown20 = SoundSsdDriver::get()->findBank(unknown28);
}

mm::mtl::List<SoundSsdSource *>::iterator SoundSsdBank::findSource(const char *name) {
  for (mm::mtl::List<SoundSsdSource *>::iterator it = unknown270.begin(); it != unknown270.end(); ++it) {
    if (strcmp((*it)->unknown134.c_str(), name) == 0) {
      return it;
    }
  }

  return unknown270.end();
}

mm::mtl::IntrusivePtr<SoundSsdSource> SoundSsdBank::addWave(const WaveInfo &info) {
  mm::mtl::List<SoundSsdSource *>::iterator it = findSource(info.unknown08);
  if (it != unknown270.end()) {
    return *it;
  }

  SoundSsdSource::SetupWaveInfo setup;
  setup.unknown98 = info.unknown1c;
  setup.unknown9c = unknown25c;
  setup.unknowna0 = info.unknown00;
  setup.unknowna8 = info.unknown08;
  setup.unknownb0 = info.unknown10;
  setup.unknownb8 = info.unknown18;
  ssd::SoundParam &param = setup.unknown00;
  param.Init();
  param.unknown4c.unknown01 = unknown130.unknown18;
  param.unknown4c.unknown02 = info.unknown1c;
  param.unknown4c.unknown18 = static_cast<f32>(info.unknown20);
  param.unknown48 = SoundManager::getUniqueID(info.unknown1c);
  param.unknown00 = ssd::TextRef(info.unknown08);
  if (info.unknown44 != 0) {
    param.unknown4c.unknown0c = 0.0f;
  }

  if (info.unknown38 != 0) {
    param.unknown4c.unknown04 = static_cast<f32>(info.unknown38) * 0.01f;
  }

  if (info.unknown3c != 0) {
    param.unknown4c.unknown08 = static_cast<f32>(info.unknown3c) * 0.01f;
  }

  if (info.unknown40 > 0.000001f) {
    param.unknown4c.unknown10 = info.unknown40;
  }

  if (info.unknown24) {
    param.unknown68.unknown01 = true;
    param.unknown68.unknown02 = true;
    param.unknown68.unknown03 = false;
    param.unknown68.unknown06 = false;
  } else {
    param.unknown68.unknown01 = false;
    param.unknown68.unknown02 = false;
    param.unknown4c.unknown0c = info.unknown2c;
    if (param.unknown4c.unknown0c == 0.0f) {
      param.unknown4c.unknown0c = 1.0f;
    }
  }

  param.unknown68.unknown07 = info.unknown44 != 0;
  param.unknown70.unknown00 = info.unknown28;
  param.unknown70.unknown04 = info.unknown2c;
  param.unknown70.unknown08 = info.unknown30;
  param.unknown70.unknown0c = info.unknown34;
  return SoundSsdSource::createWave(setup);
}

mm::mtl::IntrusivePtr<SoundSsdSource> SoundSsdBank::addStream(const char *name, SoundCategory category, SoundPriority priority) {
  mm::mtl::List<SoundSsdSource *>::iterator it = findSource(name);
  if (it != unknown270.end()) {
    return *it;
  }

  SoundSsdSource::SetupInfo setup;
  setup.unknown98 = category;
  setup.unknown9c = unknown25c;
  setup.unknowna0 = name;
  ssd::SoundParam &param = setup.unknown00;
  param.Init();
  param.unknown4c.unknown00 = true;
  param.unknown4c.unknown02 = category;
  param.unknown4c.unknown18 = static_cast<f32>(priority);
  param.unknown48 = SoundManager::getUniqueID(category);
  param.unknown4c.unknown01 = unknown130.unknown18;
  param.unknown4c.unknown0c = SoundSsdDriver::get()->getBgmVolume(name);
  return SoundSsdSource::createStream(setup);
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

void SoundSsdBank::removeSource(SoundSsdSource *source) {
  mm::mtl::List<SoundSsdSource *>::iterator end = unknown270.end();
  for (mm::mtl::List<SoundSsdSource *>::iterator it = unknown270.begin(); it != end;) {
    mm::mtl::List<SoundSsdSource *>::iterator cur = it;
    ++it;
    if (*cur == source) {
      unknown270.erase(cur);
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

SoundSsdDriver::~SoundSsdDriver() {
  finalize();
  if (unknown1b70 != nullptr) {
    delete unknown1b70;
    unknown1b70 = nullptr;
  }
}

bool SoundSsdDriver::isDeviceEnable() const {
  if (unknown10 != nullptr) {
    return !unknown10->unknown11;
  }

  return false;
}

const mm::Mat44 &SoundSsdDriver::getListeningPoint() const { return m_listeningPoint; }

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
    m_listeningPoint = matrix;
  }
}

u32 SoundSsdDriver::playBgm(const char *name, f32 volume, bool ignorePause, int loopCount, SoundCategory category) {
  ml::CS lock(unknown70);
  return playStream(name, volume, ignorePause, category, SOUND_PRIORITY_UNKNOWN_255, findBank("SystemBgmBank"), SOUND_TYPE_UNKNOWN_1);
}

u32 SoundSsdDriver::playVoice(const char *name, f32 volume, bool ignorePause, SoundCategory category) {
  ml::CS lock(unknown70);
  return playStream(name, volume, ignorePause, category, SOUND_PRIORITY_UNKNOWN_254, findBank("SystemVoiceBank"), SOUND_TYPE_UNKNOWN_2);
}

void SoundSsdDriver::removeBank(const char *name) {
  u32 hash = mm::mtl::hashStrCrc(name);
  for (mm::mtl::List<SoundSsdBank *>::iterator it = unknown838.begin(); it != unknown838.end(); ++it) {
    SoundSsdBank *bank = *it;
    if (bank->unknown258 == hash && strcmp(bank->unknown154.c_str(), name) == 0) {
      unknown838.erase(it);
      if (bank != nullptr) {
        bank->release();
      }

      return;
    }
  }
}

// Inferred role: typed call of GetPlatformDataImpl; the game loads the name before the virtual call, a direct call does not match; original name unknown.
static inline nn::audio::AudioRendererConfig *unknown007(ssd::SoundCore *core, const char *name) { return static_cast<nn::audio::AudioRendererConfig *>(core->GetPlatformDataImpl(name)); }

inline nn::audio::AudioRendererConfig *SoundSsdDriver::unknown004() {
  nn::audio::AudioRendererConfig *config = nullptr;
  if (get() != nullptr) {
    ssd::SoundCore *core = get()->unknown10;
    if (core != nullptr) {
      config = unknown007(core, ssd::SoundCore::audioRendererConfigName_);
    }
  }

  return config;
}

void SoundSsdDriver::attachPoolMemory(void *memory, u32 size) {
  ml::CS lock(unknownc0);
  if (findPoolMemory(memory, size) == nullptr) {
    // __LINE__ must be 1570 as in the original file: it is the line argument of operator new.
#line 1570
    SoundPoolMemory *pool = new (FrameworkMemory::getAllocator(5), 8, __FILE__, __LINE__) SoundPoolMemory(memory, size);
    NN_ABORT_UNLESS(nn::audio::AcquireMemoryPool(unknown004(), &pool->unknown08, memory, size));
    NN_ABORT_UNLESS(nn::audio::RequestAttachMemoryPool(&pool->unknown08));
    unknown8f0.push_back(pool);
  }
}

inline void SoundSsdDriver::unknown005(SoundPoolMemory *pool) {
  if (pool->unknown14 == SoundPoolMemory::STATE_UNKNOWN_1) {
    MM_VERIFY(unknown004());
    nn::audio::RequestDetachMemoryPool(&pool->unknown08);
    pool->unknown14 = SoundPoolMemory::STATE_UNKNOWN_2;
  } else if (pool->unknown00 == nullptr) {
    pool->unknown14 = SoundPoolMemory::STATE_UNKNOWN_3;
  }
}

void SoundSsdDriver::detachPoolMemory(void *memory, u32 size) {
  ml::CS lock(unknownc0);
  SoundPoolMemory *pool = findPoolMemory(memory, size);
  if (pool != nullptr) {
    unknown005(pool);
  }
}

bool SoundSsdDriver::finalize() {
  if (unknown10 == nullptr) {
    return unknown1b64 == 5;
  }

  u32 state = unknown1b64;
  switch (state) {
  case 1:
    pauseAll(false, 0.0f);
    stopAll();
    state = 2;
    unknown1b64 = state;
    break;
  case 2:
    if (unknown10->GetNumPlaySound() != 0) {
      return false;
    }

    for (mm::mtl::FixedList<SoundPoolMemory *, 256>::iterator it = unknown8f0.begin(); it != unknown8f0.end(); ++it) {
      unknown005(*it);
    }

    unknown1b64 = 3;
    unknown1b68 = 15;
    state = 3;
    break;
  case 3:
    if (--unknown1b68 > 0) {
      return false;
    }

    updatePoolMemory();
    if (unknown8f0.size() != 0) {
      return false;
    }

    unknown1b60 = false;
    destroyResourceAll();
    state = 4;
    unknown1b64 = state;
    break;
  case 4: {
    unknown1b28.destroy();
    ssd::SoundListener *listener = unknown28;
    if (listener != nullptr) {
      listener->~SoundListener();
      mtl::MemManager::deallocate(listener, 0, false);
      unknown28 = nullptr;
    }

    unknown10->Quit(false);
    ssd::SoundCore::DeleteInstance();
    unknown10 = nullptr;
    state = 5;
    unknown1b64 = state;
    break;
  }
  }

  return state == 5;
}

void SoundSsdDriver::updatePoolMemory() {
  ml::CS lock(unknownc0);
  for (mm::mtl::FixedList<SoundPoolMemory *, 256>::iterator it = unknown8f0.begin(); it != unknown8f0.end(); ++it) {
    SoundPoolMemory *pool = *it;
    if (pool->unknown14 == SoundPoolMemory::STATE_UNKNOWN_2) {
      if (nn::audio::GetMemoryPoolState(&pool->unknown08) == nn::audio::MemoryPoolState_UNKNOWN_3) {
        nn::audio::ReleaseMemoryPool(unknown004(), &pool->unknown08);
        pool->unknown006();
      }

      pool->unknown14 = SoundPoolMemory::STATE_UNKNOWN_3;
      it = unknown8f0.erase(it);
      if (pool != nullptr) {
        SsdObjectAllocator::deleteObject(pool);
      }
    }
  }
}

void SoundSsdDriver::setMasterVolume(f32 volume) {
  if (unknown10 != nullptr) {
    for (u32 i = 1; i < CATEGORY_UNKNOWN_18; i++) {
      unknowne8[i].unknown3c = volume;
      unknown10->SetCategory(unknowne8[i].unknown00);
    }
  }
}

u32 SoundSsdDriver::getSoundHandleForFw(ssd::SoundHandle *handle) {
  mm::mtl::Map<ssd::SoundHandle *, SoundSsdPlayer *>::iterator it = unknown1b10.find(handle);
  if (it != unknown1b10.end() && it->second != nullptr) {
    return it->second->m_handle;
  }

  return 0;
}

SoundSsdSource::~SoundSsdSource() {
  if (unknown20 != nullptr) {
    unknown20->removeEntry(unknown18);
  }

  ssd::SoundEntry *entry = unknown18;
  if (entry != nullptr) {
    entry->~SoundEntry();
    mtl::MemManager::deallocate(entry, 0, false);
    unknown18 = nullptr;
  }

  ssd::WaveSource *wave = unknown10;
  if (wave != nullptr) {
    wave->~WaveSource();
    mtl::MemManager::deallocate(wave, 0, false);
    unknown10 = nullptr;
  }

  unknown20->removeSource(this);
}

bool SoundSsdSource::isLoop() const {
  if (unknown10 != nullptr) {
    return unknown10->unknown50;
  }

  return false;
}

int SoundSsdSource::getSourceRefCount() const {
  if (unknown10 != nullptr) {
    return unknown10->unknown6c;
  }

  return 0;
}

bool SoundSsdPlayer::getTotalTime(f32 &time) const {
  time = 0.0f;
  if ((unknownc4 & FLAG_UNKNOWN_2) != 0 && isValid()) {
    return unknown88->GetDataTime(&time) >= 0;
  }

  return false;
}

bool SoundSsdPlayer::isValid() const { return unknown88 != nullptr && unknown88->IsValidHandle(); }

bool SoundSsdPlayer::setPlayTime(f32 time) {
  if ((unknownc4 & FLAG_UNKNOWN_2) != 0 && isValid()) {
    return unknown88->SetPlayTime(time) >= 0;
  }

  return false;
}

bool SoundSsdPlayer::getPlayTime(f32 &time) const {
  time = 0.0f;
  if ((unknownc4 & FLAG_UNKNOWN_2) != 0 && isValid()) {
    return unknown88->GetPlayTime(&time) >= 0;
  }

  return false;
}

bool SoundSsdPlayer::is3DSource() const {
  if (isValid()) {
    return (unknown80->unknown240 & SoundSsdSource::FLAG_UNKNOWN_1) != 0;
  }

  return false;
}

bool SoundSsdPlayer::is3D() const {
  if (!isValid()) {
    return false;
  }

  bool isSource3D = is3DSource();
  bool hasListener = (unknownc4 & FLAG_UNKNOWN_3) != 0;
  return isSource3D && hasListener;
}

bool SoundSsdPlayer::isLoop() const {
  if (isValid()) {
    ssd::WaveSource *source = unknown80->unknown10;
    if (source != nullptr) {
      return source->unknown50;
    }
  }

  return false;
}

bool SoundSsdPlayer::setRemainLoopCount(int count) {
  if ((unknownc4 & FLAG_UNKNOWN_2) != 0 && isValid()) {
    return unknown88->SetRemainLoopCount(count) >= 0;
  }

  return false;
}

bool SoundSsdPlayer::getRemainLoopCount(int &count) const {
  count = 0;
  if ((unknownc4 & FLAG_UNKNOWN_2) != 0 && isValid()) {
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
    unknownc4 |= FLAG_UNKNOWN_3;
  } else {
    unknownc4 &= ~FLAG_UNKNOWN_3;
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
    case SOUND_VOLUME_TYPE_UNKNOWN_0:
      result = unknown88->unknown84.unknown00;
      break;
    case SOUND_VOLUME_TYPE_UNKNOWN_1:
      result = unknown88->GetDistanceVolume();
      break;
    case SOUND_VOLUME_TYPE_UNKNOWN_2:
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
  if ((unknownc4 & FLAG_UNKNOWN_1) != 0) {
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
    if (player != nullptr && player->unknownb0 == SOUND_TYPE_UNKNOWN_3 && strcmp(player->unknown80->unknown134.c_str(), name) == 0) {
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
    if (found != &unknowne8[CATEGORY_UNKNOWN_18]) {
      found->unknown44 = pitch;
    }
  }
}

void SoundSsdDriver::updateDebugInfoLocal(mm::mtl::FixedVector<SoundHandleDebugInfo, 128> &handles) {}

void SoundSsdDriver::updateDebugInfoLocal(mm::mtl::FixedVector<SoundCategoryDebugInfo, 18> &categories) {}

void SoundSsdDriver::updateDebugInfo(mm::mtl::FixedVector<SoundHandleDebugInfo, 128> &handles, mm::mtl::FixedVector<SoundCategoryDebugInfo, 18> &categories) {}

void SoundSsdDriver::stopBgmAll() {
  ml::CS lock(unknown70);
  stopSoundAll(SOUND_TYPE_UNKNOWN_1, 0.0f);
}

void SoundSsdDriver::stopVoiceAll() {
  ml::CS lock(unknown70);
  stopSoundAll(SOUND_TYPE_UNKNOWN_2, 0.0f);
}

void SoundSsdDriver::stopSeAll() {
  ml::CS lock(unknown70);
  stopSoundAll(SOUND_TYPE_UNKNOWN_3, 0.0f);
}

void SoundSsdDriver::stopAll() {
  for (mm::mtl::List<SoundSsdBank *>::iterator it = unknown838.begin(); it != unknown838.end(); ++it) {
    (*it)->stopAll();
  }

  if (unknown10 != nullptr) {
    unknown10->StopSound(0.0f);
  }
}

void SoundSsdDriver::destroyResourceAll() {
  while (!unknown838.empty()) {
    SoundSsdBank *bank = *unknown838.begin();
    bank->destroy();
    if (bank != nullptr) {
      bank->release();
    }
    unknown838.erase(unknown838.begin());
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

SoundSsdBank *SoundSsdBank::create(const char *name, SoundCategory category, u32 maxSound) {
  SoundSsdBank *bank = SoundSsdDriver::get()->findBank(name);
  if (bank != nullptr) {
    bank->addRef();
    return bank;
  }

  SoundBankSetup setup;
  setup.unknown00 = FrameworkMemory::getAllocator(5);
  setup.unknown08 = m_bankUniqueID.unknown001();
  setup.unknown10 = name;
  setup.unknown18 = category;
  setup.unknown1c = maxSound;
  // __LINE__ must be 1118 as in the original file: it is the line argument of operator new.
#line 1118
  bank = new (FrameworkMemory::getAllocator(5), 8, __FILE__, __LINE__) SoundSsdBank(setup);
  bank->addRef();
  SoundSsdDriver::get()->registBank(name, bank);
  return bank;
}

void SoundSsdDriver::registBank(const char *name, SoundSsdBank *bank) {
  for (mm::mtl::List<SoundSsdBank *>::iterator it = unknown838.begin(); it != unknown838.end(); ++it) {
    if (*it == bank) {
      return;
    }
  }

  unknown838.push_back(bank);
  bank->addRef();
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

void SoundSsdBank::destroy() {
  u32 waitCount = 0;
  while (!unknown270.empty()) {
    SoundSsdSource *source = *unknown270.begin();
    if (source->getSourceRefCount() == 0) {
      unknown270.erase(unknown270.begin());
      source->release();
      waitCount = 0;
    } else {
      ml::MicroThread::get()->sleep(1, true);
      if (++waitCount > 90) {
        unknown270.erase(unknown270.begin());
        source->release();
        waitCount = 0;
      }
    }
  }

  while (unknown10.GetReferenceCounter() > 0 && unknown10.NumSoundEntry() != 0) {
    ml::MicroThread::get()->sleep(1, true);
  }

  unknown270.unknown001();
  unknown270.clear();
  unknown10.Quit();
}

SoundSsdBank::~SoundSsdBank() {
  // The game evaluates canRelease and traverses the sources here without using the results (1.0.0: 0x71001a4e10);
  // the code that used them is unknown, perhaps compiled out.
  canRelease();
  for (mm::mtl::List<SoundSsdSource *>::iterator it = unknown270.begin(); it != unknown270.end(); ++it) {
  }
  unknown270.unknown001();
  unknown270.clear();
  unknown10.Quit();
}

} // namespace fw

template mm::mtl::FixedList<fw::SoundPoolMemory *, 256>::iterator mm::mtl::FixedList<fw::SoundPoolMemory *, 256>::erase(mm::mtl::FixedList<fw::SoundPoolMemory *, 256>::iterator);

template mm::mtl::PtrSingleton<fw::SoundSsdDriver>::~PtrSingleton();

// Instantiated here: the game emits it next to SoundSsdDriver::playStream, its caller (1.0.0: 0x71001a86e0).
template void mm::mtl::replacestr<mm::mtl::FixStr<256>>(mm::mtl::FixStr<256> &, const char *, const char *);

// Instantiated here, where the driver keeps its sound handle allocator: the game calls the out-of-line ssd::SoundHandle constructor, which sound_handle.cpp would inline.
template ssd::SoundHandle *mm::mtl::ObjectAllocator<ssd::SoundHandle>::allocate();

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<ssd::SoundHandle *, fw::SoundSsdPlayer *>::MapTraits<ssd::SoundHandle *, fw::SoundSsdPlayer *>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<ssd::SoundHandle *, fw::SoundSsdPlayer *> &);
template void unknown101::rebalance(unknown101::node *);
template void unknown101::erase(unknown101::node *);
template void unknown101::rebalance_after_erase(unknown101::node *);
