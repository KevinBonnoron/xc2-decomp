#pragma once
#include <stddef.h>

namespace ml {

class DrMan;
class DrResMdoTexSimple;

class DrMdoTexSimpleMan {
public:
  DrMdoTexSimpleMan(DrMan *drMan);
  ~DrMdoTexSimpleMan();
  DrResMdoTexSimple *createTextureObj(const void *data, int size, bool isMiddle);

  DrMan *unknown00;                   // Inferred role: dr manager; original member name unknown.
  DrResMdoTexSimple *unknown08[2][2]; // Inferred role: first and last texture per buffer; original member name unknown.
  DrResMdoTexSimple *unknown28;       // Inferred role: first texture; original member name unknown.
  DrResMdoTexSimple *unknown30;       // Inferred role: last texture; original member name unknown.
  DrResMdoTexSimple *unknown38;       // Inferred role: first released texture; original member name unknown.
  DrResMdoTexSimple *unknown40;       // Inferred role: last released texture; original member name unknown.
};

static_assert(offsetof(DrMdoTexSimpleMan, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoTexSimpleMan, unknown28) == 0x28, "");
static_assert(offsetof(DrMdoTexSimpleMan, unknown38) == 0x38, "");
static_assert(sizeof(DrMdoTexSimpleMan) == 0x48, "");

} // namespace ml
