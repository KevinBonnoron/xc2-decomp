#pragma once
#include <stddef.h>

#include "grlib/cglib_uniform_array.h"
#include "layer/layer_act_base.h"
#include "layer/layer_obj_res_tex.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
class CGLibTextureBuffer;
class CGLibVtxInstans;
} // namespace grlib

namespace layer {

struct LayerResViewPortInfo;
class LayerTextureObj;
struct LayerResNode;
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
    u8 _00[0x04];
    u32 unknown04; // Inferred role: pixel width; original member name unknown.
    u8 _08[0x0c - 0x08];
    u32 unknown0c; // Inferred role: pixel height; original member name unknown.
    f32 unknown10; // Inferred role: scale x; original member name unknown.
    f32 unknown14; // Inferred role: scale y; original member name unknown.
    u32 unknown18; // Inferred role: frame count; original member name unknown.
    f32 unknown1c; // Inferred role: frame time; original member name unknown.
  };

  struct unknown008 {
    grlib::CGLibVtxInstans *unknown00; // Inferred role: instance vertex; original member name unknown.
    u32 unknown08;                     // Inferred role: instance count; original member name unknown.
  };

  // Inferred layout of a LayerResNode as LayerObjTopDef::workIconCreate resets it, in 8 byte pairs; original type and member names unknown.
  struct unknown009 {
    mm::Pnt<f32> unknown00; // Inferred role: cleared to 0; original member name unknown.
    mm::Pnt<f32> unknown08; // Inferred role: set to 1; original member name unknown.
    mm::Pnt<f32> unknown10; // Inferred role: cleared to 0; original member name unknown.
    mm::Pnt<f32> unknown18; // Inferred role: set to 1; original member name unknown.
    mm::Pnt<f32> unknown20; // Inferred role: set to 1; original member name unknown.
    mm::Pnt<f32> unknown28; // Inferred role: cleared to 0; original member name unknown.
    mm::Pnt<f32> unknown30; // Inferred role: cleared to 0; original member name unknown.
  };

  struct unknown002 {
    const unknown001 *unknown00; // Inferred role: animation data; original member name unknown.
    const u8 *unknown08;         // Inferred role: texture table of the draw data; original member name unknown.
    const u8 *unknown10;         // Inferred role: draw table; original member name unknown.
    const u8 *unknown18;         // Inferred role: mesh table; original member name unknown.
    const u8 *unknown20;         // Inferred role: place resource data; original member name unknown.
    const u8 *unknown28;         // Inferred role: place table; original member name unknown.
    const u8 *unknown30;         // Inferred role: draw resource data; original member name unknown.
    const u8 *unknown38;         // Inferred role: draw entry table; original member name unknown.
    u32 unknown40;               // Inferred role: draw entry count; original member name unknown.
    u8 _44[0x48 - 0x44];
    const u8 *unknown48; // Inferred role: icon entry table; original member name unknown.
    s32 unknown50;       // Inferred role: icon entry count; original member name unknown.
    u8 _54[0x58 - 0x54];
    LayerResViewPortInfo *m_layerResViewPortInfo;                     // Inferred role: view port; original member name unknown.
    u32 *unknown60;                                                   // Inferred role: icon entry states; original member name unknown.
    grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> *unknown68; // Inferred role: icon uniforms; original member name unknown.
    LayerResNode *m_layerResNode;                                     // Inferred role: draw entry nodes; original member name unknown.
    unknown008 *unknown78;                                            // Inferred role: instance vertex info; original member name unknown.
    f32 unknown80;                                                    // Inferred role: frame count; original member name unknown.
    f32 unknown84;                                                    // Inferred role: start frame; original member name unknown.
  };

  struct unknown003 {
    f32 m_second;  // Inferred role: second; named after the game accessor layer::LayerObjWork::setSecond.
    s32 unknown04; // Inferred role: whole frame, cleared by calcFrmParm; original member name unknown.
  };

  // Inferred layout of the def object resource header; original type and member names unknown.
  struct unknown013 {
    u8 _00[0x08];
    u32 unknown08; // Inferred role: flags; original member name unknown.
    u32 unknown0c; // Inferred role: offset of the animation data; original member name unknown.
    u32 unknown10; // Inferred role: offset of the vertex resource; original member name unknown.
    u32 unknown14; // Inferred role: offset of the draw resource data; original member name unknown.
    u32 unknown18; // Inferred role: offset of the place resource data; original member name unknown.
    u32 unknown1c; // Inferred role: offset of the draw entry list; original member name unknown.
    u32 unknown20; // Inferred role: offset of the icon entry list; original member name unknown.
    u32 unknown24; // Inferred role: offset of the texture resource; original member name unknown.
    s32 unknown28; // Inferred role: frame parm count; original member name unknown.
    u32 unknown2c; // Inferred role: offset of the icon max; original member name unknown.
    u32 unknown30; // Inferred role: mul color, one byte per channel; original member name unknown.
    u32 unknown34; // Inferred role: offset of the action data; original member name unknown.
    u32 unknown38; // Inferred role: data type; original member name unknown.
  };

  // Inferred layout of the draw resource data header, offsets relative to itself; original type and member names unknown.
  struct unknown014 {
    u32 unknown00; // Inferred role: offset of the mesh table; original member name unknown.
    u8 _04[0x08 - 0x04];
    u32 unknown08; // Inferred role: offset of the draw table; original member name unknown.
    u8 _0c[0x10 - 0x0c];
    u32 unknown10; // Inferred role: offset of the texture table; original member name unknown.
  };

  // Inferred layout of the place resource data header; original type and member names unknown.
  struct unknown015 {
    u8 _00[0x04];
    u32 unknown04; // Inferred role: offset of the place table, relative to the header; original member name unknown.
  };

  // Inferred layout of an entry list header, offset relative to itself; original type and member names unknown.
  struct unknown016 {
    u32 unknown00; // Inferred role: offset of the entries; original member name unknown.
    s32 unknown04; // Inferred role: entry count; original member name unknown.
  };

  // Inferred layout of an icon entry; original type and member names unknown.
  struct unknown017 {
    u16 unknown00; // Inferred role: mesh idx; original member name unknown.
    u16 unknown02; // Inferred role: node idx; original member name unknown.
  };

  // Inferred layout of the icon resource header; original type and member names unknown.
  struct unknown018 {
    u32 unknown00; // Inferred role: icon max; original member name unknown.
    u8 _04[0x18 - 0x04];
    u32 unknown18; // Inferred role: offset of the icon uv table, relative to this header; original member name unknown.
  };

  // Inferred layout of an icon uv entry (stride 0x1c in LayerObjMesh::call_uniform_number); original type and member names unknown.
  struct unknown021 {
    f32 unknown00[2]; // Inferred role: size; original member name unknown.
    f32 unknown08[4]; // Inferred role: uv rect; original member name unknown.
    u8 _18[0x1c - 0x18];
  };

  // Evidence: LayerObjTopDef(const char *) inlines FixStr::operator= on it (fixstr.h asserts at lines 219 and 221).
  mm::mtl::FixStr<16> unknown258; // Inferred role: name; original member name unknown.
  u8 _26c[0x270 - 0x26c];
  LayerVertexObj *m_layerVertexObj;       // Inferred role: vertex object; original member name unknown.
  LayerTextureObj *m_layerTextureObj;     // Inferred role: texture object; original member name unknown.
  grlib::CGLibTextureBuffer **unknown280; // Inferred role: default texture list; original member name unknown.

  u32 m_textureMax; // Inferred role: texture max; named after the game accessor layer::LayerAccDefTexture::getTextureMax.
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
  f32 unknown2b8;         // Inferred role: previous frame, cleared by calcFrmParm; original member name unknown.
  u8 _2bc[0x2c0 - 0x2bc];
  LayerObjResTex m_layerObjResTex; // Inferred role: additional textures; original member name unknown.
};

