#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
class DrIBLColiAcc;
class DrMan;
struct _EnvColiListTreeData;
struct _IBLPrimHeader;

class DrIBLObj {
public:
  struct unknown001 { // Inferred role: IBL data header; original name unknown.
    u32 unknown00;    // Inferred role: signature; original member name unknown.
    u32 unknown04;    // Inferred role: version; original member name unknown.
    u32 unknown08;    // Inferred role: IBL count; original member name unknown.
    u32 unknown0c;    // Inferred role: IBL entries offset; original member name unknown.
    s32 unknown10;    // Inferred role: primitive count; original member name unknown.
    u32 unknown14;    // Inferred role: primitives offset; original member name unknown.
    u8 _18[0x1c - 0x18];
    u32 unknown1c; // Inferred role: collision tree offset; original member name unknown.
  };

  struct unknown002 { // Inferred role: IBL entry; original name unknown.
    f32 unknown00;    // Inferred role: position x; original member name unknown.
    f32 unknown04;    // Inferred role: position y; original member name unknown.
    f32 unknown08;    // Inferred role: position z; original member name unknown.
    u32 unknown0c;    // Inferred role: name offset; original member name unknown.
    u32 unknown10;    // Inferred role: albedo texture offset; original member name unknown.
    u32 unknown14;    // Inferred role: albedo texture size; original member name unknown.
    u32 unknown18;    // Inferred role: normal texture offset; original member name unknown.
    u32 unknown1c;    // Inferred role: normal texture size; original member name unknown.
    u8 _20[0x28 - 0x20];
  };

  struct unknown003 { // Inferred role: sphere IBL primitive; original name unknown.
    f32 unknown00;    // Inferred role: center x; original member name unknown.
    f32 unknown04;    // Inferred role: center y; original member name unknown.
    f32 unknown08;    // Inferred role: center z; original member name unknown.
    f32 unknown0c;    // Inferred role: radius; original member name unknown.
  };

  DrIBLObj(const void *data);
  ~DrIBLObj();
  void initialize(DrMan *man);
  void update();
  bool hasValidIBL() const;
  u32 getIBLNum() const;
  // Signed: DrIBLMan::update takes an object over the current one when the current one has no primitive (-1 compares below any priority).
  int getPriority() const;
  grlib::CGLibTextureBuffer *getAlbedoTexture() const;
  grlib::CGLibTextureBuffer *getNormalTexture() const;
  const char *getIBLName(u32 index) const;
  grlib::CGLibTextureBuffer *debug_getAlbedoTexture(u32 index) const;
  grlib::CGLibTextureBuffer *debug_getNormalTexture(u32 index) const;
  void debug_renderColli(bool isCurrent);
  void render_box(const u8 *data);
  void render_sphere(const u8 *data);
  void render_cylinder(const u8 *data);
  void render_notrot_box(const u8 *data);
  void render_notrot_cylinder(const u8 *data);

  static void (DrIBLObj::*s_pRenderColi[5])(const u8 *data);

  const unknown001 *unknown00;           // Inferred role: IBL data; original member name unknown.
  const unknown002 *unknown08;           // Inferred role: IBL entries; original member name unknown.
  const _IBLPrimHeader *unknown10;       // Inferred role: IBL primitives; original member name unknown.
  const _EnvColiListTreeData *unknown18; // Inferred role: collision tree; original member name unknown.
  mm::Vec3 unknown20;                    // Inferred role: position tested against the collisions; original member name unknown.
  u8 _30[0x38 - 0x30];
  const _IBLPrimHeader *unknown38; // Inferred role: current IBL primitive; original member name unknown.
  u32 unknown40;                   // Inferred role: texture count; original member name unknown.
  u8 _44[0x48 - 0x44];
  grlib::CGLibTextureBuffer *unknown48; // Inferred role: albedo textures; original member name unknown.
  grlib::CGLibTextureBuffer *unknown50; // Inferred role: normal textures; original member name unknown.
  u32 unknown58;                        // Inferred role: state flags; original member name unknown.
  u8 unknown5c;                         // Inferred role: unknown, 1 after construction; original member name unknown.
  u8 _5d[0x60 - 0x5d];
  DrIBLColiAcc *unknown60; // Inferred role: collision access; original member name unknown.
  u8 _68[0x70 - 0x68];
};
static_assert(offsetof(DrIBLObj::unknown001, unknown08) == 0x08, "");
static_assert(offsetof(DrIBLObj::unknown001, unknown1c) == 0x1c, "");
static_assert(offsetof(DrIBLObj::unknown002, unknown0c) == 0x0c, "");
static_assert(offsetof(DrIBLObj::unknown002, unknown1c) == 0x1c, "");
static_assert(sizeof(DrIBLObj::unknown002) == 0x28, "");
static_assert(offsetof(DrIBLObj::unknown003, unknown0c) == 0x0c, "");
static_assert(offsetof(DrIBLObj, unknown08) == 0x08, "");
static_assert(offsetof(DrIBLObj, unknown38) == 0x38, "");
static_assert(offsetof(DrIBLObj, unknown40) == 0x40, "");
static_assert(offsetof(DrIBLObj, unknown48) == 0x48, "");
static_assert(offsetof(DrIBLObj, unknown50) == 0x50, "");
static_assert(offsetof(DrIBLObj, unknown58) == 0x58, "");
static_assert(offsetof(DrIBLObj, unknown5c) == 0x5c, "");
static_assert(offsetof(DrIBLObj, unknown60) == 0x60, "");
static_assert(sizeof(DrIBLObj) == 0x70, "");

} // namespace ml
