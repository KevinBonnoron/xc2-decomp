#include "dr/dr_environment_time.h"

namespace ml {

// Inferred role: header of the environment time data block; original type name unknown.
struct unknown001 {
  s32 unknown00; // Inferred role: key count; original member name unknown.
  u32 unknown04; // Inferred role: offset of the keys from the block; original member name unknown.
};

DrEnvironmentTime::DrEnvironmentTime() : unknown00(nullptr), unknown08(nullptr), unknown10(0), unknown14(0), unknown18(0.06f), unknown1c(0.2f), unknown28(false), unknown29(0) {
  unknown2c = 0;
  unknown20 = 0;
  unknown24 = 0;
}

bool DrEnvironmentTime::setEnvTimeData(const LgtFileHeader *header, const u8 *data, bool isLoop) {
  unknown28 = isLoop;
  if (header->unknown1c != 0) {
    unknown00 = data + header->unknown1c;
    const unknown001 *time = reinterpret_cast<const unknown001 *>(unknown00);
    unknown10 = time->unknown00;
    unknown08 = unknown00 + time->unknown04;
    return true;
  }
  return false;
}

void DrEnvironmentTime::changeMemEnvTimeData(const LgtFileHeader *header, const u8 *data) {
  if (header->unknown1c != 0) {
    unknown00 = data + header->unknown1c;
    unknown08 = unknown00 + reinterpret_cast<const unknown001 *>(unknown00)->unknown04;
  }
}

} // namespace ml
