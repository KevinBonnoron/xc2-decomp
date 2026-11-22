#pragma once
#include <stddef.h>

#include "grlib/cglib_shd_list.h"
#include "types.h"

namespace ml {
class DrCalcStmListObj;
struct MdsMatTechnique;
class DrShdMdoDecRes;

// Inferred helper: returns the shader of a shader list at a u32 (zero extended) index, the form of the group index of CGLibShdListBase::unknown004; original name unknown. Users:
// DrShdMdoDecShdObj::DrShdMdoDecShdObj (1.0.0: 0x71008a0a7c, inlined in both DrShdMdoMan::createShaderObj, 0x71008a05e8 and 0x71008a0774) and DrShdMdoExtTblObj::setDecObj (0x71008a1144). In
// those loops the game keeps the shader pointer on a plain 64 bit induction variable and sign extends (add 1 << 32, asr 32) the 32 bit counter for the technique and extension table indexes.
// With the shader written `list.unknown40[i]` clang widens the counter once for all of them (the constructor 54 instructions against the game's 62, createShaderObj 91 and 99 against 99 and 107,
// setDecObj 101 against 107); with a u32 accessor for the technique entry instead (createShaderObj 97) the pointer walk of the technique replaces the shifted counter.
template <typename T> inline T *unknown102(grlib::CGLibShdListBase<T> &list, u32 index) { return list.unknown40 + index; }

class DrShdMdoDecShdObj {
public:
  DrShdMdoDecShdObj(const u8 *data, const u8 *vertexData, const MdsMatTechnique *technique);
  ~DrShdMdoDecShdObj();
  void update();
  void changeMemShader(const u8 *data, const u8 *vertexData, const MdsMatTechnique *technique);

  DrShdMdoDecShdObj *unknown00;                      // Inferred role: previous shader object; original member name unknown.
  DrShdMdoDecShdObj *unknown08;                      // Inferred role: next shader object; original member name unknown.
  const u8 *unknown10;                               // Inferred role: shader pack data; original member name unknown.
  s32 unknown18;                                     // Inferred role: reference count; original member name unknown.
  DrCalcStmListObj *m_drCalcStmListObj;              // Inferred role: stream list object; original member name unknown.
  grlib::CGLibShdListBase<DrShdMdoDecRes> unknown28; // Inferred role: shader list; original member name unknown.
};

static_assert(offsetof(DrShdMdoDecShdObj, unknown08) == 0x08, "");
static_assert(offsetof(DrShdMdoDecShdObj, unknown10) == 0x10, "");
static_assert(offsetof(DrShdMdoDecShdObj, unknown18) == 0x18, "");
static_assert(offsetof(DrShdMdoDecShdObj, m_drCalcStmListObj) == 0x20, "");
static_assert(offsetof(DrShdMdoDecShdObj, unknown28) == 0x28, "");
static_assert(sizeof(DrShdMdoDecShdObj) == 0x80, "");

} // namespace ml
