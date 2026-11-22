#pragma once
#include <stddef.h>

#include "layer/layer_obj_list.h"
#include "layer/layer_res_view_port_info.h"
#include "layer/layer_view_port.h"
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
    u32 unknown00;           // Inferred role: flags; original member name unknown.
    LayerViewPort unknown04; // Inferred role: view port; original member name unknown.
    u8 _14[0x18 - 0x14];
    grlib::CGLibRenderTarget *unknown18;    // Inferred role: render target; original member name unknown.
    LayerObjTopTexObj *m_layerObjTopTexObj; // Inferred role: texture object; original member name unknown.
    mm::Col4 unknown28;                     // Inferred role: clear color; original member name unknown.
  };

  static_assert(offsetof(unknown001, unknown04) == 0x04, "");
  static_assert(offsetof(unknown001, unknown18) == 0x18, "");
  static_assert(offsetof(unknown001, m_layerObjTopTexObj) == 0x20, "");
  static_assert(offsetof(unknown001, unknown28) == 0x28, "");
  static_assert(sizeof(unknown001) == 0x38, "");

  // Inferred layout of the layout work data, cleared as one block by the constructor (memset of 0x150 bytes at 0x2a0);
  // original type and member names unknown.
  struct unknown002 {
    const u8 *unknown00;                        // Inferred role: layout data block; original member name unknown.
    const LyrLayoutPosData *m_lyrLayoutPosData; // Inferred role: pos data table; original member name unknown.
    LayerViewPort unknown10;                    // Inferred role: view port; original member name unknown.
    u32 m_autoAnchorMode;                       // Inferred role: auto anchor mode; named after the game accessor layer::LayerAccLayoutObj::getAutoAnchorMode.
    u16 unknown24[2];                           // Inferred role: priority tbls; original member name unknown.
    u16 unknown28;                              // Inferred role: priority tbl; original member name unknown.
    u8 _2a[0x30 - 0x2a];
    LayerSortMan *m_layerSortMan;                // Inferred role: sort manager; original member name unknown.
    LayerResViewPortInfo m_layerResViewPortInfo; // Inferred role: view port info of the children; original member name unknown.
    unknown001 unknown70[2];                     // Inferred role: render targets; original member name unknown.
    unknown001 unknowne0;                        // Inferred role: previous render target; original member name unknown.
    unknown001 unknown118;                       // Inferred role: active render target; original member name unknown.
  };

  static_assert(offsetof(unknown002, unknown10) == 0x10, "");
  static_assert(offsetof(unknown002, m_autoAnchorMode) == 0x20, "");
  static_assert(offsetof(unknown002, unknown28) == 0x28, "");
  static_assert(offsetof(unknown002, m_layerSortMan) == 0x30, "");
  static_assert(offsetof(unknown002, m_layerResViewPortInfo) == 0x38, "");
  static_assert(offsetof(unknown002, unknown70) == 0x70, "");
  static_assert(offsetof(unknown002, unknowne0) == 0xe0, "");
  static_assert(offsetof(unknown002, unknown118) == 0x118, "");
  static_assert(sizeof(unknown002) == 0x150, "");

  LayerObjLayout();
  void workLayoutRelease();
  void updatePriTbl();
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
