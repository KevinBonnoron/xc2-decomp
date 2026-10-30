#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {

// Layout evidence: constructor 0x71007b12b4 (stores at 0x0, 0x8, 0x10, 0x18, 0x20), release 0x71007b1308 (flags
// tested at 0x18, release type taken from its upper half), BuffReleaseTbl::createObj 0x71007b1620 (next link at
// 0x20, stride 0x28) and CGLibSystemContext::releaseDelay* (0x71007a8c48 to 0x71007a8e14) which fill the members.
class CGLibReleaseObj_plf {
public:
  struct wrkRelease {
    void *unknown00; // Inferred role: object to release; original member name unknown.
    void *unknown08; // Inferred role: allocated buffer; original member name unknown.
    u32 unknown10;   // Inferred role: texture id; original member name unknown.
    u32 unknown14;   // Inferred role: sampler id; original member name unknown.
    u16 unknown18;   // Inferred role: release flags; original member name unknown.
    u16 unknown1a;   // Inferred role: release type; original member name unknown.
    u32 unknown1c;   // Inferred role: unused; original member name unknown.
  };

  typedef void (*ReleaseFunc)(wrkRelease &work);

  static void release_mempool(wrkRelease &work);
  static void release_textrue(wrkRelease &work);
  static void release_sampler(wrkRelease &work);
  static void release_vertex(wrkRelease &work);

  static ReleaseFunc s_callRelease[4];

  wrkRelease unknown00; // Inferred role: release work; original member name unknown.
};

static_assert(offsetof(CGLibReleaseObj_plf::wrkRelease, unknown18) == 0x18, "");
static_assert(sizeof(CGLibReleaseObj_plf::wrkRelease) == 0x20, "");

class CGLibReleaseObj : public CGLibReleaseObj_plf {
public:
  CGLibReleaseObj();
  ~CGLibReleaseObj();
  void release();

  CGLibReleaseObj *unknown20; // Inferred role: next link; original member name unknown.
};

static_assert(offsetof(CGLibReleaseObj, unknown20) == 0x20, "");
static_assert(sizeof(CGLibReleaseObj) == 0x28, "");

} // namespace grlib
