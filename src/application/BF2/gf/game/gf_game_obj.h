#pragma once
#include "mm_mtl/fixstr.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfGameObj {
public:
  static bool isEmpty();
  static void bdatReload();
  static bool isValidGameObj(GF_OBJ_HANDLE *handle, bool isCheckState, mm::mtl::FixStr<128> *reason);
  static bool isEnterGameObj(GF_OBJ_HANDLE *handle);
};

} // namespace gf
