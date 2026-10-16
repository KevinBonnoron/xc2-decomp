#pragma once
#include "mm_mtl/fixstr.h"

namespace fw {
class CommonResource;
} // namespace fw

class RchaCam;

namespace event {

class ShakerRes {
public:
  ShakerRes();
  virtual ~ShakerRes();
  void destroy();
  void create(const char *name);
  void update();

  const char *getName() const { return name.c_str(); }
  RchaCam *getRcha() const { return rcha; }

private:
  mm::mtl::FixStr<64> name;
  fw::CommonResource *resource;
  RchaCam *rcha;
};

static_assert(sizeof(ShakerRes) == 0x60, "");

} // namespace event
