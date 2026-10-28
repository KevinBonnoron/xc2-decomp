#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

struct GfDropitemInfo {
  u32 unknown00; // Inferred role: item id; original member name unknown.
  u16 unknown04; // Inferred role: number and percentage; original member name unknown.
  u8 _06[0x08 - 0x06];
  u32 unknown08; // Inferred role: gold; original member name unknown.
  u32 unknown0c; // Role and original member name unknown.
};

static_assert(offsetof(GfDropitemInfo, unknown08) == 0x08, "");
static_assert(sizeof(GfDropitemInfo) == 0x10, "");

class GfFobjDropitem {
public:
  struct BdatInfo {
    void create(s32 id);

    u16 unknown00; // Inferred role: sound of the drop; original member name unknown.
    u16 unknown02; // Inferred role: sound of the pickup; original member name unknown.
    u8 unknown04;  // Role and original member name unknown.
  };

  struct EmitInfo {
    bool isValid() const;

    mm::Vec3 unknown00;
    u8 _10[0x28 - 0x10];
    mm::mtl::Vector<GfDropitemInfo> unknown28; // Inferred role: dropitems; original member name unknown.
    u32 unknown50;                             // Role and original member name unknown.
    u8 unknown54;                              // Inferred role: parameter id; original member name unknown.
    bool unknown55;                            // Role and original member name unknown.
  };

  virtual ~GfFobjDropitem() {}
  void bindToGfObj(GF_OBJ_HANDLE *handle) const;
  void unbindToGfObj(GF_OBJ_HANDLE *handle) const;
  void destroy();
  void setEventDisp(bool isDisp);
  static u32 getBdatDefineFromItemId(s32 itemId);
  static u32 getResBdatIdFromItemId(s32 itemId);
  bool isEnableGet() const;
  void disposeEffect();

  u16 unknown08;  // Role and original member name unknown.
  u16 unknown0a;  // Role and original member name unknown.
  bool unknown0c; // Role and original member name unknown.
  u8 _0d;
  bool unknown0e; // Role and original member name unknown.
  u8 _0f;
  GF_OBJ_HANDLE *unknown10; // Inferred role: object; original member name unknown.
  u8 _18[0x20 - 0x18];
  u64 unknown20; // Role and original member name unknown.
  u32 unknown28; // Role and original member name unknown.
  u8 _2c[0x30 - 0x2c];
  s32 unknown30; // Inferred role: state; original member name unknown.
  u8 _34[0x38 - 0x34];
  u64 unknown38;  // Role and original member name unknown.
  u64 unknown40;  // Role and original member name unknown.
  u64 unknown48;  // Role and original member name unknown.
  bool unknown50; // Role and original member name unknown.
  u8 _51[0x54 - 0x51];
  u32 unknown54; // Inferred role: effect handle; original member name unknown.
  u8 _58[0x60 - 0x58];
};

static_assert(offsetof(GfFobjDropitem::EmitInfo, unknown28) == 0x28, "");
static_assert(offsetof(GfFobjDropitem::EmitInfo, unknown50) == 0x50, "");
static_assert(offsetof(GfFobjDropitem::EmitInfo, unknown54) == 0x54, "");
static_assert(offsetof(GfFobjDropitem, unknown08) == 0x08, "");
static_assert(offsetof(GfFobjDropitem, unknown10) == 0x10, "");
static_assert(offsetof(GfFobjDropitem, unknown30) == 0x30, "");
static_assert(offsetof(GfFobjDropitem, unknown50) == 0x50, "");
static_assert(offsetof(GfFobjDropitem, unknown54) == 0x54, "");

} // namespace gf
