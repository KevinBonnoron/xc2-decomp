#pragma once
#include <stddef.h>

#include "layer/layer_obj_list.h"
#include "mm_math/mm_col4.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
class CGLibRenderTarget;
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

struct LyrLayoutPosData;
class LayerObjTopTexObj;
class LayerSortMan;

class LayerObjLayout : public LayerObjList {
public:
  // Inferred layout of a render target entry; original type and member names unknown.
  struct unknown001 {
    u32 unknown00; // Inferred role: flags; original member name unknown.
    f32 unknown04; // Inferred role: x; original member name unknown.
    f32 unknown08; // Inferred role: y; original member name unknown.
    f32 unknown0c; // Inferred role: width; original member name unknown.
    f32 unknown10; // Inferred role: height; original member name unknown.
    u8 _14[0x18 - 0x14];
    grlib::CGLibRenderTarget *unknown18; // Inferred role: render target; original member name unknown.
    LayerObjTopTexObj *unknown20;        // Inferred role: texture object; original member name unknown.
    mm::Col4 unknown28;                  // Inferred role: clear color; original member name unknown.
  };

  static_assert(offsetof(unknown001, unknown18) == 0x18, "");
  static_assert(offsetof(unknown001, unknown20) == 0x20, "");
  static_assert(offsetof(unknown001, unknown28) == 0x28, "");
  static_assert(sizeof(unknown001) == 0x38, "");

  // Inferred layout of the layout work data, cleared as one block by the constructor (memset of 0x150 bytes at 0x2a0);
  // original type and member names unknown.
  struct unknown002 {
    const u8 *unknown00;               // Inferred role: layout data block; original member name unknown.
    const LyrLayoutPosData *unknown08; // Inferred role: pos data table; original member name unknown.
    f32 unknown10;                     // Inferred role: view port x; original member name unknown.
    f32 unknown14;                     // Inferred role: view port y; original member name unknown.
    f32 unknown18;                     // Inferred role: view port width; original member name unknown.
    f32 unknown1c;                     // Inferred role: view port height; original member name unknown.
    u32 unknown20;                     // Inferred role: auto anchor mode; original member name unknown.
    u16 unknown24[2];                  // Inferred role: priority tbls; original member name unknown.
    u16 unknown28;                     // Inferred role: priority tbl; original member name unknown.
    u8 _2a[0x30 - 0x2a];
    LayerSortMan *unknown30; // Inferred role: sort manager; original member name unknown.
    u8 _38[0x70 - 0x38];
    unknown001 unknown70[2]; // Inferred role: render targets; original member name unknown.
    unknown001 unknowne0;    // Inferred role: previous render target; original member name unknown.
    unknown001 unknown118;   // Inferred role: active render target; original member name unknown.
  };

  static_assert(offsetof(unknown002, unknown10) == 0x10, "");
  static_assert(offsetof(unknown002, unknown20) == 0x20, "");
  static_assert(offsetof(unknown002, unknown28) == 0x28, "");
  static_assert(offsetof(unknown002, unknown30) == 0x30, "");
  static_assert(offsetof(unknown002, unknown70) == 0x70, "");
  static_assert(offsetof(unknown002, unknowne0) == 0xe0, "");
  static_assert(offsetof(unknown002, unknown118) == 0x118, "");
  static_assert(sizeof(unknown002) == 0x150, "");

  LayerObjLayout();
  void workLayoutRelease();
  void createRenderTarget(f32 x, f32 y, f32 width, f32 height, mm::Col4 clearColor);
  void releaseRenderTarget();
  grlib::CGLibTextureBuffer *getTexture();
  void setRender(bool render);
  bool isRender() const;

  unknown002 unknown2a0;                   // Inferred role: layout work data; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown3f0; // Inferred role: uniform block; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown3f8; // Inferred role: uniform block; original member name unknown.
};

static_assert(offsetof(LayerObjLayout, unknown2a0) == 0x2a0, "");
static_assert(offsetof(LayerObjLayout, unknown3f0) == 0x3f0, "");
static_assert(sizeof(LayerObjLayout) == 0x400, "");

} // namespace layer
