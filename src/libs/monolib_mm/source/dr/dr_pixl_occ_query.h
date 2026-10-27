#pragma once
#include <stddef.h>

#include "grlib/cglib_occlusion_query.h"
#include "types.h"

namespace ml {
class DrResUseQueryObj;
class DrShdDataList;
class DrShdDataObj;

struct DrResQueryObj {
  u32 getOccZPassCount();
  DrResQueryObj();
  ~DrResQueryObj();
  bool update();
  void begin();
  void end();

  DrResQueryObj *unknown00;             // Inferred role: next; original member name unknown.
  DrResQueryObj *unknown08;             // Inferred role: prev; original member name unknown.
  grlib::CGLibOcclusionQuery unknown10; // Inferred role: query; original member name unknown.
  DrResUseQueryObj *unknown28;          // Inferred role: user; original member name unknown.
  DrResQueryObj *unknown30;             // Inferred role: sub next; original member name unknown.
  u32 unknown38;                        // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrResQueryObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResQueryObj, unknown28) == 0x28, "");
static_assert(offsetof(DrResQueryObj, unknown38) == 0x38, "");

class DrPixlOccQuery {
public:
  DrResQueryObj *createObj();
  void end();

  u8 _00[0x10 - 0x00];
  DrShdDataList *unknown10; // Inferred role: shader data list; original member name unknown.
  DrShdDataObj *unknown18;  // Inferred role: occlusion box shader; original member name unknown.
  u8 _20[0x24 - 0x20];
  s32 unknown24; // Inferred role: post uniform block offset; original member name unknown.
  u32 unknown28; // Inferred role: query state; original member name unknown.
};

static_assert(offsetof(DrPixlOccQuery, unknown10) == 0x10, "");
static_assert(offsetof(DrPixlOccQuery, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlOccQuery, unknown24) == 0x24, "");
static_assert(offsetof(DrPixlOccQuery, unknown28) == 0x28, "");

} // namespace ml
