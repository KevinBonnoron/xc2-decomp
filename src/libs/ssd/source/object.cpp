#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"

namespace ssd {

Object::Object(ObjectType::Id type) : unknown08(type), unknown0c(0), m_soundCore(SoundCore::instance_) {}

} // namespace ssd
