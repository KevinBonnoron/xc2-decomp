#pragma once
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

class alignas(8) GfEvtSe {
public:
  GfEvtSe();
  ~GfEvtSe();
  void cleanup();
  void destroySe();
  void createSe(const char *name);
  bool isLoadedSe() const;
  void update(const fw::UpdateInfo &info);

  u8 _0[0x1d0 - 0x0];
};

static_assert(sizeof(GfEvtSe) == 0x1d0, "");

} // namespace gf
