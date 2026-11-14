#include "event/cam_util.h"

#include "bdat.h"
#include <math.h>

namespace event {

constexpr f32 unknown015 = 25.39f;       // Inferred role: film width; original name unknown.
constexpr f32 unknown016 = 3.1415f;      // Inferred role: pi; original name unknown.
constexpr f32 unknown017 = 0.017452778f; // Inferred role: deg to rad; original name unknown.

f32 CamUtil::toFov(f32 focal) { return atanf(unknown015 / (focal * 2.0f)) * 2.0f * 180.0f / unknown016; }

f32 CamUtil::toFocal(f32 fov) { return unknown015 / (tanf(fov * unknown017 * 0.5f) * 2.0f); }

f32 CamUtil::id2near(int id) {
  Bdat::Value value;
  value.valueU32 = Bdat::getValCheck(Bdat::getFP("EVT_nearfar"), "near", id, 8);
  return value.valueF32;
}

f32 CamUtil::id2far(int id) {
  Bdat::Value value;
  value.valueU32 = Bdat::getValCheck(Bdat::getFP("EVT_nearfar"), "far", id, 8);
  return value.valueF32;
}

const char *CamUtil::id2nearfarName(int id) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_nearfar"), "name", id, 7)); }

} // namespace event
