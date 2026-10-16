#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfAppend {
public:
  u16 getMountIndex() const;
};

class GfAppendWire {
public:
  void startWire(GF_OBJ_HANDLE *target, f32 time);
  void startWireWithClose(GF_OBJ_HANDLE *target, f32 time, f32 closeTime, f32 closeDistance);
  void startWireWithBone(GF_OBJ_HANDLE *target, const char *bone, f32 time);
  void endWire(f32 time);
};

} // namespace gf
