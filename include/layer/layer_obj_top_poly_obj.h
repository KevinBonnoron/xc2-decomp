#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_res_tex.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
class CGLibVtxIndex;
class CGLibVtxVertex;
} // namespace grlib

namespace layer {
struct LayerPolyVertex;

class LayerObjTopPolyObj : public LayerObj {
public:
  struct layPolyWork {
    grlib::CGLibVtxVertex *unknown00[2]; // Inferred role: vertex buffers; original member name unknown.
    grlib::CGLibVtxIndex *unknown10[2];  // Inferred role: index buffers; original member name unknown.
    void *unknown20[2];                  // Inferred role: vertex data; original member name unknown.
    void *unknown30[2];                  // Inferred role: index data; original member name unknown.
    u16 unknown40;                       // Inferred role: vertex num; original member name unknown.
    u16 unknown42;                       // Inferred role: index num; original member name unknown.
    u16 unknown44[2];                    // Inferred role: index start; original member name unknown.
    u16 unknown48[2];                    // Inferred role: index num; original member name unknown.
    u16 unknown4c;                       // Inferred role: current index start; original member name unknown.
    u16 unknown4e;                       // Inferred role: current index num; original member name unknown.
    u16 unknown50;                       // Inferred role: current vertex buffer; original member name unknown.
    u16 unknown52;                       // Inferred role: current index buffer; original member name unknown.
    u8 _54[0x58 - 0x54];
  };

  void LockVertex();
  void setVertex(u32 index, const LayerPolyVertex &vertex);
  void UnlockVertex();
  void LockIndex();
  void setIndex(u32 index, u16 vertexIndex);
  void UnlockIndex();
  void setTexutre(const void *data);
  void setTexutre(grlib::CGLibTextureBuffer &texture);
  void resetTexutre();
  void setIndexInfo(u16 start, u16 num);

  u32 unknown250; // Inferred role: update flags; original member name unknown.
  u8 _254[0x280 - 0x254];
  grlib::CGLibDblUniformBlock unknown280; // Inferred role: uniform block; original member name unknown.
  LayerObjResTex unknown2b8;              // Inferred role: textures; original member name unknown.
  layPolyWork unknown300;                 // Inferred role: poly work; original member name unknown.
  void *unknown358;                       // Inferred role: locked buffer; original member name unknown.
  u8 _360[0x370 - 0x360];
};

static_assert(offsetof(LayerObjTopPolyObj, unknown250) == 0x250, "");
static_assert(offsetof(LayerObjTopPolyObj, unknown280) == 0x280, "");
static_assert(offsetof(LayerObjTopPolyObj, unknown2b8) == 0x2b8, "");
static_assert(offsetof(LayerObjTopPolyObj, unknown300) == 0x300, "");
static_assert(offsetof(LayerObjTopPolyObj, unknown358) == 0x358, "");
static_assert(sizeof(LayerObjTopPolyObj::layPolyWork) == 0x58, "");
static_assert(sizeof(LayerObjTopPolyObj) == 0x370, "");

} // namespace layer
