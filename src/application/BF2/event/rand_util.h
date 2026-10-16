#pragma once
#include "mm_math/mm_vec3.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class Object;

class RandUtil {
public:
  static Object *searchByID(int id);
  static mm::Vec3 getEyePos(gf::GF_OBJ_HANDLE *handle);
  static mm::Vec3 getEyePos(int id);
  static mm::Vec3 getCurentTarPos(int id, bool &isFound);
};

} // namespace event
