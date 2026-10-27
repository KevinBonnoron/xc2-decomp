#include "ssd/ssd_allocator.h"
#include "ssd/ssd_array.h"
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_behavior_impl.h" // IWYU pragma: keep
#include "ssd/ssd_mutex.h"
#include "ssd/ssd_result.h"
#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_wave_source.h"
#include "types.h"

namespace ssd {

int SoundBank::GetNumber() const { return m_number; }

int SoundBank::NumSoundEntry() const { return unknowne0.count; }

SoundGroup *SoundBank::GetSoundGroup(int id) const {
  if (SoundCore::instance_ == nullptr) {
    return nullptr;
  }
  if (m_number >= 0) {
    SoundGroup **end = unknown108.unknown10 + unknown108.unknown08;
    for (SoundGroup **it = unknown108.unknown10; it != end; it++) {
      if ((*it)->unknown18 == id) {
        return *it;
      }
    }
  }
  return nullptr;
}

SoundEntry *SoundBank::begin() const {
  if (SoundCore::instance_ != nullptr) {
    return unknowne0.unknown002();
  }
  return nullptr;
}

const SoundEntry *SoundBank::end() const {
  if (SoundCore::instance_ != nullptr) {
    return unknowne0.unknown003();
  }
  return nullptr;
}

bool SoundBank::empty() const {
  if (SoundCore::instance_ != nullptr) {
    return unknowne0.head.next == &unknowne0.head;
  }
  return false;
}

SoundEntry *SoundBank::AddSoundEntry(SoundEntry *entry) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr || m_number < 0) {
    return nullptr;
  }
  entry->unknownd0 = this;
  core->unknown708.Lock();
  unknowne0.PushBack(entry);
  core->unknown708.Unlock();
  return entry;
}

Result SoundBank::RemoveSoundEntry(int number) {
  if (SoundCore::instance_ == nullptr) {
    return static_cast<Result>(-12);
  }
  if (m_number < 0) {
    return static_cast<Result>(-14);
  }
  SoundEntry *entry = GetSoundEntryFromNumber(number);
  if (entry != nullptr) {
    return RemoveSoundEntry(entry);
  }
  return static_cast<Result>(-27);
}

Result SoundBank::RemoveSoundEntry(SoundEntry *entry) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return static_cast<Result>(-12);
  }
  if (m_number < 0) {
    return static_cast<Result>(-14);
  }
  if (entry == nullptr) {
    return static_cast<Result>(-6);
  }
  core->unknown708.Lock();
  unknowne0.unknown001(entry);
  core->unknown708.Unlock();
  if (entry->unknownd8) {
    SoundMemory::allocator_->unknown001(entry);
  }
  return set_result(static_cast<Result>(0));
}

SoundEntry *SoundBank::GetSoundEntryFromNumber(int number) const {
  if (SoundCore::instance_ == nullptr) {
    return nullptr;
  }
  if (m_number < 0) {
    return nullptr;
  }
  for (SoundEntry *it = begin(); it != end(); it = List<SoundEntry>::unknown004(it)) {
    if (it->unknown78 == number) {
      return it;
    }
  }
  return nullptr;
}

SoundEntry *SoundBank::GetSoundEntryFromIndex(int index) const {
  if (SoundCore::instance_ == nullptr) {
    return nullptr;
  }
  if (m_number >= 0) {
    if (unknowne0.count <= index) {
      return nullptr;
    }
    for (SoundEntry *it = begin(); it != end(); it = List<SoundEntry>::unknown004(it)) {
      if (index-- == 0) {
        return it;
      }
    }
  }
  return nullptr;
}

Result SoundBank::AddSoundGroup(SoundGroup *group) {
  if (SoundCore::instance_ != nullptr && m_number >= 0) {
    int count = unknown108.unknown08;
    if (unknown108.unknown0c <= count) {
      unknown108.SetArraySize(unknown108.unknown0c + 16);
      count = unknown108.unknown08;
    }
    unknown108.unknown10[count] = group;
    unknown108.unknown08++;
    return set_result(static_cast<Result>(0));
  }
  return static_cast<Result>(-1);
}

int SoundBank::GetReferenceCounter() const {
  if (SoundCore::instance_ == nullptr) {
    return 0;
  }
  if (m_number >= 0) {
    int count = 0;
    for (SoundEntry *it = begin(); it != end(); it = List<SoundEntry>::unknown004(it)) {
      count += it->unknownc8->unknown6c;
    }
    return count;
  }
  return 0;
}

Result SoundBank::Stop(f32 fadeTime) {
  SystemCore *core = static_cast<SystemCore *>(SoundCore::instance_);
  if (core == nullptr) {
    return static_cast<Result>(-12);
  }
  if (m_number >= 0) {
    core->StopBank(this, fadeTime);
    return set_result(static_cast<Result>(0));
  }
  return static_cast<Result>(-14);
}

SoundEntry::SoundEntry() : Object(ObjectType::SOUND_ENTRY), unknown70(0), unknownc8(nullptr), unknownd0(nullptr), unknownd8(false) {}

SoundEntry::~SoundEntry() {}

SoundGroup *SoundEntry::GetSoundGroup() const {
  if (SoundCore::instance_ == nullptr) {
    return nullptr;
  }
  return unknownd0->GetSoundGroup(unknown7d);
}

template List<SoundBank> *List<SoundBank>::Delete();
template List<SoundBank>::Node::~Node();

template List<SoundEntry> *List<SoundEntry>::Delete();
template List<SoundEntry>::Node::~Node();

} // namespace ssd
