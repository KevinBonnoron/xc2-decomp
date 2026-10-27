#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
class DrMan;
class DrResEtcTexList;

class DrMdoTextureMan {
public:
  DrMdoTextureMan(DrMan *drMan);
  grlib::CGLibTextureBuffer *getTextureID(u32 id);
  grlib::CGLibTextureBuffer *getTextureName(const char *name);

  DrMan *unknown00;           // Inferred role: dr man; original member name unknown.
  void *unknown08;            // Inferred role: unknown pointer cleared by the constructor; original member name unknown.
  void *unknown10;            // Inferred role: unknown pointer cleared by the constructor; original member name unknown.
  DrResEtcTexList *unknown18; // Inferred role: etc texture lists; original member name unknown.
  void *unknown20;            // Inferred role: unknown pointer cleared by the constructor; original member name unknown.
};

static_assert(offsetof(DrMdoTextureMan, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoTextureMan, unknown10) == 0x10, "");
static_assert(offsetof(DrMdoTextureMan, unknown18) == 0x18, "");
static_assert(offsetof(DrMdoTextureMan, unknown20) == 0x20, "");

} // namespace ml
