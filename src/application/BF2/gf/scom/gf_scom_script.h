#pragma once
#include "types.h"

namespace gf {

struct GF_SCOM_HANDLE;

class SCOM_SCRIPT {
public:
  static GF_SCOM_HANDLE *create(u32 slot, const char *script, bool isWait);
};

} // namespace gf