static_assert(offsetof(LayerObjWork, unknown258) == 0x258, "");
static_assert(offsetof(LayerObjWork, m_layerVertexObj) == 0x270, "");
static_assert(offsetof(LayerObjWork, m_layerTextureObj) == 0x278, "");
static_assert(offsetof(LayerObjWork, unknown280) == 0x280, "");
static_assert(offsetof(LayerObjWork, m_textureMax) == 0x288, "");
static_assert(offsetof(LayerObjWork, unknown290) == 0x290, "");
static_assert(offsetof(LayerObjWork, unknown2a0) == 0x2a0, "");
static_assert(offsetof(LayerObjWork, unknown2a8) == 0x2a8, "");
static_assert(offsetof(LayerObjWork, unknown298) == 0x298, "");
static_assert(offsetof(LayerObjWork, unknown2ac) == 0x2ac, "");
static_assert(offsetof(LayerObjWork, unknown2b0) == 0x2b0, "");
static_assert(offsetof(LayerObjWork, unknown2b8) == 0x2b8, "");
static_assert(offsetof(LayerObjWork, m_layerObjResTex) == 0x2c0, "");
static_assert(offsetof(LayerObjWork::unknown001, unknown04) == 0x04, "");
static_assert(offsetof(LayerObjWork::unknown001, unknown0c) == 0x0c, "");
static_assert(offsetof(LayerObjWork::unknown001, unknown18) == 0x18, "");
static_assert(sizeof(LayerObjWork::unknown009) == 0x38, "");
static_assert(offsetof(LayerObjWork::unknown002, unknown40) == 0x40, "");
static_assert(offsetof(LayerObjWork::unknown002, unknown48) == 0x48, "");
static_assert(offsetof(LayerObjWork::unknown002, m_layerResViewPortInfo) == 0x58, "");
static_assert(offsetof(LayerObjWork::unknown002, unknown68) == 0x68, "");
static_assert(offsetof(LayerObjWork::unknown002, unknown78) == 0x78, "");
static_assert(sizeof(LayerObjWork::unknown002) == 0x88, "");
static_assert(offsetof(LayerObjWork::unknown013, unknown08) == 0x08, "");
static_assert(offsetof(LayerObjWork::unknown013, unknown38) == 0x38, "");
static_assert(offsetof(LayerObjWork::unknown014, unknown10) == 0x10, "");
static_assert(sizeof(LayerObjWork::unknown017) == 0x04, "");
static_assert(offsetof(LayerObjWork::unknown018, unknown18) == 0x18, "");
static_assert(sizeof(LayerObjWork::unknown021) == 0x1c, "");

} // namespace layer
