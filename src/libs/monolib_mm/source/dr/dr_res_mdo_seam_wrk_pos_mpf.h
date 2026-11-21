#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrResMdoSeamMemObj;

// Inferred role: node of the object tree of an instance mpf; original member names unknown. Layout from DrMdoCtlMpfInst::calcInstMpf (0x71007f9fc4), which
// steps through the nodes at 0x20 bytes and reads the u16 at 0x1c; the rest of the node is read by calcMpfObjTree, not matched yet.
struct MdsMpfObjTreeData {
  u8 _00[0x1c];
  u16 unknown1c; // Inferred role: index of the object data; original member name unknown.
  u8 _1e[0x20 - 0x1e];
};

static_assert(offsetof(MdsMpfObjTreeData, unknown1c) == 0x1c, "");
static_assert(sizeof(MdsMpfObjTreeData) == 0x20, "");

class DrResMdoSeamWrkPosMpf {
public:
  // Inferred role: header of the position data of an etc mpf; original type name unknown.
  struct unknown001 {
    u8 _00[0x04];
    u32 unknown04; // Inferred role: first table offset; original member name unknown.
    u8 _08[0x0c - 0x08];
    u32 unknown0c; // Inferred role: second table offset; original member name unknown.
    u32 unknown10; // Inferred role: position num; original member name unknown.
  };

  DrResMdoSeamWrkPosMpf();
  u32 getDataSize() const;
  void setupMpfBasePos(const u8 *data);
  void setupMpfEtcPos(int index, DrResMdoSeamMemObj *memObj);
  void changeMemCall();

  const u8 *unknown00;                // Inferred role: first position table; original member name unknown.
  const MdsMpfObjTreeData *unknown08; // Inferred role: object tree nodes (0x20 byte stride, read by DrMdoCtlMpfInst::calcInstMpf, 0x71007f9fc4); original member name unknown.
  const u8 *unknown10;                // Inferred role: position data; original member name unknown.
  s32 unknown18;                      // Inferred role: position num; original member name unknown. Signed: DrMdoCtlMpfInst::calcInstMpf compares it with `cmp w8, #1; b.lt` and `ldrsw` (0x71007f9fc4).
  DrResMdoSeamMemObj *unknown20;      // Inferred role: memory object; original member name unknown.
  s32 unknown28;                      // Inferred role: etc position index; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkPosMpf, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoSeamWrkPosMpf, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoSeamWrkPosMpf, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkPosMpf, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoSeamWrkPosMpf, unknown28) == 0x28, "");

} // namespace ml
