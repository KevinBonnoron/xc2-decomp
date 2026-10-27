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
  void create(const CreateInfo &info);
  void dispose();

  GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
  u64 unknown08;            // Role and original member name unknown.
};

static_assert(offsetof(GfBigObjUnique, unknown08) == 0x08, "");
static_assert(sizeof(GfBigObjUnique) == 0x10, "");

} // namespace gf
