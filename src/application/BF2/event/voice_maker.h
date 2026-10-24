#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace event {

class VoiceMaker {
public:
  enum {
    FLAG_ENABLE = 1 << 0,
  };

  VoiceMaker();
  virtual ~VoiceMaker() {}
  void create(bool isEnable, const char *directory, const char *name);
  const char *makePath(const char *file);

private:
  u32 unknown08;                   // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<256> unknown0c;  // Inferred role: folder; original member name unknown.
  mm::mtl::FixStr<256> unknown110; // Inferred role: path; original member name unknown.
};

static_assert(sizeof(VoiceMaker) == 0x218, "");

} // namespace event
