#pragma once
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

class GfDataSound {
public:
  static void getFullPath(mm::mtl::FixStr<128> &path, const char *name);
  static bool getFootStepSePackFile(mm::mtl::FixedVector<const char *, 2> &files, u32 footStep);
  static const char *getSeFileByWeaponType(u32 weaponType);
};

} // namespace gf
