#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"

namespace ssd {

int SoundBank::GetNumber() const { return m_number; }

int SoundBank::NumSoundEntry() const { return m_numSoundEntry; }

SoundGroup *SoundBank::GetSoundGroup(int id) const {
  if (SoundCore::instance_ == nullptr) {
    return nullptr;
  }
  if (m_number >= 0) {
    SoundGroup **end = unknown118 + unknown110;
    for (SoundGroup **it = unknown118; it != end; it++) {
      if ((*it)->unknown18 == id) {
        return *it;
      }
    }
  }
  return nullptr;
}

SoundGroup *SoundEntry::GetSoundGroup() const {
  if (SoundCore::instance_ == nullptr) {
    return nullptr;
  }
  return unknownd0->GetSoundGroup(unknown7d);
}

} // namespace ssd
