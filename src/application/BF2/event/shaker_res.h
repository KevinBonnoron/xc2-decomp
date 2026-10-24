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

  const char *getName() const { return unknown08.c_str(); }
  RchaCam *getRcha() const { return unknown58; }

private:
  mm::mtl::FixStr<64> unknown08; // Inferred role: name; original member name unknown.
  fw::CommonResource *unknown50; // Inferred role: resource; original member name unknown.
  RchaCam *unknown58;            // Inferred role: rcha; original member name unknown.
};

static_assert(sizeof(ShakerRes) == 0x60, "");

} // namespace event
