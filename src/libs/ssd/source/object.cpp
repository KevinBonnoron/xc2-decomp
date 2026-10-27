#include "ssd/ssd_sound.h"
#include "ssd/ssd_sound_core.h"

namespace ssd {

Object::Object(ObjectType::Id type) : unknown08(type), unknown0c(0), unknown10(SoundCore::instance_) {}

} // namespace ssd
