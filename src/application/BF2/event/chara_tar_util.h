#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaTarUtil {
public:
  static mm::Vec3 getCharaDefaultEyeVec(gf::GF_OBJ_HANDLE *handle);
  static mm::Vec3 getCharaEyePos(gf::GF_OBJ_HANDLE *handle);
  static f32 getCharaEyeRotY(gf::GF_OBJ_HANDLE *handle);
  static mm::Vec3 calcTarget(const mm::Vec3 &position, const mm::Vec3 &eyePosition, f32 weight, const mm::Vec3 &target, f32 rotation);
  static mm::Vec3 calcWeight(const mm::Vec3 &position, const mm::Vec3 &target, f32 rotation);
  static const char *aimmotType2stat(int type);
  static const char *aimmotType2name(int type);
};

} // namespace event
