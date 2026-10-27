#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
class DrMan;
class DrResEtcTexList;
class DrResMdoTexList;

class DrMdoTextureMan {
public:
  DrMdoTextureMan(DrMan *drMan);
  ~DrMdoTextureMan();
  DrResMdoTexList *createTextureObj(const u8 *data);
  DrResMdoTexList *createTextureObj(const u8 *header, const u8 *data);
  DrResEtcTexList *createEtxTexture(const u8 *data);
  void releaseTextureObj(DrResMdoTexList *list);
  grlib::CGLibTextureBuffer *getTextureID(u32 id);
  grlib::CGLibTextureBuffer *getTextureName(const char *name);

  DrMan *unknown00;           // Inferred role: dr man; original member name unknown.
  DrResMdoTexList *unknown08; // Inferred role: first mdo texture list; original member name unknown.
  DrResMdoTexList *unknown10; // Inferred role: last mdo texture list; original member name unknown.
  DrResEtcTexList *unknown18; // Inferred role: first etc texture list; original member name unknown.
  DrResEtcTexList *unknown20; // Inferred role: last etc texture list; original member name unknown.
};

static_assert(offsetof(DrMdoTextureMan, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoTextureMan, unknown10) == 0x10, "");
static_assert(offsetof(DrMdoTextureMan, unknown18) == 0x18, "");
static_assert(offsetof(DrMdoTextureMan, unknown20) == 0x20, "");

} // namespace ml
