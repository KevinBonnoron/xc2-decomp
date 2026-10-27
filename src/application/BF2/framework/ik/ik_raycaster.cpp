#include "framework/ik/ik_raycaster.h"

#include "fw/fw_coli_check.h"
#include "mm_math/mm_vec3.h"

namespace fw {

bool Raycaster::castRay(const mm::Vec3 &start, const mm::Vec3 &end, mm::Vec3 *position, mm::Vec3 *normal) {
  ColiCheckConfig config;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown14 = false;
  config.unknown15 = false;
  config.unknown10 = 1;
  config.unknown04 = 0xfffffffa;
  config.unknown00 = 9;
  TColiCheckResult<256> result;
  ColiCheck::testLine(result, start, end, config);
  if (result.getCount() != 0) {
    *position = result.getPosition(0);
    *normal = result.getNormal(0);
  }

  return result.isHit;
}

PlaneRayCaster::PlaneRayCaster() : unknown08(nullptr) {}

void PlaneRayCaster::bind(IKFootGroundInterface &ground) { unknown08 = &ground; }

} // namespace fw
