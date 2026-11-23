#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_render_target.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_sort_mem_obj.h"
#include "types.h"

namespace layer {

struct LayerResViewPortInfo;

class LayerObjTopMemObj : public LayerObj {
public:
  LayerObjTopMemObj(u32 width, u32 height, LayerMemType type);
  ~LayerObjTopMemObj() override;
  void createWorkBuffer();
  void releaseWorkBuffer();
  void resourceInit() override;
  void *getBuffer();
  void updateBufer();
  void setRender(bool render);
  bool isRender() const;
  void applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) override;
  void setDrawList(LayerSortMan *sortMan, bool is3D) override;
  void setupRender();
  void lastRender();
  void finalRender();

  LayerResViewPortInfo *m_layerResViewPortInfo; // Inferred role: view port; original member name unknown.
  LayerObjSortMemObj m_layerObjSortMemObj;      // Inferred role: sort object; original member name unknown.
  u32 unknown270;                               // Inferred role: flags; original member name unknown.
  u8 _274[0x278 - 0x274];
  grlib::CGLibRenderTarget m_cGLibRenderTarget;       // Inferred role: render target; original member name unknown.
  grlib::CGLibDblUniformBlock m_cGLibDblUniformBlock; // Inferred role: uniform block; original member name unknown.
  grlib::CGLibOneUniformBlock unknown678;             // Inferred role: uniform block; original member name unknown.
  grlib::CGLibOneUniformBlock unknown6a0[2];          // Inferred role: uniform blocks; original member name unknown.
  grlib::CGLibOneUniformBlock unknown6f0[2];          // Inferred role: uniform blocks; original member name unknown.
  u32 m_memWidth;                                     // Inferred role: width; named after the game accessor layer::LayerAccMemObj::getMemWidth.
  u32 m_memHeight;                                    // Inferred role: height; named after the game accessor layer::LayerAccMemObj::getMemHeight.
  u32 unknown748;                                     // Inferred role: first buffer size; original member name unknown.
  u32 unknown74c;                                     // Inferred role: second buffer size; original member name unknown.
  LayerMemType unknown750;                            // Inferred role: memory type; original member name unknown.
};

static_assert(offsetof(LayerObjTopMemObj, m_layerResViewPortInfo) == 0x250, "");
static_assert(offsetof(LayerObjTopMemObj, m_layerObjSortMemObj) == 0x258, "");
static_assert(offsetof(LayerObjTopMemObj, unknown270) == 0x270, "");
static_assert(offsetof(LayerObjTopMemObj, m_cGLibRenderTarget) == 0x278, "");
static_assert(offsetof(LayerObjTopMemObj, m_cGLibDblUniformBlock) == 0x640, "");
static_assert(offsetof(LayerObjTopMemObj, unknown678) == 0x678, "");
static_assert(offsetof(LayerObjTopMemObj, unknown6a0) == 0x6a0, "");
static_assert(offsetof(LayerObjTopMemObj, unknown6f0) == 0x6f0, "");
static_assert(offsetof(LayerObjTopMemObj, m_memWidth) == 0x740, "");
static_assert(offsetof(LayerObjTopMemObj, unknown748) == 0x748, "");
static_assert(offsetof(LayerObjTopMemObj, unknown750) == 0x750, "");

} // namespace layer
