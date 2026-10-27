#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrResMdoSeamMemObj;
class DrResMdoSeamParmRead;
class DrResMdoSeamTexture;
class DrResMdoSeamVertex;

class DrResMdoSeamWrkPosInst {
public:
  // Inferred role: shared work of the position tree; original type name unknown.
  struct unknown001 {
    const u8 *unknown00; // Inferred role: position data; original member name unknown.
    const u8 *unknown08; // Inferred role: tree; original member name unknown.
    s32 unknown10;       // Inferred role: tree num; original member name unknown.
    s32 unknown14;       // Inferred role: bit table size; original member name unknown.
    u32 *unknown18;      // Inferred role: bit table; original member name unknown.
  };

  // Inferred role: entry of a position; original type name unknown.
  struct unknown002 {
    u8 _00[0x08];
    const u8 *unknown08; // Inferred role: position model; original member name unknown.
    u8 _10[0x28 - 0x10];
  };

  // Inferred role: offsets of the position model tables; original type name unknown.
  struct unknown003 {
    u32 unknown00; // Inferred role: first table offset; original member name unknown.
    u8 _04[0x08 - 0x04];
    u32 unknown08; // Inferred role: second table offset; original member name unknown.
    u8 _0c[0x10 - 0x0c];
    u32 unknown10; // Inferred role: third table offset; original member name unknown.
  };

  DrResMdoSeamWrkPosInst();
  void delCall();
  u32 getDataSize() const;
  u32 clipCheck(u32 index);
  u32 *getShwBitTbl(u32 index);
  void clearShwBitTbl(u32 index);
  void clearAllShwBitTbl();
  void changeMemBaseInstPos(const u8 *data);
  void changeMemEtcInstPos();
  static void seachCalcTbl(u16 *vertexTbl, u16 *textureTbl, DrResMdoSeamVertex *seamVertex, DrResMdoSeamTexture *seamTexture, DrResMdoSeamParmRead *parmRead);

  static u16 *s_pVertexTbl;
  static u16 *s_pTextureTbl;
  static DrResMdoSeamVertex *s_pSeamVertex;
  static DrResMdoSeamTexture *s_pSeamTexture;
  static DrResMdoSeamParmRead *s_pParmRead;

  const u8 *unknown00;         // Inferred role: position data; original member name unknown.
  const u8 *unknown08;         // Inferred role: position models; original member name unknown.
  const u8 *unknown10;         // Inferred role: first position table; original member name unknown.
  const u8 *unknown18;         // Inferred role: second position table; original member name unknown.
  const unknown003 *unknown20; // Inferred role: model table offsets; original member name unknown.
  const u8 *unknown28;         // Inferred role: first model table; original member name unknown.
  const u8 *unknown30;         // Inferred role: second model table; original member name unknown.
  const u8 *unknown38;         // Inferred role: third model table; original member name unknown.
  unknown001 *unknown40;
  unknown002 *unknown48;
  DrResMdoSeamMemObj *unknown50; // Inferred role: memory object; original member name unknown.
  u32 **unknown58;               // Inferred role: shadow bit tables; original member name unknown.
  u32 unknown60;                 // Inferred role: shadow bit table size; original member name unknown.
  u8 _64[0x6c - 0x64];
  s32 unknown6c; // Inferred role: position num; original member name unknown.
  u8 _70[0x74 - 0x70];
  u32 unknown74;   // Inferred role: state flags; original member name unknown.
  void *unknown78; // Inferred role: allocated work; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown48) == 0x48, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown50) == 0x50, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown58) == 0x58, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown60) == 0x60, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown6c) == 0x6c, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown74) == 0x74, "");
static_assert(offsetof(DrResMdoSeamWrkPosInst, unknown78) == 0x78, "");
static_assert(sizeof(DrResMdoSeamWrkPosInst) == 0x80, "");

} // namespace ml
