#include "event/cam_util.h"

#include "bdat.h"
#include <math.h>

namespace event {

constexpr f32 FILM_WIDTH = 25.39f;
constexpr f32 PI = 3.1415f;
constexpr f32 DEG_TO_RAD = 0.017452778f;

f32 CamUtil::toFov(f32 focal) { return atanf(FILM_WIDTH / (focal * 2.0f)) * 2.0f * 180.0f / PI; }

f32 CamUtil::toFocal(f32 fov) { return FILM_WIDTH / (tanf(fov * DEG_TO_RAD * 0.5f) * 2.0f); }

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
