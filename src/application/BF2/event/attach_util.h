#pragma once
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf
namespace mm {
struct Vec3;
} // namespace mm

namespace event {

enum ATTACH_TYPE : int;

class AttachUtil {
public:
  static void setCaster(bool isSet, gf::GF_OBJ_HANDLE *handle, u32 effect);
  static void setMount(bool isSet, gf::GF_OBJ_HANDLE *handle, u32 effect, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type);
};

} // namespace event
