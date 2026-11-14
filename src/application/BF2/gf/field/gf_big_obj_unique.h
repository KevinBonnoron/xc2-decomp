#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfBigObjUnique {
public:
  struct CreateInfo {
    GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
  };

  GfBigObjUnique(const CreateInfo *info);
  ~GfBigObjUnique() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  void update(f32 deltaTime);

  GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
  f32 unknown08;            // Inferred role: time since the last unique motion; original member name unknown.
  f32 unknown0c;            // Inferred role: previous local time of the asm; original member name unknown.
};

static_assert(offsetof(GfBigObjUnique, unknown08) == 0x08, "");
static_assert(offsetof(GfBigObjUnique, unknown0c) == 0x0c, "");
static_assert(sizeof(GfBigObjUnique) == 0x10, "");

} // namespace gf
