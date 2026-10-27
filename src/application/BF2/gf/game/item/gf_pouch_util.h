#pragma once
#include "types.h"

namespace gf {

struct SDataPouch;

class GfPouchUtil {
public:
  static SDataPouch *getPouch(u32 driver, u32 slot);
  static bool isExistOpenItem();
};

} // namespace gf
