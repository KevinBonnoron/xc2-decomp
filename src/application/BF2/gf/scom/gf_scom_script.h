#pragma once
#include "types.h"

namespace gf {

class SCOM_SCRIPT {
public:
  static void create(u32 slot, const char *script, bool isWait);
};

} // namespace gf
