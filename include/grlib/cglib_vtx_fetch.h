#pragma once
#include <stddef.h>

#include "types.h"

struct NVNvertexAttribState;

// Inferred role: vtx format; original type name unknown.
enum unknown073 {
  unknown073_10 = 10, // Inferred role: r32f; original name unknown.
  unknown073_11 = 11, // Inferred role: r32ui; original name unknown.
  unknown073_13 = 13,
  unknown073_17 = 17, // Inferred role: rg16f; original name unknown.
  unknown073_19 = 19, // Inferred role: rg16sn; original name unknown.
  unknown073_20 = 20, // Inferred role: rg16ui; original name unknown.
  unknown073_22 = 22, // Inferred role: rg32f; original name unknown.
  unknown073_34 = 34, // Inferred role: rgb32f; original name unknown.
  unknown073_37 = 37, // Inferred role: rgba8; original name unknown.
  unknown073_38 = 38, // Inferred role: rgba8sn; original name unknown.
  unknown073_39 = 39, // Inferred role: rgba8ui; original name unknown.
  unknown073_42 = 42, // Inferred role: rgba16; original name unknown.
  unknown073_43 = 43, // Inferred role: rgba16sn; original name unknown.
  unknown073_45 = 45, // Inferred role: rgba16i; original name unknown.
  unknown073_46 = 46, // Inferred role: rgba32f; original name unknown.
  unknown073_47 = 47, // Inferred role: rgba32ui; original name unknown.
};

namespace grlib {

struct CGLibVtxAttr {
  unknown073 unknown00; // Inferred role: format; original member name unknown.
  u32 unknown04;        // Inferred role: location; original member name unknown.
  u32 unknown08;        // Inferred role: offset; original member name unknown.
  u32 unknown0c;        // Inferred role: buffer index; original member name unknown.
};

class CGLibVtxFetch {
public:
  CGLibVtxFetch();
  ~CGLibVtxFetch();
  void release();
  void createFetchObj(CGLibVtxAttr *attributes, int num);
  void createMemFetchObj(void *memory, CGLibVtxAttr *attributes, int num);
  static int calcFetchWorkSize(int num);

  NVNvertexAttribState *unknown00; // Inferred role: attribute states; original member name unknown.
  u16 unknown08;                   // Inferred role: attribute num; original member name unknown.
  u16 unknown0a;                   // Inferred role: owns attribute states; original member name unknown.
  u8 _0c[0x10 - 0x0c];
};

static_assert(offsetof(CGLibVtxFetch, unknown0a) == 0x0a, "");

} // namespace grlib
