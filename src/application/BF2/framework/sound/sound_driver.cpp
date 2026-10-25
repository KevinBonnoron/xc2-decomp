#include "framework/sound/sound_driver.h"

namespace fw {

bool ISoundDriver::isDeviceEnable() const { return false; }

void ISoundDriver::attachPoolMemory(void *memory, u32 size) {}

void ISoundDriver::detachPoolMemory(void *memory, u32 size) {}

} // namespace fw
