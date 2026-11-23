#pragma once
#include <stddef.h>

#include "dr/dr_res_mdo_tex_list.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
class DrMan;
class DrCalcStmListObj;
class DrResEtcTexList;

class DrMdoTextureMan {
public:
  DrMdoTextureMan(DrMan *drMan);
  ~DrMdoTextureMan();
  // Inferred role: appends a new model texture list; original name unknown.
  void unknown001(DrResMdoTexList *list) {
    if (unknown10 == nullptr) {
      unknown08 = list;
      unknown10 = list;
      list->unknown00 = nullptr;
    } else {
      unknown10->unknown08 = list;
      list->unknown00 = unknown10;
      unknown10 = list;
    }
    list->unknown08 = nullptr;
  }
  DrResMdoTexList *createTextureObj(const u8 *data);
  DrResMdoTexList *createTextureObj(const u8 *header, const u8 *data);
  DrResMdoTexList *createTextureObj(const u8 *header, DrCalcStmListObj *stmList, const u8 *data, const MdsTexHeader *stmHeader);
  DrResMdoTexList *createTextureObj(const u8 *header, DrCalcStmListObj *stmList, const u8 *data, const u16 *stmTexIdx);
  DrResEtcTexList *createEtxTexture(const u8 *data);
  void releaseTextureObj(DrResMdoTexList *list);
  void update();
  grlib::CGLibTextureBuffer *getTextureID(u32 id);
  grlib::CGLibTextureBuffer *getTextureName(const char *name);

  DrMan *m_drMan;             // Inferred role: dr man; original member name unknown.
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
