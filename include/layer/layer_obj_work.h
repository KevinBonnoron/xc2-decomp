#pragma once
#include <stddef.h>

#include "layer/layer_act_base.h"
#include "layer/layer_obj_res_tex.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
class CGLibVtxInstans;
} // namespace grlib

namespace layer {

class LayerTextureObj;
class LayerVertexObj;

class LayerObjWork : public LayerActBase {
public:
  LayerObjWork();
  f32 getMaxSecond() const;
  f32 getSecond() const;
  void setSecond(f32 second);
  void setAddTexture(const void *data, u32 index);
  void resetAddTexutre(u32 index);
  void setAddTexture(grlib::CGLibTextureBuffer &texture, u32 index);
  void resetAddAllTexutre();
  void workCreate();
  void workRelease();
  void setupDefTexList();
  void updapteAddTexList();
  void calcFrmParm(s32 count);

  struct unknown001 {
    u8 _00[0x18];
    u32 unknown18; // Inferred role: frame count; original member name unknown.
    f32 unknown1c; // Inferred role: frame time; original member name unknown.
  };

  struct unknown008 {
    grlib::CGLibVtxInstans *unknown00; // Inferred role: instance vertex; original member name unknown.
    u32 unknown08;                     // Inferred role: instance count; original member name unknown.
  };

  struct unknown002 {
    const unknown001 *unknown00; // Inferred role: animation data; original member name unknown.
    const u8 *unknown08;         // Inferred role: texture table of the draw data; original member name unknown.
    const u8 *unknown10;         // Inferred role: draw table; original member name unknown.
    u8 _18[0x20 - 0x18];
    const u8 *unknown20; // Inferred role: place resource data; original member name unknown.
    u8 _28[0x78 - 0x28];
    unknown008 *unknown78; // Inferred role: instance vertex info; original member name unknown.
    f32 unknown80;         // Inferred role: frame count; original member name unknown.
    f32 unknown84;         // Inferred role: start frame; original member name unknown.
  };

  struct unknown003 {
    f32 unknown00; // Inferred role: second; original member name unknown.
    f32 unknown04; // Inferred role: cleared by calcFrmParm; original member name unknown.
  };

  u8 unknown258; // Inferred role: cleared by the constructor; original member name unknown.
  u8 _259[0x268 - 0x259];
  u32 unknown268; // Inferred role: cleared by the constructor; original member name unknown.
  u8 _26c[0x270 - 0x26c];
  LayerVertexObj *unknown270;             // Inferred role: vertex object; original member name unknown.
  LayerTextureObj *unknown278;            // Inferred role: texture object; original member name unknown.
  grlib::CGLibTextureBuffer **unknown280; // Inferred role: default texture list; original member name unknown.

  u32 unknown288; // Inferred role: texture max; original member name unknown.
  u8 _28c[0x290 - 0x28c];
  void *unknown290;       // Inferred role: allocated memory; original member name unknown.
  unknown002 *unknown298; // Inferred role: animation work; original member name unknown.

  f32 unknown2a0; // Inferred role: parm; original member name unknown.
  u16 unknown2a4; // Inferred role: icon num; original member name unknown.
  u16 unknown2a6; // Inferred role: icon max; original member name unknown.
  u16 unknown2a8; // Inferred role: gauge; original member name unknown.
  u8 _2aa[0x2ac - 0x2aa];
  u32 unknown2ac;         // Inferred role: data type; original member name unknown.
  unknown003 *unknown2b0; // Inferred role: frame params; original member name unknown.
  u32 unknown2b8;         // Inferred role: cleared by calcFrmParm; original member name unknown.
  u8 _2bc[0x2c0 - 0x2bc];
  LayerObjResTex unknown2c0; // Inferred role: additional textures; original member name unknown.
};

static_assert(offsetof(LayerObjWork, unknown258) == 0x258, "");
static_assert(offsetof(LayerObjWork, unknown268) == 0x268, "");
static_assert(offsetof(LayerObjWork, unknown270) == 0x270, "");
static_assert(offsetof(LayerObjWork, unknown278) == 0x278, "");
static_assert(offsetof(LayerObjWork, unknown280) == 0x280, "");
static_assert(offsetof(LayerObjWork, unknown288) == 0x288, "");
static_assert(offsetof(LayerObjWork, unknown290) == 0x290, "");
static_assert(offsetof(LayerObjWork, unknown2a0) == 0x2a0, "");
static_assert(offsetof(LayerObjWork, unknown2a8) == 0x2a8, "");
static_assert(offsetof(LayerObjWork, unknown298) == 0x298, "");
static_assert(offsetof(LayerObjWork, unknown2ac) == 0x2ac, "");
static_assert(offsetof(LayerObjWork, unknown2b0) == 0x2b0, "");
static_assert(offsetof(LayerObjWork, unknown2b8) == 0x2b8, "");
static_assert(offsetof(LayerObjWork, unknown2c0) == 0x2c0, "");

} // namespace layer
