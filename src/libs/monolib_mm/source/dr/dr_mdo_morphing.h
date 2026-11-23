#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrResEtcPamObj;
class DrResMdoMorpObj;
struct MdoWrkMatRes;

class DrMdoMorphing {
public:
  DrMdoMorphing(MdoWrkMatRes *matRes, DrResMdoMorpObj *morpObj, DrResEtcPamObj *pamObj);
  ~DrMdoMorphing();
  void updateParms();
  void resetDefVertex();
  void blendVertex();
  void oldPosVertex();
  int isBlendCheck() const;
  void parmsUpdate();

  MdoWrkMatRes *m_mdoWrkMatRes;       // Inferred role: material work resource; original member name unknown.
  DrResMdoMorpObj *m_drResMdoMorpObj; // Inferred role: morph object; original member name unknown.
  DrResEtcPamObj *m_drResEtcPamObj;   // Inferred role: parameter object; original member name unknown.
  u8 _18[0x1c - 0x18];
  s32 unknown1c; // Inferred role: blend index; original member name unknown.
  // The stack frame of DrResMdoMorpObj::update holds a 0x40 byte DrMdoMorphing; no game function touches 0x20..0x3f.
  u8 _20[0x40 - 0x20];
};

static_assert(offsetof(DrMdoMorphing, m_drResMdoMorpObj) == 0x08, "");
static_assert(offsetof(DrMdoMorphing, m_drResEtcPamObj) == 0x10, "");
static_assert(offsetof(DrMdoMorphing, unknown1c) == 0x1c, "");
static_assert(sizeof(DrMdoMorphing) == 0x40, "");

} // namespace ml
